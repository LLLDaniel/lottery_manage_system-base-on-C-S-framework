

#include "common.h"

/*
	功能：添加一个新节点
	参数：head 头结点  new_node 新节点	
	返回值：-1 失败 0 成功
*/
int insert_lottery_node(lottery_node_t* head, lottery_node_t* new_node)
{
	if(NULL == head || NULL == new_node){
		return -1;
	}
	
	new_node->next = head;
	new_node->prev = head->prev;
	head->prev->next = new_node;
	head->prev = new_node;	
		
	return 0;
}


/*
	功能：创建彩票链表
	参数：无
	返回值：成功返回头结点  失败返回NULL
*/
lottery_node_t* create_lottery_link(void)
{
	lottery_node_t* head = (lottery_node_t*)calloc(1, sizeof(lottery_node_t));
	if(NULL == head){
		return NULL;
	}
	
	head->next = head;
	head->prev = head;
	return head;
}

/*释放彩票链表*/
void free_lottery_link(lottery_node_t* head)
{
	assert(head);
	lottery_node_t* p = head->next;
	lottery_node_t* q = p;
	while(p != head ){
		q = p->next;
		free(p);
		p = q;
	}
	free(head);
	head = NULL;
}

/*打印用户彩票函数*/
void display_lottery_link(lottery_node_t* head)
{
	assert(head);
	char* PRIZE[7] = {"未开奖","未中奖","一等奖","二等奖","三等奖","四等奖","五等奖"};
	char* WIN_STU[2] = {"未领奖","已领奖"};
	lottery_node_t* p = head->next;
	printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*--*-*-*\n");
	printf("彩票ID\t\t彩票期号\t购买者\t\t购买彩号\t注数\t\t领奖状态\t中奖信息\t\t中奖金额（元）\t\t\n");
	printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*--*-*-*\n");
	while(p != head ){		
			//循环打印
			for ( int i = 1; i<= p->lot.note_number; i++)
			{
				printf(" %04d\t\t %d\t\t %s\t\t%02d-%02d-%02d-%02d-%02d\t %d\t\t %s\t\t %s\t\t\t  %.1lf\t\n", p->lot.id, p->lot.issue_number, p->lot.owner_name,p->lot.winning_number[i-1][0],p->lot.winning_number[i-1][1],p->lot.winning_number[i-1][2],p->lot.winning_number[i-1][3],p->lot.winning_number[i-1][4],i,WIN_STU[p->lot.winning_status+1],PRIZE[p->lot.winning_level[i-1]+1],p->lot.winning_amount[i-1]);
			}	
		printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*--*-*-*\n");
		p = p->next;
	}
}

/*0 成功  -1 失败*/
int load_lottery(lottery_node_t* lottery_head)  // 加载用户彩票链表
{
	if(NULL == lottery_head){
		return -1;
	}
	
	FILE* fp = fopen("lotterys.bin","rb+");
	assert(fp);

	lot_t lot;
	memset(&lot, 0 , sizeof(lot));
	while( fread(&lot, sizeof(lot), 1, fp) == 1 )
	{
		//申请节点
		lottery_node_t* new_node = (lottery_node_t*)calloc(1, sizeof(lottery_node_t));
		if(NULL == new_node){
			return -1;
		}
	
		new_node->lot = lot;
		new_node->next = NULL;
		new_node->prev = NULL;

		insert_lottery_node(lottery_head, new_node);
		memset(&lot, 0 , sizeof(lot));
	}
	printf("加载用户彩票信息成功！！！\n");
	fclose(fp);
	fp =NULL;	
	return 0;

}


/*0 成功  -1 失败*/
int save_lottery(lottery_node_t* lottery_head) // 保存用户彩票链表
{
	printf("保存用户彩票信息进行！！！\n");
	if(NULL == lottery_head){
		return -1;
	}
	
	FILE* fp = fopen("lotterys.bin","wb");
	assert(fp);

	lottery_node_t* p = lottery_head->next;
	while( p != lottery_head)
	{
		lot_t lot = p->lot;

		if (fwrite(&lot, sizeof(lot),1, fp) != 1)
		{
			printf("保存用户彩票信息失败！！！\n");	
			return -1;
		}
		p = p->next;
	}
	fclose(fp);
	fp =NULL;	
	return 0;
}





