#ifndef NOTTERY_H_
#define NOTTERY_H_




/*0 成功  -1 失败*/
/*遍历用户列表，是否有中奖的, 显示中奖信息, 并且发放奖金*/
int get_winning_user(user_head_t* user_head, lottery_node_t* lottery_head, ilottery_node_t* ilottery_head, int* Win_Number, int issue_number);



#endif
