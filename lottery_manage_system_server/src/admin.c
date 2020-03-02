
#include "common.h"

/*0 成功  -1 失败*/
int issue_ilottery(or_t* p_or,int acceptfd,ilottery_node_t* ilottery_head)
{
	if(NULL == ilottery_head){
		return -1;
	}

	if( ilottery_head->prev->ilot.run_status != 0  )
	{
		printf("上一期还未开奖，不能发布彩票!!!\n");
		fflush(stdout);
		retstr_t ret;
		ret.flag = -1;
		int sendbytes = send(acceptfd, &ret , sizeof(ret), 0);
		if (sendbytes == -1) {
			printf("send failed.\n");
			close(acceptfd);
			return -1;
		}
		return -1;
	}

	issue_lot_t ilot;
	memset(&ilot, 0, sizeof(issue_lot_t));
	
	ilot.issue_number = get_issue_number(ilottery_head);  // 获取本期的开奖期号

	ilot.saled_count = get_saled_count();   // 获取本期的售出总数

	ilot.win_total_amount = get_win_total_amount(ilottery_head);  // 获取本期的奖池金额

	//printf("\t\t\t%.1f!!!\n", ilot.win_total_amount);
	ilot.price = get_price();   // 获取本期的票价
	ilot.wined_count = 0;	  // 获取本期的中奖人数
	ilot.run_status = -1;   // 获取本期开奖状态


	retstr_t ret;
	ret.flag = 0;
	sprintf(ret.data, "本期的期号：%d\n本期的票价：%d元\n本期的奖池金额：%.1lf元\n", ilot.issue_number,ilot.price,ilot.win_total_amount);
	
	int sendbytes = send(acceptfd, &ret , sizeof(ret), 0);
	if (sendbytes == -1) {
		printf("send failed.\n");
		close(acceptfd);
		return -1;
	}
	
	//申请节点
	ilottery_node_t* new_node = (ilottery_node_t*)calloc(1, sizeof(ilottery_node_t));
	if(NULL == new_node){
		return -1;
	}
	
	new_node->ilot = ilot;
	new_node->next = NULL;
	new_node->prev = NULL;
	printf("send failed.----\n");
	return insert_ilottery_node(ilottery_head, new_node);

}










