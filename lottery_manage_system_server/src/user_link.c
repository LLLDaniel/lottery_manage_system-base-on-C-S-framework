
#include "common.h"


/*
	功能：添加一个新节点
	参数：head 头结点  new_node 新节点	
	返回值：-1 失败 0 成功
*/
int insert_user_node(user_head_t* head, user_node_t* new_node)
{
	if(NULL == head || NULL == new_node){
		return -1;
	}
	
	/*找尾节点*/
	if(head->next == NULL){
		head->next = new_node;
		new_node->next = NULL;
	}else{
		user_node_t* p = head->next;
		while(p->next != NULL){
			p = p->next;
		}
		
		p->next = new_node;
		new_node->next = NULL;
	}	
		
	return 0;
}


/*
	功能：创建用户链表
	参数：无
	返回值：成功返回头结点  失败返回NULL
*/
user_head_t* create_user_link(void)
{
	user_head_t* head = (user_head_t*)calloc(1, sizeof(user_head_t));
	if(NULL == head){
		return NULL;
	}
	
	head->next = NULL;
	return head;
}

/*释放用户链表*/
void free_user_link(user_head_t* head)
{
	assert(head);
	user_node_t* p = head->next;
	user_node_t* q = p;
	while(p){
		q = p->next;
		free(p);
		p = q;
	}
	free(head);
	head = NULL;
}



/*登陆校核函数*/
user_node_t* check_user(user_head_t* head, user_t* user_node)
{
	if(NULL == head || NULL == user_node){
		return NULL;
	}
	
	/*找节点*/
	user_node_t* p = head->next;
	while(p != NULL){
		if( (strcmp(p->user.name,user_node->name) == 0) && (strcmp(p->user.pwd,user_node->pwd) == 0))
		{
			//printf("查到了一个\n");
			return p;
		}
		p = p->next;
	}		
	return NULL;
}

/*注册去重函数*/
user_node_t* check_duplicate_user(user_head_t* head, user_t* user_node)
{
	if(NULL == head || NULL == user_node){
		return NULL;
	}

	/*找节点*/
	user_node_t* p = head->next;
	while(p != NULL){
		if( (strcmp(p->user.name,user_node->name) == 0))
		{
			//printf("查到了一个\n");
			return p;
		}
		p = p->next;
	}
	//printf("没有查到\n");		
	return NULL;
}



/*打印用户中奖情况函数*/
void display_user_node_prize(user_t* user)
{
	assert(user);
	printf("进入中奖情况页面\n");
}















































