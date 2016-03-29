#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>

typedef struct word
{
	char e[20];//英语单词一般不会超过20个 
	char c[15];//汉语的也最多不超过7个字
	struct word * next;
}data;

void _free(data * head);
data * load(data * head);
void prn(data * head );
data *scan(data * head);
void translation(data * head_data,data * head_s);
int tran(data * head_data);
int add(data * head);
void save(data * head);
int del(data * head);


/*词表存盘*/
void save(data * head)
{
	FILE * fp;	
	fp = fopen("data.txt","w");
	data * p = head -> next;
	while(1)
	{
		fprintf(fp,"%s ",p -> e);
		fprintf(fp,"%s",p -> c);
		p = p -> next;
		if(p==NULL)
			break;
		fprintf(fp,"\n");	
	}
	fclose(fp);	
} 
/*添加词汇*/
int add(data * head)
{
	system("cls");
	printf("    *****************************************************************\n");
	printf("    **                      词表词汇添加                           **\n");
	printf("    **          此功能需要输入英文和其中文意思并存入词汇库中       **\n"); 
	printf("    *****************************************************************\n");
	printf("    输入想要添加的词汇：");
	printf("    ");
	
	data * p;
	p=(data *)malloc(sizeof(data));
	fflush(stdin);
	scanf("%s",p -> e);
	scanf("%s",p -> c);
	getchar();
	p -> next = head -> next;
	head -> next = p;
	save(head);
	printf("    *************************添加成功！******************************\n");
	printf("\n");
	printf("    ---------------------是否继续添加？ y/n-------------------------- ");
	fflush(stdin);
	if(getchar()=='y')
		add(head);
	else
		return 1;
} 
/*删除词汇*/ 
int del(data * head)
{
	system("cls");
	printf("    *****************************************************************\n");
	printf("    **                      词表词汇删除                           **\n");
	printf("    **               此功能需要输入你想删除的单词                  **\n"); 
	printf("    *****************************************************************\n");
	printf("    输入想要删除的词汇:");
	printf("    ");
	char x[20];
	fflush(stdin);
	scanf("%s",x);
	data * p = head -> next;
	data * s = head; 
	while(p)
	{
		if(strcmp(x,p -> e) == 0)
		{
			printf("    -------------------------是否删除? y/n---------------------------");
			fflush(stdin);
			if(getchar()=='y')
			{
				s -> next = p -> next;
				free(p);
				save(head);
				printf("    *************************删除成功！******************************\n");
				printf("\n");
				printf("    ---------------------是否继续删除？ y/n-------------------------- ");
				fflush(stdin);
				if(getchar()=='y')
					del(head);
				else
					return 0;	
			}
			else
			{
				printf("    -------------------------取消删除-------------------------------\n");
				return 0;
			}
			
		}
		p = p -> next;
		s = s -> next; 
		if(p == NULL)
		{
			printf("    --------------------删除失败！未找到该词-------------------------\n");
			printf("    ---------------------是否继续删除？ y/n-------------------------- ");
			fflush(stdin);			
			if(getchar()=='y')
				del(head);
			else
				return 1;
		}
	}
}
/*添加或删除词表交互模块*/
int add_del(data * head)
{
	system("cls");
	printf("    *****************************************************************\n");
	printf("    **                    1.词表词汇添加                           **\n");
	printf("    **                    2.词表词汇删除                           **\n");
	printf("    **                    0.返回                                   **\n"); 
	printf("    *****************************************************************\n");
	printf("    请选择:");
	int x;
	fflush(stdin);
	scanf("%d",&x);
	switch(x)
	{
		case 1:add(head);break;
		case 2:del(head);break;
		case 0:return 0;break;
	}
} 
/*词库的初始化*/ 
data * load(data * head) 
{
	head = (data *)malloc(sizeof(data));
	head -> next = NULL;
	FILE * fp;	
	fp = fopen("data.txt","r");
	
	while(!feof(fp))
	{
		data * p = (data *)malloc(sizeof(data));
		
		fscanf(fp,"%s",p->e);
		fscanf(fp,"%s",p->c);
		
		p -> next = head -> next;
		head -> next = p;
	}
	fclose(fp);
	return head;
}
/*遍历*/ 
void prn(data * head ) 
{
	data * p;
	p = head -> next; 
	while(p)
	{
		printf("    %s   ",p -> e);
		printf(" %s ",p -> c);
		p = p -> next;
		printf("\n"); 
	}
}
/*用户输入*/ 
data *scan(data * head)//利用尾插法，方便翻译时语序正确。 
{
	data * p,* r;
	head = (data *)malloc(sizeof(data));
	r = (data *)malloc(sizeof(data));
	scanf("%s",r->e);
	head -> next = r;
	if(getchar() == '\n')
	{
		r -> next = NULL;
		return head;
	}
	while(1)
	{
		p = (data *)malloc(sizeof(data));
		scanf("%s",p->e);
		r ->next = p;
		r = p;
		
		if(getchar() == '\n')
		{
			r -> next= NULL;
			break;
		}
	}
	return head;
	
}
/*翻译语句*/
void translation(data * head_data,data * head_s)
{
	data * p = head_s -> next;
	int i=0;
	while(p)
	{
		data * s = head_data -> next;
		while(s)
		{
			if(strcmp(p -> e , s -> e) == 0)
			{
				printf("%s ",s -> c);
				break;
			}
			
			s = s -> next;
			
			if(s == NULL)
			{
				printf("none! "); 
			}			
		}
		p = p -> next;
	}
	_free(head_s);//释放输入链表 
}
/*释放链表*/ 
void _free(data * head)
{
	data *current=head->next;
	data *tmp;
	while(current)
	{
		tmp=current->next; 
		free(current);
		current=tmp;
	}
}
/*翻译交互界面*/ 
int tran(data * head_data)
{
	data * head_s;
	system("cls");
	printf("    *****************************************************************\n");
	printf("    **                            翻译                             **\n");
	printf("    *****************************************************************\n");
	printf("    **                    none!表示该单词词库中没有                **\n");
	printf("    *****************************************************************\n");
	printf("    **                     输入想要翻译句子或单词                  **\n");
	printf("    ");
	head_s = scan(head_s);
	printf("    ");
	translation(head_data,head_s);
	printf("\n");
	printf("    ---------------------是否继续翻译？ y/n-------------------------- ");
	if(getchar()=='y')
		tran(head_data);
	else
	{
		free(head_s);
		return 1;
	}
} 
/*主程序*/ 
int main()
{
	data * head_data;//单词库的链表头 
	head_data = load(head_data);//将单词库导入内存 
	while(1)
	{
		
		int x;
		printf("    *****************************************************************\n");
		printf("    **                      简单英语翻译                           **\n");
		printf("    *****************************************************************\n");
		printf("    **                      1.翻译                                 **\n");
		printf("    **                      2.浏览词库                             **\n");
		printf("    **                      3.添加或删除词库                       **\n");
		printf("    **                      0.退出程序                             **\n");
		printf("    *****************************************************************\n");
		printf("    请选择：");
		scanf("%d",&x);
		switch(x)
		{
			case 1:tran(head_data);break;
			case 2:prn(head_data);break;
			case 3:add_del(head_data);break;
			case 0:	_free(head_data);
				free(head_data);
				printf("    *****************************************************************\n");
				printf("    **                         谢谢使用！                          **\n");
				printf("    **                         制作者：郭鑫                        **\n");
				printf("    *****************************************************************\n");
				printf("    ");
				system("pause");				
				exit(0);
				break; 
		} 
		printf("    ————————————返回主菜单中———————————————\n");
		printf ("    ");
		system("pause");
		system("cls");
	}
	return 0;
}
