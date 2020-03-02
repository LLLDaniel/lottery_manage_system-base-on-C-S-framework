
#include "common.h"



/*0 成功  -1 失败*/
int load_user(user_head_t* user_head)
{
	if(NULL == user_head){
		return -1;
	}
	
	FILE* fp = fopen("users.bin","rb+");
	assert(fp);

	user_t user;
	memset(&user, 0 , sizeof(user));
	while( fread(&user, sizeof(user), 1, fp) == 1 )
	{
		//申请节点
		user_node_t* new_node = (user_node_t*)calloc(1, sizeof(user_node_t));
		if(NULL == new_node){
			return -1;
		}
	
		new_node->user = user;
		new_node->next = NULL;
		insert_user_node(user_head, new_node);
		memset(&user, 0 , sizeof(user));
	}
	fclose(fp);
	fp =NULL;	
	return 0;
	printf("加载用户信息成功！！！\n");
}


/*0 成功  -1 失败*/
int save_user(user_head_t* user_head)
{
	printf("保存用户信息进行！！！\n");
	if(NULL == user_head){
		return -1;
	}
	
	FILE* fp = fopen("users.bin","wb");
	assert(fp);

	user_node_t* user_node = user_head->next;
	while( user_node != NULL)
	{
		user_t user = user_node->user;

		if (fwrite(&user, sizeof(user),1, fp) != 1)
		{
			printf("保存用户信息失败！！！\n");	
			return -1;
		}
		user_node = user_node->next;
	}
	fclose(fp);
	fp =NULL;	
	return 0;
}








