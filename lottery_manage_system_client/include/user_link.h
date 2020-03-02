#ifndef USER_LINK_H_
#define USER_LINK_H_



/*用户结构体*/
typedef struct user{
	char 	name[SIZE];
	char 	pwd[SIZE];
	double  	money;
}user_t;


/*
	功能: 用户充值
	参数：  user_node 用户节点的指针	
	返回值：-1 失败 0 成功
*/
int recharge_user();

/*
	功能: 用户修改自己的信息
	参数：  user_node 用户节点的指针	
	返回值：-1 失败 0 成功
*/
int change_info_user();

/*释放用户链表*/
void free_user_link();

/*打印测试函数*/
void display_user_link();

/*打印用户个人信息函数*/
void display_user_node();

/*打印用户中奖情况函数*/
void display_user_node_prize();

/*对用户链表根据金额大小排序*/
void sort_money_user();

/*根据彩民余额区间查询彩民*/
void display_money_section_user();  

/*释放用户个人账户*/
int free_user_node();




#endif
