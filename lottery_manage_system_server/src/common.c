#include "common.h"

char *get_string(char *s, int len)
{
	if(NULL == s){
		return NULL;
	}
	
	fgets(s, len, stdin);
	if(s[strlen(s) - 1] == '\n'){
		s[strlen(s) - 1] = '\0';
	}else{
		FLUSH();
	}
	return s;
}

//////////////////////////////user////////////////////////
/*用户充值函数*/
int recharge_user(or_t* p_or,int acceptfd,user_t* user)
{
	printf("%lf\n",user->money);
	retstr_t res;
	sprintf(res.data,"%.2f",user->money);
	if( send(acceptfd,&res, sizeof(res),0) <= 0)
	{
		printf("send failed！！！\n");
	}
	memset(p_or, 0, sizeof(or_t));
	int recvbytes = recv(acceptfd, p_or , sizeof(or_t), 0);
	if (recvbytes == -1) {
		printf("recv failed.\n");
		close(acceptfd);
		return -1;
	}
	
	double money = atoi(p_or->data);
	user->money += money;
	
	memset(&res, 0, sizeof(retstr_t));
	sprintf(res.data,"%.2f",user->money);
	if( send(acceptfd,&res, sizeof(res),0) <= 0)
	{
		printf("send failed！！！\n");
	}
	
	return 0;
}

/*打印用户个人信息函数*/
void display_user_node(or_t* p_or,int acceptfd,user_t* user)
{
	retstr_t res;
	sprintf(res.data,"%s\t\t\t%s\t\t\t%.1lf\n", user->name, user->pwd, user->money);
	if( send(acceptfd,&res, sizeof(res),0) <= 0)
	{
		printf("send failed！！！\n");
	}
	return;

}

/*用户修改自己的信息*/
int change_info_user(or_t* p_or,int acceptfd,user_t* user)
{

	retstr_t res;
	sprintf(res.data,"%s",user->pwd);
	if( send(acceptfd,&res, sizeof(res),0) <= 0)
	{
		printf("send failed！！！\n");
	}


	memset(p_or, 0, sizeof(or_t));
	int recvbytes = recv(acceptfd, p_or , sizeof(or_t), 0);
	if (recvbytes == -1) {
		printf("recv failed.\n");
		close(acceptfd);
		return -1;
	}
	strcpy(user->pwd, p_or->data);
	return 0;
	
}


/*抹掉用户个人账户,并且在此之前将该用户信息保存到制定文件*/
int free_user_node(or_t* p_or,int acceptfd,user_t* user, user_head_t* user_head, lottery_node_t* lottery_head)
{
	assert(user && user_head && lottery_head );
	// 1.如果该用户购买了彩票，清空这张彩票上的人名
	lottery_node_t* p_lott = lottery_head->next;

	while( p_lott != lottery_head ){
		if( strcmp( p_lott->lot.owner_name, user->name) == 0 )
		{
			memset( p_lott->lot.owner_name, 0 , SIZE);
		}	
		p_lott = p_lott->next;
	}
	// 2.修改用户链表，抹掉用户链表上的相关名字
	user_node_t* p = user_head->next;
	if(p == NULL || p->next == NULL)
	{
	
		free(p);
		user_head->next = NULL;
		return 0;
	}
	
	user_node_t* q = p;
	
	FILE* fp = fopen("deregister_users.bin","a+");
	
	while(p != NULL){		
		if( strcmp( user->name,p->user.name ) == 0 )
		{
			fwrite(&p->user,sizeof(user_node_t), 1, fp);
			q->next = p->next;
			free(p);
			p=NULL;	
			fclose(fp);		
			return 0;	
		} 
		q = p;
		p = p->next;
	}	
	
	return -1;
}

