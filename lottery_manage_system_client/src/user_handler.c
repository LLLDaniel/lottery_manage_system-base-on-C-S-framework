
#include "common.h"


/*0 成功  -1 失败*/
int register_user()  //普通用户注册
{
	or_t or;
	or.cmd = INSERT;
	printf("请输入用户名: ");
	get_string(or.user.name, SIZE);

	printf("请输入密码: ");

	getPassword(or.user.pwd, SIZE);
	char pwd_double[SIZE] = {'\0'};
	printf("请再次输入密码: ");
	//get_string(pwd_double, SIZE);
	getPassword(pwd_double, SIZE);

	if( strcmp(pwd_double, or.user.pwd) != 0)
	{
		printf("两次输入密码不一致，请重新注册！！！\n");
		return -1;
	}
	
	
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
	PAU();
	return 0;
}

/* !NULL 成功  NULL 失败*/
int login_user()
{
	or_t or;
	or.cmd = LOGIN;
	printf("请输入用户名: ");
	get_string(or.user.name, SIZE);
	printf("请输入密码: ");

	getPassword(or.user.pwd, SIZE);
	{
		//输入验证码
		int ret = identifyCode();
		if( 0==ret )
		{	
			return -1;
		}	
	}
	
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
	if(ret.flag == 0)
	{
		return 0;
	}else{
		return -1;
	}
	
}













