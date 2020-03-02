

#include "common.h"


int get_issue_number_user_lott( ilottery_node_t* ilottery_head)  //获取彩票发布期号，要发行彩票的链表
{
	if(ilottery_head->prev != ilottery_head)
	{
		return ilottery_head->prev->ilot.issue_number;
	}
	else
	{
		return 1000;
	}
}

int get_id(lottery_node_t* lottery_head) //获取彩票id，
{	
	if(lottery_head->prev != lottery_head)
	{
		return lottery_head->prev->lot.id + 1;
	}
	else
	{
		return 1;
	}
}

int deduct_user_money(user_t* user, int note_number)   //根据用户购买注数扣钱
{	
	if( NULL == user)
	{
		return -1;
	}
	// 用户余额不足返回 购买失败
	if( user->money < note_number*2 )
	{
		return -1;
	}
	user->money -= note_number*2;
	return 0;
}


int check_winning_number_user( int *winning_number )  //检查用户输入的彩号
{
	for( int i=0;i<5;i++)
	{
		//printf("\t\t\t%d--------------------------------------\n\n",*(winning_number+i));
		if( *(winning_number+i) > WIN_NUMBER_RANGE || *(winning_number+i) < 1 )
		{
			return -1;
		}
	}
	return 0;
}


/*
	功能: 三方改变金额
	参数：  user 用户节点的指针  lottery_head 用户彩票节点的指针 	ilottery_head 发行彩票节点的指针  prize_level 用户获奖等级 
	返回值：-1 失败 0 成功
*/
int redeem_money(user_t* user, lottery_node_t* lott_p, ilottery_node_t* ilott_p, int* prize_level)
{
	for(int i=0; i<5; i++)
	{
		switch(prize_level[i])
		{
			case 1:		//一等奖
				{
					double money = 0.3*ilott_p->ilot.win_total_amount + 5000000.0;   //一等奖中奖金额，总的金额的百分之30,外加500万
					printf("您成功兑换%d等奖，奖金为 30%% x %.1lf + %.1lf = %.1lf元，已经发放到您的账户\n",prize_level[i],ilott_p->ilot.win_total_amount, 5000000.0 , money);
					ilott_p->ilot.win_total_amount -= money;   //发行彩票扣钱
					if(ilott_p->ilot.win_total_amount <= 0)
					{
						printf("奖池余额不够请联系管理员！！！\n");
						ilott_p->ilot.win_total_amount = 0;
					}
					user->money +=  money;			//用户加钱
					lott_p->lot.winning_amount[i] = money; 	//用户彩票写上中奖
				}
				break;
			case 2:		//二等奖
				{
					double money = 0.1*ilott_p->ilot.win_total_amount + 1000000.0;  //二等奖中奖金额，总的金额的百分之10,外加一百万
					printf("您成功兑换%d等奖，奖金为 10%% x %.1lf + %.1lf = %.1lf元，已经发放到您的账户\n",prize_level[i],ilott_p->ilot.win_total_amount, 1000000.0 , money);
					ilott_p->ilot.win_total_amount -= money;   //发行彩票扣钱
					if(ilott_p->ilot.win_total_amount <= 0)
					{
						printf("奖池余额不够请联系管理员！！！\n");
						ilott_p->ilot.win_total_amount = 0;
					}
					user->money +=  money;			//用户加钱
					lott_p->lot.winning_amount[i] = money; 	//用户彩票写上中奖
				}
				break;
			case 3:		//三等奖
				{
					double money = 0.05*ilott_p->ilot.win_total_amount + 200000.0;    //三等奖中奖金额，总的金额的百分之5，外加20万
					printf("您成功兑换%d等奖，奖金为 5%% x %.1lf + %.1lf = %.1lf元，已经发放到您的账户\n",prize_level[i],ilott_p->ilot.win_total_amount, 200000.0 , money);
					ilott_p->ilot.win_total_amount -= money;   //发行彩票扣钱
					if(ilott_p->ilot.win_total_amount <= 0)
					{
						printf("奖池余额不够请联系管理员！！！\n");
						ilott_p->ilot.win_total_amount = 0;
					}
					user->money +=  money;			//用户加钱
					lott_p->lot.winning_amount[i] = money; 	//用户彩票写上中奖	
				}
				break;
			case 4:		//四等奖
				{
					double money = 200.0;
					ilott_p->ilot.win_total_amount -= money;   //发行彩票扣钱
					if(ilott_p->ilot.win_total_amount <= 0)
					{
						printf("奖池余额不够请联系管理员！！！\n");
						ilott_p->ilot.win_total_amount = 0;
					}
					user->money +=  money;			//用户加钱
					lott_p->lot.winning_amount[i] = money; 	//用户彩票写上中奖
					printf("您成功兑换%d等奖，奖金为 %.1lf 元，已经发放到您的账户\n",prize_level[i], money);
				}
				break;
			case 5:		//五等奖
				{
					double money = 5.0;
					ilott_p->ilot.win_total_amount -= money;   //发行彩票扣钱
					if(ilott_p->ilot.win_total_amount <= 0)
					{
						printf("奖池余额不够请联系管理员！！！\n");
						ilott_p->ilot.win_total_amount = 0;
					}
					user->money +=  money;			//用户加钱
					lott_p->lot.winning_amount[i] = money; 	//用户彩票写上中奖
					printf("您成功兑换%d等奖，奖金为 %.1lf 元，已经发放到您的账户\n",prize_level[i], money);
				}
				break;	
		}
		
	}
	return 0;
}





