void display_user_lottery_link(or_t* p_or,int acceptfd,user_t* user, user_head_t* user_head, lottery_node_t* lottery_head)	//打印用户的个人彩票的链表
{
	char* PRIZE[7] = {"未开奖","未中奖","一等奖","二等奖","三等奖","四等奖","五等奖"};
	char* WIN_STU[2] = {"未领奖","已领奖"};
	lottery_node_t* p = lottery_head->prev;
	
	while( p != lottery_head )
	{
		if( strcmp( p->lot.owner_name, user->name) == 0 )
		{	
			//循环打印
			retstr_t res;
			res.flag = 1;
			for ( int i = 1; i<= p->lot.note_number; i++)
			{
				
				sprintf(res.data," %04d\t\t %d\t\t %s\t\t%02d-%02d-%02d-%02d-%02d\t %d\t\t %s\t\t %s\t\t\t  %.1lf\t\n", p->lot.id, p->lot.issue_number, p->lot.owner_name,p->lot.winning_number[i-1][0],p->lot.winning_number[i-1][1],p->lot.winning_number[i-1][2],p->lot.winning_number[i-1][3],p->lot.winning_number[i-1][4],i,WIN_STU[p->lot.winning_status+1],PRIZE[p->lot.winning_level[i-1]+1],p->lot.winning_amount[i-1]);
				if( send(acceptfd,&res, sizeof(res),0) <= 0)
				{
					printf("send failed！！！\n");
				}
			}
			sprintf(res.data,"%s","-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*--*-*-*\n");
			if( send(acceptfd,&res, sizeof(res),0) <= 0)
			{
				printf("send failed！！！\n");
			}	
		}
		p = p->prev;
	}
	retstr_t res;
	res.flag = 0;
	if( send(acceptfd,&res, sizeof(res),0) <= 0)
	{
		printf("send failed！！！\n");
	}
}


/*0 成功  -1 失败*/
int register_user(or_t* p_or,int acceptfd,info_t* p_info)  //普通用户注册
{
	if(NULL == p_info->user_head){
		return -1;
	}
	
	user_t user = p_or->user;

	/*查找是否重名*/
	{
		user_node_t* get_user = NULL;
		get_user = check_duplicate_user(p_info->user_head, &user);
		if(get_user != NULL)
		{	
			printf("已经存在相同用户名！！！\n");
			retstr_t res;
			strcpy(res.data,"已经存在相同用户名");
			if( send(acceptfd,&res, sizeof(res),0) <= 0)
			{
				printf("send failed！！！\n");
			}
			return -1;
		}
	}

	user.money = 100.0;
	
	//申请节点
	user_node_t* new_node = (user_node_t*)calloc(1, sizeof(user_node_t));
	if(NULL == new_node){
		return -1;
	}
	
	new_node->user = user;
	new_node->next = NULL;
	
	int ret = insert_user_node(p_info->user_head, new_node);
	if( ret != 0)
	{
		printf("新增加用户失败！！！\n");	
	}
	
	retstr_t res;
	strcpy(res.data,"注册成功！！！");
	if( send(acceptfd,&res, sizeof(res),0) <= 0)
	{
		printf("send failed！！！\n");
	}
	return 0;
}



/* !NULL 成功  NULL 失败*/
user_t* login_user(or_t* p_or,int acceptfd,info_t* p_info)
{
	if(NULL == p_info->user_head){
		return NULL;
	}
	
	user_t user = p_or->user;
	retstr_t res;
	
	user_node_t* get_user = check_user(p_info->user_head, &user);
	if(get_user == NULL)
	{
		printf("登陆失败！！！\n");
		res.flag = -1;
		strcpy(res.data,"登陆失败！！！----");
		if( send(acceptfd,&res, sizeof(res),0) <= 0)
		{
			printf("send failed！！！\n");
		}	
		return NULL;
	}
	
	
	strcpy(res.data,"登陆成功！！！----");
	res.flag = 0;
	if( send(acceptfd,&res, sizeof(res),0) <= 0)
	{
		printf("send failed！！！\n");
	}
	return &(get_user->user);
}


