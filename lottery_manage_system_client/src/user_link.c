
#include "common.h"

/*
	功能：添加一个新节点
	参数：head 头结点  new_node 新节点	
	返回值：-1 失败 0 成功
*/
int insert_user_node()
{
	
		
	return 0;
}


/*
	功能：创建用户链表
	参数：无
	返回值：成功返回头结点  失败返回NULL
*/
int create_user_link(void)
{

	return 0;
}

/*释放用户链表*/
void free_user_link()
{
	
	return;
}

/*打印测试函数*/
void display_user_link()
{
	printf("进入界面\n");
	printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*\n");
	printf("姓名\t\t\t密码\t\t\t余额\n");
	printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*\n");
	or_t or;
	or.cmd = SELECTALLUSER;
	int sendbytes = send(sockfd, &or , sizeof(or), 0);
	if (sendbytes == -1) {
		printf("send failed.\n");
		close(sockfd);
		return;
	}
	
	retstr_t ret;
	ret.flag = 1;
	while(ret.flag)
	{
		int recvbytes = recv(sockfd, &ret , sizeof(ret), 0);
		if (recvbytes == -1) {
			printf("recv failed.\n");
			close(sockfd);
			return;
		}
			
		printf("%s\n", ret.data);
		printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*\n");
	}
	return;
}

/*登陆校核函数*/
void check_user()
{
		
	return;
}

/*注册去重函数*/
void check_duplicate_user()
{
		
	return;
}


/*用户充值函数*/
int recharge_user()
{
	
	printf("进入充值界面\n");
	or_t or;
	or.cmd = RECHARGE;
	int sendbytes = send(sockfd, &or , sizeof(or), 0);
	if (sendbytes == -1) {
		printf("send failed.\n");
		close(sockfd);
		return -1;
	}
	retstr_t ret;
	int recvbytes = recv(sockfd, &ret , sizeof(ret), 0);
	if (recvbytes == -1) {
		printf("recv failed.\n");
		close(sockfd);
		return -1;
	}
	
	printf("账户余额为：%s元\n", ret.data);
	int charge_m = 0;
	while(charge_m <= 0)
	{
		printf("请输入充值金额(正数)：");
		scanf("%d",&charge_m);	
	}
	
	memset(or.data, 0, sizeof(or.data));
	sprintf(or.data, "%d",charge_m);
	sendbytes = send(sockfd, &or , sizeof(or), 0);
	if (sendbytes == -1) {
		printf("send failed.\n");
		close(sockfd);
		return -1;
	}
	memset(&ret, 0, sizeof(ret));
	recvbytes = recv(sockfd, &ret , sizeof(ret), 0);
	if (recvbytes == -1) {
		printf("recv failed.\n");
		close(sockfd);
		return -1;
	}
	printf("充值成功！！！\n");
	printf("账户余额为：%s元\n", ret.data);
	
	return 0;
}

/*打印用户个人信息函数*/
void display_user_node()
{
	printf("进入界面\n");
	printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*\n");
	printf("姓名\t\t\t密码\t\t\t余额\n");
	printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*\n");
	or_t or;
	or.cmd = USERSELECT;
	int sendbytes = send(sockfd, &or , sizeof(or), 0);
	if (sendbytes == -1) {
		printf("send failed.\n");
		close(sockfd);
		return;
	}
	retstr_t ret;
	int recvbytes = recv(sockfd, &ret , sizeof(ret), 0);
	if (recvbytes == -1) {
		printf("recv failed.\n");
		close(sockfd);
		return;
	}

	printf("%s\n", ret.data);
	return;
}


/*打印用户中奖情况函数*/
void display_user_node_prize()
{
	
	printf("进入中奖情况页面\n");
	return;
}



/*用户修改自己的信息*/
int change_info_user()
{
	
	printf("进入修改用户密码界面（Esc强制退回）\n");
	or_t or;
	or.cmd = USERUPDATA;
	int sendbytes = send(sockfd, &or , sizeof(or), 0);
	if (sendbytes == -1) {
		printf("send failed.\n");
		close(sockfd);
		return -1;
	}
	
	
	int flag = 1;
	user_t user;
	
	retstr_t ret;
	int recvbytes = recv(sockfd, &ret , sizeof(ret), 0);
	if (recvbytes == -1) {
		printf("recv failed.\n");
		close(sockfd);
		return -1;
	}
	strcpy(user.pwd, ret.data);
	while(flag)
	{
		char new_pwd[SIZE] = {'\0'};
		char new_pwd_t[SIZE] = {'\0'};
		printf("请输入新的密码：");
		///get_string(new_pwd, SIZE);
		getPassword(new_pwd, SIZE);
		if( (strcmp(user.pwd,new_pwd) == 0))
		{
			printf("新密码和旧密码不能一致！！！\n");
			FLUSH();
			continue;
		
		}else if( new_pwd[0] == 27 ){
			return -1;
		}
		
		printf("请再次确认新的密码：");
		//get_string(new_pwd_t, SIZE);
		getPassword(new_pwd_t, SIZE);
		
		if( new_pwd_t[0] == 27 )
		{
			return -1;
		}
		else if( (strcmp(new_pwd_t,new_pwd) != 0))
		{
			printf("两次密码不一致！！！\n");
			FLUSH();
			continue;
		
		}
		else
		{
			flag  = 0;
			memset(or.data, 0, sizeof(or.data));
			sprintf(or.data, "%s",new_pwd);
			int sendbytes = send(sockfd, &or , sizeof(or), 0);
			if (sendbytes == -1) {
				printf("send failed.\n");
				close(sockfd);
				return -1;
			}
			return 0;
		}
	}
	
	
	return 0;
	
}

/*对用户链表根据金额大小排序*/
void sort_money_user()
{
	or_t or;
	or.cmd = SORTUSERBYMONEY;
	int sendbytes = send(sockfd, &or , sizeof(or), 0);
	if (sendbytes == -1) {
		printf("send failed.\n");
		close(sockfd);
		return;
	}
	
	return;
}


/*根据彩民余额区间查询彩民*/
void display_money_section_user()
{
	int max = 0, min = 0;
	printf("请输入最大金额:");
	scanf("%d",&max);
	printf("请输入最小金额:");
	scanf("%d",&min);
	
	FLUSH();

	printf("进入界面\n");
	printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*\n");
	printf("姓名\t\t\t密码\t\t\t余额\n");
	printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*\n");
	or_t or;
	sprintf(or.data,"%d-%d",max, min);
	or.cmd = SELECTUSERBYMONEYSECTION;
	int sendbytes = send(sockfd, &or , sizeof(or), 0);
	if (sendbytes == -1) {
		printf("send failed.\n");
		close(sockfd);
		return;
	}
	retstr_t ret;
	ret.flag = 1;
	while(ret.flag)
	{
		int recvbytes = recv(sockfd, &ret , sizeof(ret), 0);
		if (recvbytes == -1) {
			printf("recv failed.\n");
			close(sockfd);
			return;
		}
			
		printf("%s\n", ret.data);
		printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*\n");
	}
	
	return;
}


/*抹掉用户个人账户,并且在此之前将该用户信息保存到制定文件*/
int free_user_node()
{
	or_t or;
	or.cmd = DELETE;
	int sendbytes = send(sockfd, &or , sizeof(or), 0);
	if (sendbytes == -1) {
		printf("send failed.\n");
		close(sockfd);
		return -1;
	}
	
	return 0;
}




































