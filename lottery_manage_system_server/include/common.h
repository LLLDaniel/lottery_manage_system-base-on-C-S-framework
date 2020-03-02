#ifndef COMMON_H_
#define COMMON_H_

/*
*Target：c/s版本--彩票管理系统-iotek-pw-1907
*Author：luxi
*Date：日期-2019-11-26-17:03:00
*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <unistd.h>  
# include<termios.h>  
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



#include "user_lottery_link.h"
#include "user_link.h"
#include "issue_lottery.h"
#include "user_handler.h"
#include "lottery_handler.h"


#include "nottery.h"

#define FLUSH() { char ch = '\0'; while( (ch = getchar()) != '\n' && ch != EOF); }
#define PAU()  getchar(); getchar(); 


/*界面暂停*/
#define CONTINUE(X) { printf(X);  getchar(); }



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


typedef struct info{           //链表的头节点
	user_head_t* user_head;
	ilottery_node_t* ilottery_head;
	lottery_node_t* lottery_head;
}info_t;



char *get_string(char *s, int len);



//////////////////////////////user////////////////////////
int recharge_user(or_t* p_or,int acceptfd,user_t* user);

/*打印用户个人信息函数*/
void display_user_node(or_t* p_or,int acceptfd,user_t* user);

/*用户修改自己的信息*/
int change_info_user(or_t* p_or,int acceptfd,user_t* user);

/*抹掉用户个人账户,并且在此之前将该用户信息保存到制定文件*/
int free_user_node(or_t* p_or,int acceptfd,user_t* user, user_head_t* user_head, lottery_node_t* lottery_head);

void display_user_lottery_link(or_t* p_or,int acceptfd,user_t* user, user_head_t* user_head, lottery_node_t* lottery_head);	//打印用户的个人彩票的链表

/*0 成功  -1 失败*/
int register_user(or_t* p_or,int acceptfd,info_t* p_info);

/*0 成功  -1 失败*/
user_t* login_user(or_t* p_or,int acceptfd,info_t* p_info);


/*
	功能: 用户购买彩票
	参数：  user 用户节点的指针	
	返回值：-1 失败 0 成功
*/
int user_buy_lottery(or_t* p_or,int acceptfd,user_t* user, lottery_node_t* lottery_head, ilottery_node_t* ilottery_head);

/*
	功能: 用户兑换彩票
	参数：  user 用户节点的指针  lottery_head 用户彩票节点的指针 	ilottery_head 发行彩票节点的指针
	返回值：-1 失败 0 成功
*/
int user_redeem_lottery(or_t* p_or,int acceptfd, user_t* user, lottery_node_t* lottery_head, ilottery_node_t* ilottery_head);

//////////////////////////////admin////////////////////////

#include "admin.h"
/*
	功能: 管理员登陆
	参数：   	
	返回值：-1 失败 0 成功
*/
int login_admin(or_t* p_or,int acceptfd);

/*打印彩票函数*/
void display_ilottery_link(or_t* p_or,int acceptfd,ilottery_node_t* head);

/*打印所有用户函数*/
void display_user_link(or_t* p_or,int acceptfd,user_head_t* head);


/*对用户链表根据金额大小排序*/
void sort_money_user(or_t* p_or,int acceptfd,user_head_t* head);

/*根据彩民余额区间查询彩民*/
void display_money_section_user(or_t* p_or,int acceptfd,user_head_t* head); 


//////////////////////////////nottery////////////////////////
/*0 成功  -1 失败*/
int login_nottery(or_t* p_or,int acceptfd);

/*彩票开奖函数*/
/*0 成功  -1 失败*/
int run_lottery(or_t* p_or,int acceptfd, user_head_t* user_head, lottery_node_t* lottery_head, ilottery_node_t* ilottery_head);







#endif
