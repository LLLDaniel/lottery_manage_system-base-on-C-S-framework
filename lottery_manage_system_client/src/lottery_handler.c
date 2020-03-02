

#include "common.h"


void display_user_lottery_link()	//打印用户的个人彩票的链表
{
	or_t or;
	or.cmd = USERSELECTLOTTERYS;
	int sendbytes = send(sockfd, &or , sizeof(or), 0);
	if (sendbytes == -1) {
		printf("send failed.\n");
		close(sockfd);
		return;
	}
	printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*--*-*-*\n");
	printf("彩票ID\t\t彩票期号\t购买者\t\t购买彩号\t注数\t\t领奖状态\t中奖信息\t\t中奖金额（元）\t\t\n");
	printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*--*-*-*\n");
	
	int flag = 1;
	while( flag )
	{
		retstr_t ret;
		int recvbytes = recv(sockfd, &ret , sizeof(ret), 0);
		if (recvbytes == -1) {
			printf("recv failed.\n");
			close(sockfd);
			return;
		}
		printf("%s\n",ret.data);
		flag = ret.flag;
	}
	return;
}



int get_issue_number_user_lott( ilottery_node_t* ilottery_head)  //获取彩票发布期号，要发行彩票的链表
{
	if(ilottery_head->prev != ilottery_head)
	{
		return ilottery_head->prev->ilot.issue_number;
	}
	else
	{
		return 1000;
	}
}

int get_id(lottery_node_t* lottery_head) //获取彩票id，
{	
	if(lottery_head->prev != lottery_head)
	{
		return lottery_head->prev->lot.id + 1;
	}
	else
	{
		return 1;
	}
}

int deduct_user_money(user_t* user, int note_number)   //根据用户购买注数扣钱
{	
	if( NULL == user)
	{
		return -1;
	}
	// 用户余额不足返回 购买失败
	if( user->money < note_number*2 )
	{
		return -1;
	}
	user->money -= note_number*2;
	return 0;
}


int check_winning_number_user( int *winning_number )  //检查用户输入的彩号
{
	for( int i=0;i<5;i++)
	{
		//printf("\t\t\t%d--------------------------------------\n\n",*(winning_number+i));
		if( *(winning_number+i) > WIN_NUMBER_RANGE || *(winning_number+i) < 1 )
		{
			return -1;
		}
	}
	return 0;
}

int get_winning_number_user(int (*winning_number)[5],int* note_number)  //获取购买者填写的彩票选号
{	
	int flag = 1;
	do{
		printf("请输入你想要选择的彩号--------------------------------------\n\n");
		
		//获取用户输入的5注彩票
		int noteNum = 0;
		int cho = 0;
		for( noteNum= 0; noteNum<5; noteNum++)
		{
			
			if( 2 == cho ) break;
			cho = 0;
			
			while(1)
			{	
				printf("请输入第%d注你想要选择的五位彩号:",noteNum+1);
				for( int i = 0;i<5;i++)
				{
					scanf("%d", &winning_number[noteNum][i]);
				}
				FLUSH();
				int ret = check_winning_number_user( (int*)winning_number+noteNum );
				if( 0==ret )
				{
					break;	
				}
				else{
					printf("您所选的彩号不在开彩范围，请重新输入！！！\n\n");
				}
			}
			if( 4 > noteNum )
			{
				printf("\n请选择您的操作(1.继续下注 2.停止下注):");
				scanf("%d",&cho);
				FLUSH();
		 	}			
		}
		
		
		*note_number = noteNum;  // 把购买注数复制到彩票节点上
		//printf("%d----",*note_number);
		if( 0 != (*note_number) )
		{
			//购买成功，显示信息
			printf("您购买的彩号是：\n\n");
			printf("\n༺  ༺  ༺  ༺  ༺  ༺  ༺  ༺  ༺  ༺  ༺  ༺  ༻  ༻  ༻  ༻  ༻  ༻  ༻  ༻  ༻   \n\n");
			for(int i = 0;i<5;i++)
			{
				printf("༺  ༺  ༺  ༺  ༺    %02d --- %02d --- %02d --- %02d --- %02d  ༻  ༻  ༻  ༻  ༻    \n\n", winning_number[i][0],winning_number[i][1],winning_number[i][2],winning_number[i][3],winning_number[i][4]);
			}
			printf("༺  ༺  ༺  ༺  ༺  ༺  ༺  ༺  ༺  ༺  ༺  ༺  ༻  ༻  ༻  ༻  ༻  ༻  ༻  ༻  ༻   \n\n");
			while(1){
				int choice = 0;
				printf("你将支付 %d 元钱，请确认你的选择（1:确认，2:重新填写彩号,3:停止购买彩票）:", (*note_number)*2);
				scanf("%d", &choice);
				FLUSH();
				if( 1 == choice ){
					flag = 0;
					break;
				}
				else if( 2 == choice ){	
					memset(winning_number, 0, sizeof(int)*25);				
					break;
				}
				else if( 3 == choice ){	
					memset(winning_number, 0, sizeof(int)*25);				
					return -1;
				}
			}
			
		}
	}while( 1 == flag );
	
	return 0;
}


