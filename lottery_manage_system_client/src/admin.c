
#include "common.h"

/*0 成功  -1 失败*/
int issue_ilottery()
{
	or_t or;
	or.cmd = ISSUEINSERT;
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
	
	
	if( ret.flag == -1 )
	{
		printf("上一期还未开奖，不能发布彩票!!!\n");
		return -1;
	}
	else if( ret.flag == 0)
	{
		printf("%s\n",ret.data);
		
		return 0;
	}
	
	return 0;

}

/*0 成功  -1 失败*/
int login_admin()
{
	or_t or;
	or.cmd = ADMINLOGIN;
	or.login.jurisdiction = ADMIN_ROOT;
	
	printf("请输入管理员账户名: ");
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
	

	/*校验是否是管理员*/
	if( strcmp(ret.data, ADMIN_NAME) == 0)
	{		
		return 0;
	}else{
		return -1;
	}
}








