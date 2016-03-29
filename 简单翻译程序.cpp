#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>

typedef struct word
{
	char e[20];//Ӣ�ﵥ��һ�㲻�ᳬ��20�� 
	char c[15];//�����Ҳ��಻����7����
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


/*�ʱ����*/
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
/*��Ӵʻ�*/
int add(data * head)
{
	system("cls");
	printf("    *****************************************************************\n");
	printf("    **                      �ʱ�ʻ����                           **\n");
	printf("    **          �˹�����Ҫ����Ӣ�ĺ���������˼������ʻ����       **\n"); 
	printf("    *****************************************************************\n");
	printf("    ������Ҫ��ӵĴʻ㣺");
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
	printf("    *************************��ӳɹ���******************************\n");
	printf("\n");
	printf("    ---------------------�Ƿ������ӣ� y/n-------------------------- ");
	fflush(stdin);
	if(getchar()=='y')
		add(head);
	else
		return 1;
} 
/*ɾ���ʻ�*/ 
int del(data * head)
{
	system("cls");
	printf("    *****************************************************************\n");
	printf("    **                      �ʱ�ʻ�ɾ��                           **\n");
	printf("    **               �˹�����Ҫ��������ɾ���ĵ���                  **\n"); 
	printf("    *****************************************************************\n");
	printf("    ������Ҫɾ���Ĵʻ�:");
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
			printf("    -------------------------�Ƿ�ɾ��? y/n---------------------------");
			fflush(stdin);
			if(getchar()=='y')
			{
				s -> next = p -> next;
				free(p);
				save(head);
				printf("    *************************ɾ���ɹ���******************************\n");
				printf("\n");
				printf("    ---------------------�Ƿ����ɾ���� y/n-------------------------- ");
				fflush(stdin);
				if(getchar()=='y')
					del(head);
				else
					return 0;	
			}
			else
			{
				printf("    -------------------------ȡ��ɾ��-------------------------------\n");
				return 0;
			}
			
		}
		p = p -> next;
		s = s -> next; 
		if(p == NULL)
		{
			printf("    --------------------ɾ��ʧ�ܣ�δ�ҵ��ô�-------------------------\n");
			printf("    ---------------------�Ƿ����ɾ���� y/n-------------------------- ");
			fflush(stdin);			
			if(getchar()=='y')
				del(head);
			else
				return 1;
		}
	}
}
/*��ӻ�ɾ���ʱ���ģ��*/
int add_del(data * head)
{
	system("cls");
	printf("    *****************************************************************\n");
	printf("    **                    1.�ʱ�ʻ����                           **\n");
	printf("    **                    2.�ʱ�ʻ�ɾ��                           **\n");
	printf("    **                    0.����                                   **\n"); 
	printf("    *****************************************************************\n");
	printf("    ��ѡ��:");
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
/*�ʿ�ĳ�ʼ��*/ 
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
/*����*/ 
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
/*�û�����*/ 
data *scan(data * head)//����β�巨�����㷭��ʱ������ȷ�� 
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
/*�������*/
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
	_free(head_s);//�ͷ��������� 
}
/*�ͷ�����*/ 
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
/*���뽻������*/ 
int tran(data * head_data)
{
	data * head_s;
	system("cls");
	printf("    *****************************************************************\n");
	printf("    **                            ����                             **\n");
	printf("    *****************************************************************\n");
	printf("    **                    none!��ʾ�õ��ʴʿ���û��                **\n");
	printf("    *****************************************************************\n");
	printf("    **                     ������Ҫ������ӻ򵥴�                  **\n");
	printf("    ");
	head_s = scan(head_s);
	printf("    ");
	translation(head_data,head_s);
	printf("\n");
	printf("    ---------------------�Ƿ�������룿 y/n-------------------------- ");
	if(getchar()=='y')
		tran(head_data);
	else
	{
		free(head_s);
		return 1;
	}
} 
/*������*/ 
int main()
{
	data * head_data;//���ʿ������ͷ 
	head_data = load(head_data);//�����ʿ⵼���ڴ� 
	while(1)
	{
		
		int x;
		printf("    *****************************************************************\n");
		printf("    **                      ��Ӣ�﷭��                           **\n");
		printf("    *****************************************************************\n");
		printf("    **                      1.����                                 **\n");
		printf("    **                      2.����ʿ�                             **\n");
		printf("    **                      3.��ӻ�ɾ���ʿ�                       **\n");
		printf("    **                      0.�˳�����                             **\n");
		printf("    *****************************************************************\n");
		printf("    ��ѡ��");
		scanf("%d",&x);
		switch(x)
		{
			case 1:tran(head_data);break;
			case 2:prn(head_data);break;
			case 3:add_del(head_data);break;
			case 0:	_free(head_data);
				free(head_data);
				printf("    *****************************************************************\n");
				printf("    **                         ллʹ�ã�                          **\n");
				printf("    **                         �����ߣ�����                        **\n");
				printf("    *****************************************************************\n");
				printf("    ");
				system("pause");				
				exit(0);
				break; 
		} 
		printf("    �������������������������������˵��С�����������������������������\n");
		printf ("    ");
		system("pause");
		system("cls");
	}
	return 0;
}
