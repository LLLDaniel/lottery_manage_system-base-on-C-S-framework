#ifndef COMMON_H_
#define COMMON_H_

/*
*Target：彩票管理系统-iotek-pw-1907
*Author：luxi
*Date：日期-2019-11-26-17:03:00
*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <unistd.h>  
#include<termios.h>  
#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/time.h>
#include <sys/select.h>
#include <pthread.h>



#define SIZE 20
#define ADMIN_NAME "admin"
#define ADMIN_PWD "1"
#define NOTTERY_NAME "nottery"
#define NOTTERY_PWD "1"
#define WIN_NUMBER_SIZE 5
#define WIN_NUMBER_RANGE 40

#define ADMIN_ROOT 0x01
#define NOTTERY_ROOT 0x02
#define USER 0x03

enum PTOTOCAL{
	LOGIN,			//普通用户登录
	ADMINLOGIN,			//管理员登录
	NOTTERYLOGIN,			//公正员登录
	INSERT,			//插入信息
	ISSUEINSERT,		//发行彩票插入
	RUNLOTTERY, 		//彩票开奖请求
	DELETE,			//删除
	UPDATA,			//更新数据
	RECHARGE,			//更新数据
	SELECT,			//查询
	USERSELECTLOTTERYS,			//查询购买记录
	SELECTALLILOTTERYS,			//查询所有发行彩票
	HISTORY,        //查询历史记录
	SELECTALLUSER,       //查询所以用户
	USERSELECT,        //user select
	USERUPDATA,    
	SORTUSERBYMONEY,   //根据金钱对用户进行排序 
	SELECTUSERBYMONEYSECTION,   //根据金钱区间查询用户
	BUYLOTTERY,   //购买彩票
	STOPBUYLOTTERY,   //停止购买彩票
	REDEEMLOTTERY,   //兑换彩票
};



#include "menuView.h"
#include "getPasswd.h"
#include "user_lottery_link.h"
#include "user_link.h"
#include "issue_lottery.h"
#include "user_handler.h"
#include "lottery_handler.h"
#include "controller.h"
#include "admin.h"
#include "nottery.h"

#define FLUSH() { char ch = '\0'; while( (ch = getchar()) != '\n' && ch != EOF); }
#define PAU()  getchar(); getchar(); 



/*界面暂停*/
#define CONTINUE(X) { printf(X);  getchar(); }


//定义日期结构体
//typedef struct date{
//	int 	year;
//	int 	month;
//	int 	day;
//	int 	hour;
//	int 	min;
//	int 	sec;
//}date_t;


//登录请求结构体
typedef struct loginStruct {
	int jurisdiction;	//权限（root/user）
	char name[SIZE];		//用户名
	char passwd[SIZE];	//密码
}login_t;

//操作请求
typedef struct operation_request
{
	int		cmd;		 //请求码
	char	data[256];	//附加信息  （更新数据等 时的选择项值）
	login_t login;		//登录信息
	user_t user;		//用户信息
}or_t;


typedef struct retstr{

	int flag; 		//0：结束 1：未结束
	char data[1024];
} retstr_t;


int sockfd;


char *get_string(char *s, int len);

/*
	function:验证码
	return:正确返回1，否则返回0
*/
int identifyCode(void);

//小游戏
void game();

#endif
