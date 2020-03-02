#ifndef ADMIN_H_
#define ADMIN_H_


/*
	功能: 管理员发布彩票
	参数：  ilottery_head 法行彩票节点的指针	
	返回值：-1 失败 0 成功
*/
int issue_ilottery(or_t* p_or,int acceptfd,ilottery_node_t* ilottery_head);



#endif