/*
	功能: 用户购买彩票
	参数：  user 用户节点的指针  lottery_head 用户彩票节点的指针 	ilottery_head 发行彩票节点的指针
	返回值：-1 失败 0 成功
*/
int user_buy_lottery()  //用户购买彩票
{
	
	or_t or;
	or.cmd = BUYLOTTERY;
	int sendbytes = send(sockfd, &or , sizeof(or), 0);
	if (sendbytes == -1) {
		printf("send failed.\n");
		close(sockfd);
		return -1;
	}
	
	retstr_t ret;
	ret.flag = -1;
	int recvbytes = recv(sockfd, &ret , sizeof(ret), 0);
	if (recvbytes == -1) {
		printf("recv failed.\n");
		close(sockfd);
		return -1;
	}
	
	if( ret.flag == 0 )
	{
		printf("很抱歉，本期彩票正在开奖，不能购买，请等待新一期的彩票发布......\n");
		return -1;
	}
	printf("开始彩票购买（说明：彩号在1~%d之间选择，最多购买五注，每注2元钱）\n", WIN_NUMBER_RANGE);
	
	lot_t lot;
	memset(&lot, 0, sizeof(lot));
	
	/*输入买彩票的相关信息*/	
	int ret_c = get_winning_number_user(lot.winning_number, &lot.note_number);  //获取购买者填写的彩票选号
	if( -1 == ret_c ){
		or.cmd = STOPBUYLOTTERY;
		int sendbytes = send(sockfd, &or , sizeof(or), 0);
		if (sendbytes == -1) {
			printf("send failed.\n");
			close(sockfd);
			return -1;
		}
		return -1;     //用户停止购买彩票
	}
	
	memcpy(or.data, &lot, sizeof(lot));
	sendbytes = send(sockfd, &or , sizeof(or), 0);
	if (sendbytes == -1) {
		printf("send failed.\n");
		close(sockfd);
		return -1;
	}
	
	recvbytes = recv(sockfd, &ret , sizeof(ret), 0);
	if (recvbytes == -1) {
		printf("recv failed.\n");
		close(sockfd);
		return -1;
	}
	
	if( ret.flag == 0)   //扣钱
	{
		CONTINUE("很抱歉，余额不足，彩票购买失败！！！\n");
		return -1;
	}

	return 0;
}


/*
	功能: 用户兑换彩票
	参数：  user 用户节点的指针  lottery_head 用户彩票节点的指针 	ilottery_head 发行彩票节点的指针
	返回值：-1 失败 0 成功
*/
int user_redeem_lottery()
{
	
	//用户输入需要兑换的彩票的ID,获取几等奖
	int lottery_id = 0;
	int issue_number = 0;
	
	printf("请输入需要兑换的彩票的ID:");
	scanf("%d", &lottery_id);
	FLUSH();
	printf("请输入需要兑换的彩票的发布期号:");
	scanf("%d", &issue_number);
	FLUSH();

	or_t or;
	or.cmd = REDEEMLOTTERY;
	sprintf(or.data, "%d-%d", lottery_id, issue_number);
	
	int sendbytes = send(sockfd, &or , sizeof(or), 0);
	if (sendbytes == -1) {
		printf("send failed.\n");
		close(sockfd);
		return -1;
	}
	
	retstr_t ret;
	ret.flag = -1;
	int recvbytes = recv(sockfd, &ret , sizeof(ret), 0);
	if (recvbytes == -1) {
		printf("recv failed.\n");
		close(sockfd);
		return -1;
	}
	
	printf("%s\n",ret.data);
	if( ret.flag == 0)
	{
		return 0;
	}
	else
	{
		return -1;
	}
	
}






















