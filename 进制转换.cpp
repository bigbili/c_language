#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*�˽��ƵĽṹ��*/ 
typedef struct eight
{
	int nu;
	struct eight * next;	
}E; 

/*ʮ�����ƵĽṹ��*/ 
typedef struct sixteen
{
	char nu;
	struct sixteen * next;
}S;

//******************************************** 
int judgment_eight(int number); 

int two();
int eight();
int ten();
int sixteen();

int two_ten(char *number);

int eight_ten(int number);
E *eight_two(int number,E *head_two);
S *eight_sixteen(int number,S *head_s);

E *ten_two(int t,E *head_t);
E *ten_eight(int t,E *head_e);
S *ten_sixteen(int t,S *head_s);

int sixteen_ten(char *a,int number);

void free1(E * head);
void free2(S * head);

//**********************************************
//�ͷ� 
//**********************************************
void free1(E * head)
{	
	E *current=head->next;
	E *tmp;
	while(current)
	{
		tmp=current->next; 
		free(current);
		current=tmp;
	}
}
void free2(S * head)
{	
	S *current=head->next;
	S *tmp;
	while(current)
	{
		tmp=current->next; 
		free(current);
		current=tmp;
	}
}
//*********************************************
//������ת������ģ�� 
//********************************************* 
int two()
{
	system("cls"); 
	printf("    *****************************************************************\n");
	printf("    **                        ������ת������                       **\n");
	printf("    **               �˹��ܽ�������Ķ�������ת��Ϊ��������        **\n");
	printf("    *****************************************************************\n");
	printf("    ������һ�������Ƶ���:") ;
	
	
	char number[64];//�����Ƶ��ַ��� 
	int t;//ת����ʮ����
	 
	/*ת���ɰ˽���Ҫ���ڴ�*/ 
	E *head_e;	
	head_e=(E *)malloc(sizeof(E));
	head_e->next=NULL;
	E *e;

	
	/*ת����ʮ������Ҫ���ڴ�*/
	S *head_s;
	head_s=(S *)malloc(sizeof(S));
	head_s->next=NULL;
	S *s;
	
	fflush(stdin);
	gets(number);
	
	t=two_ten(number);
	if(t == 0)//�������� 
	{ 
		printf("    ---------------------���������������--------------------------\n");
		system("pause") ;
		system("cls");
		two();	
	}
	 
	else
	{	/*ת��*/ 
		e=ten_eight(t,head_e);
		s=ten_sixteen(t,head_s);
	
		/*���*/	
		printf("    *****************************************************************\n");
		printf("    **                        ת���������                         **\n");		
        printf("                              �˽��ƣ�"); 
        while(e!=NULL)
        {
        	printf("%d",e->nu);
        	e = e->next; 
		}
		printf("\n");
		printf("                              ʮ���ƣ�%d                             \n",t);  		
		printf("                              ʮ�����ƣ�"); 
		while(s!=NULL)
		{
			printf("%c",s->nu);
			s = s->next; 
		}		
		printf("\n"); 
		printf("    *****************************************************************\n");
	}
	free1(head_e);
	free(head_e);
	free2(head_s);
	free(head_s);
	return 0;
}
//*********************************************
//�ж������Ƿ�Ϊ�� 
//********************************************* 

int judgment_eight(int number)/*�˽��Ƶ��ж�*/ 
{
	int i;
	for(i=1;number!=0;i*=8)
	{
		if(number % 10>7)
		{
			return 0;//������� 
		}
		number /= 10;		
	}
	return 1;//������ȷ 
}

//*********************************************
//�����Ƶ�ת��
//********************************************* 
int two_ten(char * number)
{
	int d = 0;
    int len = strlen(number);
 
    if (len > 32)
        return 0;  //��λ����
    len--;
 
    int i,k;
    for (i = len,k = 1 ; i >=0; i--,k*=2)
    {
	     
        d += ((number[i] - '0') * k); 
        
		if(number[i]>'1')
	    {
	    	return 0;
		}  
    }
 
    return d;
}

//*********************************************
//�˽���ת������ģ�� 
//********************************************* 
int eight()
{
	system("cls");
	printf("    *****************************************************************\n");
	printf("    **                        �˽���ת������                       **\n");
	printf("    **               �˹��ܽ�������İ˽�����ת��Ϊ��������        **\n");
	printf("    *****************************************************************\n");
	printf("    ������һ���˽��Ƶ���:") ;
	
	int number;//��Ҫת������ 
	int t;
	
	/*ת��Ϊ������Ҫ���ڴ�*/ 
	E *head_two;	
	head_two=(E *)malloc(sizeof(E));
	head_two->next=NULL;
	E *two;
	
	/*ת����ʮ������Ҫ���ڴ�*/
	S *head_s;
	head_s=(S *)malloc(sizeof(S));
	head_s->next=NULL;
	S *s;
	
	fflush(stdin);
	scanf("%d",&number);
	
	int i;
	i=judgment_eight(number); //�����ж� 		
	
	if(i == 0)
	{ 
		printf("    ---------------------���������������--------------------------\n");
		system("pause") ;
		system("cls");
		eight();
	}
	else
	{
		t=eight_ten(number);
		two=eight_two(number,head_two);
		s=eight_sixteen(number,head_s);
		
		printf("    *****************************************************************\n");
		printf("    **                        ת���������                         **\n");
		printf("                              �����ƣ�"); //��������� 
	    while(two!=NULL)
	    {
	      	printf("%d",two->nu);
	       	two = two->next; 
		}
		printf("\n"); 
		printf("                              ʮ���ƣ�%d                             \n",t); 
		printf("                              ʮ�����ƣ�"); 
		while(s!=NULL)
		{
			printf("%c",s->nu);
			s = s->next; 
		}		
		printf("\n"); 
		printf("    *****************************************************************\n");
		
		
	} 
	free1(head_two);
	free(head_two);
	free2(head_s);
	free(head_s);
	return 0;
}

