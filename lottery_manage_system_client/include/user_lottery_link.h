#ifndef USER_LOTTERY_LINK_H_
#define USER_LOTTERY_LINK_H_


/*彩票结构体*/
typedef struct lottery{
	double 	winning_amount[WIN_NUMBER_SIZE];	 //中奖金额
	int 	issue_number;   //发布期号
	int	id;		//id
	int	note_number;	//注数 0-5
	int	winning_status;	//领奖状态 0 -1
	int	winning_level[WIN_NUMBER_SIZE];	//中奖状态    -1 未开奖 0 没中奖 1 2 3 4 5 
	char 	owner_name[SIZE];	//购买者名字
	int 	winning_number[WIN_NUMBER_SIZE][WIN_NUMBER_SIZE];	//彩票上选中的号码,五注
}lot_t;


/*普通节点结构*/
typedef struct lottery_link_node{
	lot_t 				lot;
	struct lottery_link_node* 	next;
	struct lottery_link_node* 	prev;
}lottery_node_t;



/*
	功能：创建彩票链表
	参数：无
	返回值：成功返回头结点  失败返回NULL
*/
lottery_node_t* create_lottery_link(void);


/*
	功能：添加一个新节点
	参数：head 头结点  new_node 新节点	
	返回值：-1 失败 0 成功
*/
int insert_lottery_node(lottery_node_t* head, lottery_node_t* new_node);

/*释放用户链表*/
void free_lottery_link(lottery_node_t* head);

/*打印测试函数*/
void display_lottery_link(lottery_node_t* head);

/*0 成功  -1 失败*/
int load_lottery(lottery_node_t* lottery_head);  // 加载用户彩票链表

/*0 成功  -1 失败*/
int save_lottery(lottery_node_t* lottery_head);  // 保存用户彩票链表




#endif
















