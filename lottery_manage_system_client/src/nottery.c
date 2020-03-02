
#include "common.h"

/*0 成功  -1 失败*/
int run_lottery()
{
	or_t or;
	or.cmd = RUNLOTTERY;
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
	
	printf("%s\n",ret.data);
	
	return 0;
}


/*0 成功  -1 失败 大于0 表示获奖者的个数*/
/*遍历用户列表，是否有中奖的, 显示中奖信息, 并且发放奖金*/
int get_winning_user()
{
	return 0;
}

/*
	功能: 公正员登陆
	参数：   	
	返回值：-1 失败 0 成功
*/
int login_nottery()
{
	or_t or;
	or.cmd = NOTTERYLOGIN;
	or.login.jurisdiction = NOTTERY_ROOT;

	printf("请输入公正员账户名: ");
	get_string(or.login.name, SIZE);
	printf("请输入密码: ");
	//get_string(pwd, SIZE);
	getPassword(or.login.passwd, SIZE);
	
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

	/*校验是否是管理员或者公证员*/
	if( strcmp(ret.data, NOTTERY_NAME) == 0)
	{		
		return 0;
	}else{
		return -1;
	}
}







