#include "common.h"


/*
*Target：彩票管理系统-iotek-pw-1907
*Author：luxi
*Date：日期-2019-11-26-17:03:00
*/

int sockfd;
struct sockaddr_in serveraddr;
struct sockaddr_in clientaddr;
socklen_t addrlen = sizeof(serveraddr);
socklen_t cli_len = sizeof(clientaddr);



void * handle(void * arg);

int main(int argc, const char *argv[])
{
	info_t info;
	info.user_head = create_user_link();  // 创建用户链表
	info.ilottery_head = create_ilottery_link(); // 创建发行彩票链表
	info.lottery_head = create_lottery_link(); // 创建用户彩票链表

	if(NULL == info.user_head || NULL == info.ilottery_head ){
		return 0;
	}
	
	/*加载*/
	load_user(info.user_head);
	load_ilottery(info.ilottery_head);
	load_lottery(info.lottery_head);

	//identity_control(user_head,ilottery_head,lottery_head);
	
	
	//socket->填充->绑定->监听->等待连接->数据交互->关闭 

	//创建网络通信的套接字
	sockfd = socket(AF_INET,SOCK_STREAM, 0);
	if(sockfd == -1){
		perror("socket failed.\n");
		exit(-1);
	}
	printf("sockfd :%d.\n",sockfd); 

	//填充网络结构体
	memset(&serveraddr,0,sizeof(serveraddr));
	memset(&clientaddr,0,sizeof(clientaddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port   = htons(atoi(argv[2]));
	serveraddr.sin_addr.s_addr = inet_addr(argv[1]);

	//绑定网络套接字和网络结构体
	if(bind(sockfd, (const struct sockaddr *)&serveraddr,addrlen) == -1){
		printf("bind failed.\n");
		exit(-1);
	}

	//监听套接字，将主动套接字转化为被动套接字
	if(listen(sockfd,10) == -1){
		printf("listen failed.\n");
		exit(-1);
	}

	fd_set readfds;
	int select_return;
	struct timeval timeout;

	while (1)
	{
		FD_ZERO(&readfds);
		FD_SET(sockfd, &readfds);
		FD_SET(0, &readfds);

		timeout.tv_sec = 1;
		timeout.tv_usec = 0;

		//printf("开始 select ! \n");
		select_return = select(sockfd + 1,&readfds,NULL,NULL,&timeout);
		if (select_return < 0)
		{
			printf("select error ! \n");
			return -1;
		}
		else if (select_return == 0)
		{
			//printf("select 请求超时 ！\n");
		}
		else {
			int i = 0;
			for (i = 0; i <= sockfd; i++)
			{
				if (FD_ISSET(i, &readfds))
				{
					if(i == sockfd)			//并发触发方式为sockfd
					{
						//printf("select 请求成功！\n");
						pthread_t thread;
						pthread_create(&thread,NULL,handle, (void *)&info);//工作线程
					}
					if(i == 0)
					{
						//local_instal();
						char buff[24] = {'\0'};
						get_string(buff,sizeof(buff));	
						if( strcmp(buff, "exit") == 0)
						{
							goto head_exit;
						}
					}
				}
			}
		}
	}
	
head_exit:
	close(sockfd);
	
	/*保存*/
	save_user(info.user_head); // 保存用户链表
	save_ilottery(info.ilottery_head); // 保存发行彩票链表
	save_lottery(info.lottery_head); // 保存用户彩票链表

	free_user_link(info.user_head);
	free_ilottery_link(info.ilottery_head);
	free_lottery_link(info.lottery_head);
	return 0;
}



void * handle(void * arg)
{
	info_t* p_info = (info_t *)arg;
	int acceptfd;
	or_t or;
	user_t* p_user;
	ssize_t recvbytes;

	//数据交互 
	acceptfd = accept(sockfd, (struct sockaddr *)&clientaddr, &cli_len);
	if (acceptfd == -1) {
		printf("acceptfd failed.\n");
		exit(-1);
	}

	while (1) {
		memset(&or, 0, sizeof(or_t));
		recvbytes = recv(acceptfd, &or , sizeof(or_t ), 0);
		if (recvbytes == -1) {
			printf("recv failed.\n");
			close(acceptfd);
			break;
		}
		else if (recvbytes == 0) {
			printf("设备离线\n");
			goto head_exit;
			break;
		}
		else {

			printf("CMD : %d\n",or.cmd);
			switch (or .cmd)
			{
			case LOGIN:
				printf("普通登录请求\n");				
				p_user = login_user(&or,acceptfd,p_info);		
				break;
			case ADMINLOGIN:
				printf("管理员登录请求\n");			
				login_admin(&or,acceptfd);		
				break;
			case NOTTERYLOGIN:
				printf("公正员登录请求\n");			
				login_nottery(&or,acceptfd);		
				break;	
			case INSERT:
				printf("添加新用户插入请求\n");
				register_user(&or,acceptfd,p_info);
				break;
			case ISSUEINSERT:
				printf("发行彩票插入请求\n");
				issue_ilottery(&or,acceptfd,p_info->ilottery_head);
				break;
			case RUNLOTTERY:
				printf("彩票开奖请求\n");
				run_lottery(&or,acceptfd,p_info->user_head, p_info->lottery_head,p_info->ilottery_head);
				break;	
			case SELECTALLILOTTERYS:
				printf("查询所有发行彩票请求\n");
				display_ilottery_link(&or,acceptfd,p_info->ilottery_head);
				break;	
			case SELECT:
				printf("查询信息请求\n");
				
				break;
			case RECHARGE:
				printf("账户充值请求");
				recharge_user(&or,acceptfd,p_user);
				break;	
			case SELECTALLUSER:
				printf("查询所有用户信息请求");
				display_user_link(&or,acceptfd,p_info->user_head);
				break;
			case UPDATA:
				printf("数据更新请求");
				break;
			case DELETE:
				printf("数据删除请求");
				free_user_node(&or,acceptfd,p_user, p_info->user_head, p_info->lottery_head);
				break;
			case USERSELECT:
				printf("USER查询个人信息请求\n");
				display_user_node(&or,acceptfd,p_user);
				break;
			case USERSELECTLOTTERYS:
				printf("USER查询购买信息请求\n");
				display_user_lottery_link(&or,acceptfd,p_user, p_info->user_head, p_info->lottery_head);
				break;
			case USERUPDATA:
				printf("USER更新信息请求\n");
				change_info_user(&or,acceptfd,p_user);
				break;
			case SORTUSERBYMONEY:
				printf("根据金钱对用户进行排序\n");
				sort_money_user(&or,acceptfd,p_info->user_head);
				break;
			case SELECTUSERBYMONEYSECTION:
				printf("根据金钱区间查询用户\n");
				display_money_section_user(&or,acceptfd,p_info->user_head);
				break;
			case BUYLOTTERY:
				printf("用户购买彩票\n");
				user_buy_lottery(&or,acceptfd,p_user, p_info->lottery_head,p_info->ilottery_head );
				break;
			case REDEEMLOTTERY:
				printf("用户兑换彩票\n");
				user_redeem_lottery(&or,acceptfd,p_user, p_info->lottery_head,p_info->ilottery_head );
				break;
			default:
				printf("请求码查无此项！ \n");
				break;
			}

		}
	}
head_exit :
	/*保存*/
	save_user(p_info->user_head); // 保存用户链表
	save_ilottery(p_info->ilottery_head); // 保存发行彩票链表
	save_lottery(p_info->lottery_head); // 保存用户彩票链表
	pthread_exit(NULL);
}




