#ifndef LOTTERY_HANDLER_H_
#define LOTTERY_HANDLER_H_




void display_user_lottery_link();	//打印用户的个人彩票的链表
 
 
int get_issue_number_user_lott();  //获取彩票发布期号，要发行彩票的链表


/*
	功能: 用户购买彩票
	参数：  lottery_head 用户彩票节点的指针	
	返回值：彩票id
*/
int get_id(lottery_node_t* lottery_head); //获取彩票id，

/*
	功能: 用户购买彩票根据注数扣钱
	参数：  user 用户节点的指针	 note_number 用户购买的注数
	返回值：-1 失败 0 成功
*/
int deduct_user_money(user_t* user, int note_number);   //根据用户购买注数扣钱

/*
	功能: 用户购买彩票填写买的中奖号码
	参数：  winning_numbe 中奖号码的指针  note_number  用户购买的注数	
	返回值：-1 0
*/
int get_winning_number_user(int (*winning_number)[5],int* note_number);  //获取购买者填写的彩票选号


/*
	功能: 用户购买彩票
	参数：  user 用户节点的指针	
	返回值：-1 失败 0 成功
*/
int user_buy_lottery();



/*
	功能: 用户彩票
	参数：  user 用户节点的指针  lottery_head 用户彩票节点的指针 	ilottery_head 发行彩票节点的指针
	返回值：-1 失败 0 成功
*/
int user_redeem_lottery();


/*
	功能: 检查用户输入的彩号是否合法
	参数：  winning_number+noteNum 数组指针
	返回值：-1 失败 0 成功
*/
int check_winning_number_user( int *winning_number );






#endif