/*
	功能: 用户购买彩票
	参数：  user 用户节点的指针	
	返回值：-1 失败 0 成功
*/
int user_buy_lottery(or_t* p_or,int acceptfd,user_t* user, lottery_node_t* lottery_head, ilottery_node_t* ilottery_head)
{
	 if(NULL == user || NULL == lottery_head || NULL == ilottery_head ){
		return -1;
	}
	
	//如果发行彩票的开奖了，不能买
	retstr_t ret;
	if( ilottery_head->prev->ilot.run_status == 0 )
	{
		printf("很抱歉，本期彩票正在开奖，不能购买，请等待新一期的彩票发布......\n");
		
		ret.flag = 0;
		int sendbytes = send(acceptfd, &ret , sizeof(ret), 0);
		if (sendbytes == -1) {
			printf("send failed.\n");
			close(acceptfd);
			return -1;
		}
		return -1;
	}
	
	ret.flag = 1;
	int sendbytes = send(acceptfd, &ret , sizeof(ret), 0);
	if (sendbytes == -1) {
		printf("send failed.\n");
		close(acceptfd);
		return -1;
	}
	
	lot_t lot;
	memset(&lot, 0, sizeof(lot_t));
	
	memset(p_or, 0, sizeof(or_t));
	
	int recvbytes = recv(acceptfd, p_or , sizeof(or_t), 0);
	if (recvbytes == -1) {
		printf("recv failed.\n");
		close(acceptfd);
		return -1;
	}
	
	if ( p_or->cmd == STOPBUYLOTTERY ) {
		printf("用户停止购票.\n");
		return -1;
	}
	
	lot_t* p_lot = NULL;
	p_lot = (lot_t*)p_or->data;
	printf("----------%d.\n",p_lot->winning_number[0][0]);
	
	printf("----------.\n");
	memcpy(lot.winning_number, p_lot->winning_number, sizeof(int)*WIN_NUMBER_SIZE*WIN_NUMBER_SIZE);
	lot.note_number = p_lot->note_number;

	/*输入买彩票的相关信息*/
	memset(lot.winning_amount , 0, sizeof(int)*5);
	lot.id = get_id(lottery_head); //获取彩票id，

	lot.issue_number = get_issue_number_user_lott(ilottery_head);  //获取彩票发布期号，要发行彩票的链表

	strcpy(lot.owner_name, user->name);  // 获取购买者的姓名
	
	int res = 0;
	if( (res = deduct_user_money(user, lot.note_number)) == -1)   //扣钱
	{
		CONTINUE("很抱歉，余额不足，彩票购买失败！！！\n");
		ret.flag = 0;
		int sendbytes = send(acceptfd, &ret , sizeof(ret), 0);
		if (sendbytes == -1) {
			printf("send failed.\n");
			close(acceptfd);
			return -1;
		}
		
		p_lot = NULL;
		return -1;
	}
	lot.winning_status = -1;

	memset(lot.winning_level, -1, sizeof(int)*5);
	
	//申请节点
	lottery_node_t* new_node = (lottery_node_t*)calloc(1, sizeof(lottery_node_t));
	if(NULL == new_node){
		return -1;
	}
	
	new_node->lot = lot;
	new_node->next = NULL;
	new_node->prev = NULL;
	
	insert_lottery_node(lottery_head, new_node);

	// 彩票的售出总数加1
	ilottery_head->prev->ilot.saled_count += 1;
	// 发行彩票根据用户购买注数增加奖池金额
	ilottery_head->prev->ilot.win_total_amount += lot.note_number*2;
	
	ret.flag = 1;
	sendbytes = send(acceptfd, &ret , sizeof(ret), 0);
	if (sendbytes == -1) {
		printf("send failed.\n");
		close(acceptfd);
		return -1;
	}
	
	
	p_lot = NULL;
	return 0;
}


/*
	功能: 用户兑换彩票
	参数：  user 用户节点的指针  lottery_head 用户彩票节点的指针 	ilottery_head 发行彩票节点的指针
	返回值：-1 失败 0 成功
*/
int user_redeem_lottery(or_t* p_or,int acceptfd, user_t* user, lottery_node_t* lottery_head, ilottery_node_t* ilottery_head)
{

	if(NULL == user || NULL == lottery_head || NULL == ilottery_head ){
		return -1;
	}
	retstr_t ret;
	ret.flag = -1;
	//用户输入需要兑换的彩票的ID,获取几等奖
	int lottery_id = 0;
	int issue_number = 0;
	sscanf(p_or->data, "%d-%d", &lottery_id, &issue_number);
	
	int* prize_level = NULL;

	lottery_node_t* p_lott = lottery_head->prev;
	//进入循环，寻找对应的彩票获取获奖等级，
	while( p_lott != lottery_head ){
		// 如果id相等，领奖状态为-1未领奖，已经中奖信息不是0和-1，发布期号相等, 用户名相等
		if( p_lott->lot.id == lottery_id && p_lott->lot.winning_status == -1 && p_lott->lot.issue_number == issue_number && (strcmp(p_lott->lot.owner_name, user->name) == 0 ) ){
			//获取中奖等级
			prize_level = (int*)p_lott->lot.winning_level;
			break;
			
		}
		p_lott = p_lott->prev;
		
	}
	
	if( (prize_level == NULL) || (prize_level[0] == 0 && prize_level[1] == 0 && prize_level[2] == 0 && prize_level[3] == 0 && prize_level[4] == 0 )) 
	{
		sprintf(ret.data,"%s","很抱歉，该彩票不存在或者未中奖！！！\n");
		return -1;
	}
	
	
	//找到对应的发行彩票，取钱，给用户的账户加钱
	ilottery_node_t* p_ilott = ilottery_head->prev;
	if( p_ilott->ilot.issue_number != issue_number ) 
	{
		sprintf(ret.data,"%s","很抱歉，该彩票不存在或者未中奖，或者该期的兑奖期限已过！！！\n");
		return -1;
	}
	
	//三方改变金额
	redeem_money(user, p_lott, p_ilott, prize_level);
		
	//用户彩票上的兑换奖励信息改为已经兑换奖励0,防止重复领奖
	p_lott->lot.winning_status = 0;
	ret.flag = 0;
	sprintf(ret.data,"%s","很抱歉，该彩票不存在或者未中奖，或者该期的兑奖期限已过！！！\n");
	int sendbytes = send(acceptfd, &ret , sizeof(ret), 0);
	if (sendbytes == -1) {
		printf("send failed.\n");
		close(acceptfd);
		return -1;
	}
	return 0;
}



