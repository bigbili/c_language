#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*八进制的结构体*/ 
typedef struct eight
{
	int nu;
	struct eight * next;	
}E; 

/*十六进制的结构体*/ 
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
//释放 
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
//二进制转换交互模块 
//********************************************* 
int two()
{
	system("cls"); 
	printf("    *****************************************************************\n");
	printf("    **                        二进制转换功能                       **\n");
	printf("    **               此功能将你输入的二进制数转换为其他进制        **\n");
	printf("    *****************************************************************\n");
	printf("    请输入一个二进制的数:") ;
	
	
	char number[64];//二进制的字符串 
	int t;//转换成十进制
	 
	/*转化成八进制要得内存*/ 
	E *head_e;	
	head_e=(E *)malloc(sizeof(E));
	head_e->next=NULL;
	E *e;

	
	/*转化成十六进制要的内存*/
	S *head_s;
	head_s=(S *)malloc(sizeof(S));
	head_s->next=NULL;
	S *s;
	
	fflush(stdin);
	gets(number);
	
	t=two_ten(number);
	if(t == 0)//输入有误 
	{ 
		printf("    ---------------------输入错误！重新输入--------------------------\n");
		system("pause") ;
		system("cls");
		two();	
	}
	 
	else
	{	/*转换*/ 
		e=ten_eight(t,head_e);
		s=ten_sixteen(t,head_s);
	
		/*输出*/	
		printf("    *****************************************************************\n");
		printf("    **                        转换结果如下                         **\n");		
        printf("                              八进制："); 
        while(e!=NULL)
        {
        	printf("%d",e->nu);
        	e = e->next; 
		}
		printf("\n");
		printf("                              十进制：%d                             \n",t);  		
		printf("                              十六进制："); 
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
//判断输入是否为真 
//********************************************* 

int judgment_eight(int number)/*八进制的判断*/ 
{
	int i;
	for(i=1;number!=0;i*=8)
	{
		if(number % 10>7)
		{
			return 0;//输入错误 
		}
		number /= 10;		
	}
	return 1;//输入正确 
}

//*********************************************
//二进制的转换
//********************************************* 
int two_ten(char * number)
{
	int d = 0;
    int len = strlen(number);
 
    if (len > 32)
        return 0;  //数位过长
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
//八进制转换交互模块 
//********************************************* 
int eight()
{
	system("cls");
	printf("    *****************************************************************\n");
	printf("    **                        八进制转换功能                       **\n");
	printf("    **               此功能将你输入的八进制数转换为其他进制        **\n");
	printf("    *****************************************************************\n");
	printf("    请输入一个八进制的数:") ;
	
	int number;//需要转换的数 
	int t;
	
	/*转换为二进制要的内存*/ 
	E *head_two;	
	head_two=(E *)malloc(sizeof(E));
	head_two->next=NULL;
	E *two;
	
	/*转化成十六进制要的内存*/
	S *head_s;
	head_s=(S *)malloc(sizeof(S));
	head_s->next=NULL;
	S *s;
	
	fflush(stdin);
	scanf("%d",&number);
	
	int i;
	i=judgment_eight(number); //进行判定 		
	
	if(i == 0)
	{ 
		printf("    ---------------------输入错误！重新输入--------------------------\n");
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
		printf("    **                        转换结果如下                         **\n");
		printf("                              二进制："); //输出二进制 
	    while(two!=NULL)
	    {
	      	printf("%d",two->nu);
	       	two = two->next; 
		}
		printf("\n"); 
		printf("                              十进制：%d                             \n",t); 
		printf("                              十六进制："); 
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
//八进制的转换
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
//十进制的转换 
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
//十进制转换交互模块  
//********************************************* 
int ten()
{
	system("cls");
	printf("    *****************************************************************\n");
	printf("    **                        十进制转换功能                       **\n");
	printf("    **               此功能将你输入的十进制数转换为其他进制        **\n");
	printf("    *****************************************************************\n");
	printf("    请输入一个十进制的数:") ;
	
	int number;
	char ch;
	/*转换为二进制要的内存*/ 
	E *head_t;	
	head_t=(E *)malloc(sizeof(E));
	head_t->next=NULL;
	E *t;
	/*转换为八进制要的内存*/ 
	E *head_e;	
	head_e=(E *)malloc(sizeof(E));
	head_e->next=NULL;
	E *e;
	/*转换为十六进制要的内存*/ 
	S *head_s;
	head_s=(S *)malloc(sizeof(S));
	head_s->next=NULL;	
	S *s;
	/*输入需要转换的数*/	
	fflush(stdin);
	scanf("%d",&number);
	
	t=ten_two(number,head_t);
	e=ten_eight(number,head_e);
	s=ten_sixteen(number,head_s); 
	
	
	printf("    *****************************************************************\n");
	printf("    **                        转换结果如下                         **\n");
	printf("                              二进制："); //输出二进制 
    while(t!=NULL)
    {
      	printf("%d",t->nu);
       	t = t->next; 
	}
	printf("\n"); 
	
	printf("                              八进制："); //输出 八进制 
    while(e!=NULL)
    {
       	printf("%d",e->nu);
       	e = e->next; 
	}
	printf("\n"); 
	printf("                              十六进制："); 
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
//十六进制转换交互模块 
//*********************************************
int sixteen()
{
	system("cls");
	printf("    *****************************************************************\n");
	printf("    **                      十六进制转换功能                       **\n");
	printf("    **             此功能将你输入的十六进制数转换为其他进制        **\n");
	printf("    *****************************************************************\n");
	printf("    请输入一个十六进制的数(不要超过10位):") ;
	
	char change[10];
	int number; 
	int t;//转换为10进制 
	
	/*转换为二进制要的内存*/ 
	E *head_t;	
	head_t=(E *)malloc(sizeof(E));
	head_t->next=NULL;
	E *two;
	/*转换为八进制要的内存*/ 
	E *head_e;	
	head_e=(E *)malloc(sizeof(E));
	head_e->next=NULL;
	E *e;
	
	fflush(stdin);
	gets(change);
	number=strlen(change);
	
	t=sixteen_ten(change,number);//转换成10进制 
	if(t == -1)
	{
		printf("    ---------------------输入错误！重新输入--------------------------\n");
		system("pause") ;
		system("cls");
		sixteen();
	}
	else
	{
		two=ten_two(t,head_t);//十进制到二进制 
		e=ten_eight(t,head_e);//十进制到八进制 
		printf("    *****************************************************************\n");
		printf("    **                        转换结果如下                         **\n");
		printf("                              二进制："); //输出二进制 
	    while(two!=NULL)
	    {
	      	printf("%d",two->nu);
	       	two = two->next; 
		}
		printf("\n"); 
		
		printf("                              八进制："); //输出 八进制 
	    while(e!=NULL)
	    {
	       	printf("%d",e->nu);
	       	e = e->next; 
		}
		printf("\n");		
		printf("                              十进制：%d                             \n",t);
		printf("    *****************************************************************\n");
	}
	
	free1(head_e);
	free(head_e);
	free1(head_t);
	free(head_t);
	return 0; 
}

//********************************************
//十六进制转换
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
//主函数，菜单交互界面  
//********************************************* 
int main()
{
	int x;
	system("color F1");
	while(1)
	{
		printf("    *****************************************************************\n");
		printf("    **                        欢迎使用进制转换                     **\n");
		printf("    *****************************************************************\n");
		printf("    **                         选择输入的进制                      **\n"); 
		printf("    **                         1：二进制                           **\n");
		printf("    **                         2：八进制                           **\n"); 
		printf("    **                         3：十进制                           **\n");
		printf("    **                         4：十六进制                         **\n");
		printf("    **                         0：退出系统                         **\n");
		printf("    *****************************************************************\n");
		printf("    请选择：");
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
				printf("    **                         谢谢使用！                          **\n");
				printf("    **                         制作者：郭鑫                        **\n");
				printf("    *****************************************************************\n");
				printf("    ");
				system("pause");
				
				exit(0);
				break;
			}
			default:{
				printf("    ---------------------输入错误！重新输入--------------------------\n");
				break;
			}
	
		}
		printf("    ");	
		system("pause") ;
		system("cls");
	}

} 
