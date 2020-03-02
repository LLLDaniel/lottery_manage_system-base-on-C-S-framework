#ifndef ISSUE_LOTTERY_H_
#define ISSUE_LOTTERY_H_


/*彩票结构体*/
typedef struct issue_lottery{
	double	win_total_amount;	 //奖池金额
	int 	issue_number;   //发布期号
	int	price;		//彩票单价
	int	run_status;	//开奖状态
	int	saled_count;	//本期售出总数
	int	wined_count;	//中奖人数
	int 	winning_number[WIN_NUMBER_SIZE];	//中奖号码
	
}issue_lot_t;


/*普通节点结构*/
typedef struct issue_lottery_link_node{
	issue_lot_t				ilot;
	struct issue_lottery_link_node* 	next;
	struct issue_lottery_link_node* 	prev;
}ilottery_node_t;


/*
	功能：创建发布彩票链表  ------ 双向链表
	参数：无
	返回值：成功返回头结点  失败返回NULL
*/
ilottery_node_t* create_ilottery_link(void);


/*
	功能：添加一个新节点
	参数：head 头结点  new_node 新节点	
	返回值：-1 失败 0 成功
*/
int insert_ilottery_node(ilottery_node_t* head, ilottery_node_t* new_node);

/*释放用户链表*/
void free_ilottery_link(ilottery_node_t* head);

/*打印彩票测试函数*/
void display_ilottery_link();



int get_issue_number(ilottery_node_t* ilottery_head);  // 获取本期的开奖期号

int get_saled_count();   // 获取本期的售出总数

double get_win_total_amount(ilottery_node_t* ilottery_head);  // 获取本期的奖池金额

int* get_winning_number(int *win_s) ;  // 获取本期的中奖号码

// 手动获取本期的中奖号码
int* get_winning_number_hand(int *win_s);

/*0 成功  -1 失败*/
int load_ilottery(ilottery_node_t* ilottery_head);  // 加载彩票链表

/*0 成功  -1 失败*/
int save_ilottery(ilottery_node_t* ilottery_head);  // 保存彩票链表

// 获取本期的票价
int get_price();




#endif