//*********************************************
//�˽��Ƶ�ת��
//*********************************************
int eight_ten(int number)
{
	
	int i;
	int rt=0;
	for(i=1;number!=0;i*=8)
	{
		rt+=(number % 10)*i;
		number=number/10;	
	}
	return rt;
}

E *eight_two(int number,E *head_two)
{
	int t=eight_ten(number);
	E *p=ten_two(t,head_two);
	return p;
}

S *eight_sixteen(int number,S *head_s)
{
	int t=eight_ten(number);
	S *p=ten_sixteen(t,head_s);
	return p;
}

//*********************************************
//ʮ���Ƶ�ת�� 
//*********************************************
S *ten_sixteen(int t,S *head_s)
{	
	S *p;
	while(t != 0)
	{
		p=(S * )malloc(sizeof(S));
		p->nu = t % 16;
		t /= 16;
		p->next = head_s->next;
		head_s->next=p;
		if(p->nu >= 10)
		{
			switch(p->nu) 
            { 
	            case 10: 
	                p->nu = 'A'; 
	                break; 
	            case 11: 
	                p->nu = 'B'; 
	                break; 
	            case 12: 
	                p->nu = 'C'; 
	                break; 
	            case 13: 
	                p->nu = 'D'; 
	                break; 
	            case 14: 
	                p->nu = 'E'; 
	                break; 
	            case 15: 
	                p->nu = 'F'; 
	                break; 
            }        
		}
		else
        	p->nu += 48;
	} 
	return head_s->next;
}

E *ten_eight(int t,E *head_e)
{
	E *p;
	while(t!=0)
	{
		p=(E * )malloc(sizeof(E));
		p->nu = t % 8;
		t /= 8;
		p->next = head_e->next;
		head_e->next=p;
	}
	return head_e->next;
} 

E *ten_two(int t,E *head_t)
{
	E *p;
	while(t!=0)
	{
		p=(E * )malloc(sizeof(E));
		p->nu = t % 2;
		t /= 2;// 100
		p->next = head_t->next;
		head_t->next=p;
	}
	return head_t->next;
}

//*********************************************
//ʮ����ת������ģ��  
//********************************************* 
int ten()
{
	system("cls");
	printf("    *****************************************************************\n");
	printf("    **                        ʮ����ת������                       **\n");
	printf("    **               �˹��ܽ��������ʮ������ת��Ϊ��������        **\n");
	printf("    *****************************************************************\n");
	printf("    ������һ��ʮ���Ƶ���:") ;
	
	int number;
	char ch;
	/*ת��Ϊ������Ҫ���ڴ�*/ 
	E *head_t;	
	head_t=(E *)malloc(sizeof(E));
	head_t->next=NULL;
	E *t;
	/*ת��Ϊ�˽���Ҫ���ڴ�*/ 
	E *head_e;	
	head_e=(E *)malloc(sizeof(E));
	head_e->next=NULL;
	E *e;
	/*ת��Ϊʮ������Ҫ���ڴ�*/ 
	S *head_s;
	head_s=(S *)malloc(sizeof(S));
	head_s->next=NULL;	
	S *s;
	/*������Ҫת������*/	
	fflush(stdin);
	scanf("%d",&number);
	
	t=ten_two(number,head_t);
	e=ten_eight(number,head_e);
	s=ten_sixteen(number,head_s); 
	
	
	printf("    *****************************************************************\n");
	printf("    **                        ת���������                         **\n");
	printf("                              �����ƣ�"); //��������� 
    while(t!=NULL)
    {
      	printf("%d",t->nu);
       	t = t->next; 
	}
	printf("\n"); 
	
	printf("                              �˽��ƣ�"); //��� �˽��� 
    while(e!=NULL)
    {
       	printf("%d",e->nu);
       	e = e->next; 
	}
	printf("\n"); 
	printf("                              ʮ�����ƣ�"); 
	while(s!=NULL)
	{
		printf("%c",s->nu);
		s = s->next; 
	}
	
	printf("\n"); 
	printf("    *****************************************************************\n");
	
	free1(head_t);
	free(head_t);
	free1(head_e);
	free(head_e);
	free2(head_s);
	free(head_s);
	return 0;
}

