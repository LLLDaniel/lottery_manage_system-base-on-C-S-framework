
#include "common.h"


/*0 成功  -1 失败 大于0 表示获奖者的个数*/
/*遍历用户列表，是否有中奖的, 显示中奖信息, 并且发放奖金*/
int get_winning_user(user_head_t* user_head, lottery_node_t* lottery_head, ilottery_node_t* ilottery_head, int* Win_Number, int issue_number)
{
	// 1.遍历用户列表
	int count = 0; //统计获奖用户人数
	lottery_node_t* p = lottery_head->prev;
	printf("-----------!!!\n\n");
	while( p != lottery_head &&  issue_number == p->lot.issue_number ){
		
		lot_t lot = p->lot;
		int prize_num[5] = {0};
		int flag = 0;
		
		for( int j = 0; j< lot.note_number; j++)
		{
			for( int i = 0; i < 5; i++)
			{	
				int temp = prize_num[j];
				if( lot.winning_number[j][i] == Win_Number[i] )
				{
					prize_num[j] += 1;
				}
				if( temp == prize_num[j] )
				{
					break;
				}
			
			}
		}
		
		//打印中奖信息
		for( int i = 0;i<lot.note_number;i++)
		{
			if( 0 == prize_num[i])    
			{
				// 给彩票标上奖级
				p->lot.winning_level[i] = prize_num[i];
			
			}else{
				printf("%s赢得了%d等奖！！！\n", lot.owner_name, 6-prize_num[i]);
				// 给彩票标上奖级
				p->lot.winning_level[i] = 6-prize_num[i];
				
				printf("等待%s来拿奖金!!!\n\n",lot.owner_name);
				
				flag= 1;
			}
		}
		memset(prize_num ,0, sizeof(int)*5);	
		p = p->prev;	
		if ( flag != 0) count += 1;	
	}
	
	printf("-----------!!!\n\n");
	return count;
}