//////////////////////////////admin////////////////////////

/*0 成功  -1 失败*/
int login_admin(or_t* p_or,int acceptfd)
{
	/*校验是否是管理员*/
	if( strcmp(p_or->login.name, ADMIN_NAME) == 0  && strcmp(p_or->login.passwd, ADMIN_PWD) == 0 && p_or->login.jurisdiction == ADMIN_ROOT)
	{	
		retstr_t ret;
		sprintf(ret.data, "%s", ADMIN_NAME);
		int sendbytes = send(acceptfd, &ret , sizeof(ret), 0);
		if (sendbytes == -1) {
			printf("send failed.\n");
			close(acceptfd);
			return -1;
		}
		return 0;
	}else{
		retstr_t ret;
		sprintf(ret.data, "%s", "error");
		int sendbytes = send(acceptfd, &ret , sizeof(ret), 0);
		if (sendbytes == -1) {
			printf("send failed.\n");
			close(acceptfd);
			return -1;
		}
		return -1;
	}
	
}


/*打印彩票函数*/
void display_ilottery_link(or_t* p_or,int acceptfd,ilottery_node_t* head)
{
	assert(head);
	char* 	RUN_STU[2] = {"未开奖","已开奖"};
	ilottery_node_t* p = head->prev;
	
	while(p != head){
		retstr_t res;
		res.flag = 1;
		sprintf(res.data, "  %d\t\t    %d\t\t\t         %s\t\t\t   %d\t\t\t %.1f\t\t%d-%d-%d-%d-%d\t\t  %d\t\t\n", p->ilot.issue_number, p->ilot.price, RUN_STU[p->ilot.run_status+1],p->ilot.saled_count,p->ilot.win_total_amount,p->ilot.winning_number[0],p->ilot.winning_number[1],p->ilot.winning_number[2],p->ilot.winning_number[3],p->ilot.winning_number[4],p->ilot.wined_count);
		if( send(acceptfd,&res, sizeof(res),0) <= 0)
		{
			printf("send failed！！！\n");
		}
		p = p->prev;
	}
	retstr_t res;
	res.flag = 0;
	if( send(acceptfd,&res, sizeof(res),0) <= 0)
	{
		printf("send failed！！！\n");
	}
	
}


/*打印所有用户函数*/
void display_user_link(or_t* p_or,int acceptfd,user_head_t* head)
{
	assert(head);
	user_node_t* p = head->next;
	
	retstr_t ret;

	while(p){
		ret.flag = 1;
		sprintf(ret.data,"%s\t\t\t%s\t\t\t%.1lf\t\t\t\n", p->user.name, p->user.pwd, p->user.money);
		int sendbytes = send(acceptfd, &ret , sizeof(ret), 0);
		if (sendbytes == -1) {
			printf("send failed.\n");
			close(acceptfd);
			return;
		}
		p = p->next;
	}
	ret.flag = 0;
	int sendbytes = send(acceptfd, &ret , sizeof(ret), 0);
	if (sendbytes == -1) {
		printf("send failed.\n");
		close(acceptfd);
		return;
	}
}