//*********************************************
//ʮ������ת������ģ�� 
//*********************************************
int sixteen()
{
	system("cls");
	printf("    *****************************************************************\n");
	printf("    **                      ʮ������ת������                       **\n");
	printf("    **             �˹��ܽ��������ʮ��������ת��Ϊ��������        **\n");
	printf("    *****************************************************************\n");
	printf("    ������һ��ʮ�����Ƶ���(��Ҫ����10λ):") ;
	
	char change[10];
	int number; 
	int t;//ת��Ϊ10���� 
	
	/*ת��Ϊ������Ҫ���ڴ�*/ 
	E *head_t;	
	head_t=(E *)malloc(sizeof(E));
	head_t->next=NULL;
	E *two;
	/*ת��Ϊ�˽���Ҫ���ڴ�*/ 
	E *head_e;	
	head_e=(E *)malloc(sizeof(E));
	head_e->next=NULL;
	E *e;
	
	fflush(stdin);
	gets(change);
	number=strlen(change);
	
	t=sixteen_ten(change,number);//ת����10���� 
	if(t == -1)
	{
		printf("    ---------------------���������������--------------------------\n");
		system("pause") ;
		system("cls");
		sixteen();
	}
	else
	{
		two=ten_two(t,head_t);//ʮ���Ƶ������� 
		e=ten_eight(t,head_e);//ʮ���Ƶ��˽��� 
		printf("    *****************************************************************\n");
		printf("    **                        ת���������                         **\n");
		printf("                              �����ƣ�"); //��������� 
	    while(two!=NULL)
	    {
	      	printf("%d",two->nu);
	       	two = two->next; 
		}
		printf("\n"); 
		
		printf("                              �˽��ƣ�"); //��� �˽��� 
	    while(e!=NULL)
	    {
	       	printf("%d",e->nu);
	       	e = e->next; 
		}
		printf("\n");		
		printf("                              ʮ���ƣ�%d                             \n",t);
		printf("    *****************************************************************\n");
	}
	
	free1(head_e);
	free(head_e);
	free1(head_t);
	free(head_t);
	return 0; 
}

//********************************************
//ʮ������ת��
//******************************************** 
int sixteen_ten(char *a,int number)
{	
	int i,j,rt;
	int b[50];
	for(i=0;i<number;i++)
	{
		if(a[i] <= '9' && a[i] >= '0') 
        { 
            b[i]=a[i]-48;
        }
        else 
        { 
            switch(a[i]) 
            { 
	            case 'A': 
	                b[i] = 10; 
	                break; 
	            case 'B': 
	                b[i] = 11; 
	                break; 
	            case 'C': 
	                b[i] = 12; 
	                break; 
	            case 'D': 
	                b[i]= 13; 
	                break; 
	            case 'E': 
	                b[i]= 14; 
	                break; 
	            case 'F': 
	                b[i] = 15; 
	                break; 
	            case 'a': 
	                b[i] = 10; 
	                break; 
	            case 'b': 
	                b[i] = 11; 
	                break; 
	            case 'c': 
	                b[i] = 12; 
	                break; 
	            case 'd': 
	                b[i] = 13; 
	                break; 
	            case 'e': 
	                b[i] = 14; 
	                break; 
	            case 'f': 
	                b[i] = 15; 
	                break;
	            default :
	            	return -1;
	        }
		}
	}
	for(i = 1, j = number - 1; j >= 0; j--, i *= 16) 
    { 
        rt += b[j] * i; 
    }
    return rt;	
}
	 
//*********************************************
//���������˵���������  
//********************************************* 
int main()
{
	int x;
	system("color F1");
	while(1)
	{
		printf("    *****************************************************************\n");
		printf("    **                        ��ӭʹ�ý���ת��                     **\n");
		printf("    *****************************************************************\n");
		printf("    **                         ѡ������Ľ���                      **\n"); 
		printf("    **                         1��������                           **\n");
		printf("    **                         2���˽���                           **\n"); 
		printf("    **                         3��ʮ����                           **\n");
		printf("    **                         4��ʮ������                         **\n");
		printf("    **                         0���˳�ϵͳ                         **\n");
		printf("    *****************************************************************\n");
		printf("    ��ѡ��");
		scanf("%d",&x);
		switch(x)
		{
			case 1:{
				two();
				break;
			}
			case 2:{
				eight();
				break;
			}
			case 3:{
				ten();
				break;
			}
			case 4:{
				sixteen();
				break;
			}
			case 0:{
				printf("    *****************************************************************\n");
				printf("    **                         ллʹ�ã�                          **\n");
				printf("    **                         �����ߣ�����                        **\n");
				printf("    *****************************************************************\n");
				printf("    ");
				system("pause");
				
				exit(0);
				break;
			}
			default:{
				printf("    ---------------------���������������--------------------------\n");
				break;
			}
	
		}
		printf("    ");	
		system("pause") ;
		system("cls");
	}

} 
