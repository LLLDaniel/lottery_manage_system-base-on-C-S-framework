#include "common.h"

char *get_string(char *s, int len)
{
	if(NULL == s){
		return NULL;
	}
	
	fgets(s, len, stdin);
	if(s[strlen(s) - 1] == '\n'){
		s[strlen(s) - 1] = '\0';
	}else{
		FLUSH();
	}
	return s;
}

/*
	function:验证码
	return:正确返回1，否则返回0
*/
int identifyCode(void)
{
	char array[100]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	char a[5]="";
	char b[5]="";

	while(1)
	{
		//得到验证码
		srand(time(NULL));
		a[0] = array[rand()%26];
		a[1] = array[rand()%26+26];
		a[2] = array[rand()%10+52];
		a[3] = array[rand()%10+52];
		a[4] = '\0';

		printf("验证码:");
		printf("%s\n",a);
		printf("\n请输入验证码（Esc强制退回）：");
		scanf("%5s",b);
		while('\n'!=getchar());

		if(strcmp(a,b) != 0)
		{
			printf("验证码错误，请重新输入！\n");
			if(b[0]==27)
			{
				return 0;
			}
		}
		else
		{
			return 1;
		}
	}
}

//小游戏
void game()
{	
	while(1)
	{
		int st = 0;
		printf("这是一个投掷骰子的游戏！！！你所选的数字与开奖号码相差不大于2时获胜，按(1.开始  2.结束)你的游戏！！！\n");
		scanf("%d",&st);
		FLUSH();
		if (st == 1)
		{	
			int ret = 0;
			printf("请输入你的点数(3~18)：");
			scanf("%d",&ret);
			FLUSH();
			srand((int)time(NULL));
			int a = 0;
			int b = 0;
			int c = 0;

			a = rand() % 6 + 1;
			b = rand() % 6 + 1;
			c = rand() % 6 + 1;
			printf("第一个骰子的结果是%d点\n", a);
			printf("第二个骰筛子的结果是%d点\n", b);
			printf("第三个骰筛子的结果是%d点\n", c);
			printf("总共的点数是结果是%d点\n", a + b + c);
			if( ret <= (a+b+c)+2 && ret >= (a+b+c)-2)
			{
				printf("你赢啦！！！！\n");
			}else{
				printf("你输啦！！！！\n");
			}
		
		}else{
			return;
		}
	}
	return;
}