/*对用户链表根据金额大小排序*/
void sort_money_user(or_t* p_or,int acceptfd,user_head_t* head)
{
	if( head == NULL || head->next == NULL || head->next->next == NULL )
	{
		return;
	}
	user_node_t* p = head->next;
	user_node_t* q = p;
	for( p = head->next; p->next!= NULL; p = p->next)
	{
		//user_t user = p->user;
		for( q = p->next; q != NULL; q = q->next)
		{
			if(q->user.money > p->user.money)
			{
				user_t user = p->user;
				p->user = q->user;
				q->user = user;
			}
		}
		
	}
}

/*根据彩民余额区间查询彩民*/
void display_money_section_user(or_t* p_or,int acceptfd,user_head_t* head)
{
	assert(head);
	//int max = *(int*)(p_or->data), min = *((int*)(p_or->data)+1);
	int max = 0,min = 0;
	sscanf(p_or->data,"%d-%d", &max, &min);
	printf("%d--%d\n", max, min);

	user_node_t* p = head->next;
	
	retstr_t ret;
	while(p){
		if( p->user.money <= max && p->user.money > min )
		{
			ret.flag = 1;
			sprintf(ret.data,"%s\t\t\t%s\t\t\t%.1lf\t\t\t\n\n", p->user.name, p->user.pwd, p->user.money);
			int sendbytes = send(acceptfd, &ret , sizeof(ret), 0);
			if (sendbytes == -1) {
				printf("send failed.\n");
				close(acceptfd);
				return;
			}
		}
		p = p->next;
	}
	ret.flag = 0;
	int sendbytes = send(acceptfd, &ret , sizeof(ret), 0);
	if (sendbytes == -1) {
		printf("send failed.\n");
		close(acceptfd);
		return;
	}
	return;
}

//////////////////////////////nottery////////////////////////

/*0 成功  -1 失败*/
int login_nottery(or_t* p_or,int acceptfd)
{
	/*校验是否是管理员*/
	if( strcmp(p_or->login.name, NOTTERY_NAME) == 0  && strcmp(p_or->login.passwd, NOTTERY_PWD) == 0 && p_or->login.jurisdiction == NOTTERY_ROOT)
	{	
		retstr_t ret;
		sprintf(ret.data, "%s", NOTTERY_NAME);
		int sendbytes = send(acceptfd, &ret , sizeof(ret), 0);
		if (sendbytes == -1) {
			printf("send failed.\n");
			close(acceptfd);
			return -1;
		}
		return 0;
	}else{
		retstr_t ret;
		sprintf(ret.data, "%s", "error");
		int sendbytes = send(acceptfd, &ret , sizeof(ret), 0);
		if (sendbytes == -1) {
			printf("send failed.\n");
			close(acceptfd);
			return -1;
		}
		return -1;
	}
	
}

/*0 成功  -1 失败*/
int run_lottery(or_t* p_or,int acceptfd, user_head_t* user_head, lottery_node_t* lottery_head, ilottery_node_t* ilottery_head)
{

	if(NULL == user_head && NULL == lottery_head && NULL == ilottery_head ){
		return -1;
	}
	retstr_t ret;
	
	if( 0 == ilottery_head->prev->ilot.run_status ){
		sprintf(ret.data,"%s","当前没有要开的奖！！！\n");
		int sendbytes = send(acceptfd, &ret , sizeof(ret), 0);
		if (sendbytes == -1) {
			printf("send failed.\n");
			close(acceptfd);
			return -1;
		}
		return -1;
	}
	//CONTINUE("\t\t\t-------!!!\n");
	// 1.停止发售, 获取彩票期号
	ilottery_head->prev->ilot.run_status = 0;
	int issue_number = ilottery_head->prev->ilot.issue_number;

	// 2.获取中奖号码
	int* Win_Number =  get_winning_number(ilottery_head->prev->ilot.winning_number);
	
	// 3.遍历用户列表，是否有中奖的, 显示中奖信息, 并且发放奖金
	int count = get_winning_user( user_head, lottery_head, ilottery_head , Win_Number, issue_number);

	// 4.发行彩票的中奖人数更新
	ilottery_head->prev->ilot.wined_count = count;
	sprintf(ret.data,"中奖号码为%d-%d-%d-%d-%d！！！！！！！！！！！\n一共有%d张票中奖！！！！！！！！！！！\n",Win_Number[0],Win_Number[1],Win_Number[2],Win_Number[3],Win_Number[4],count);
	int sendbytes = send(acceptfd, &ret , sizeof(ret), 0);
	if (sendbytes == -1) {
		printf("send failed.\n");
		close(acceptfd);
		return -1;
	}
	return 0;
}







