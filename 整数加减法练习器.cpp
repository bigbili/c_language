#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <windows.h>
int data(int number);
void prn(int number,int right);
int data(int number)
{
	srand(time(NULL));
	int i;
	int a,b,c,d;
	int count=0;
	int res=0; 
	int answer;
	int sc=0;
	for(i=1;;i++)
	{
	    a = rand()%100;
	    b = rand()%100;
	    c = rand()%100;
	    d = rand()%4;	    
	    if(d==0&&a!=0&&b!=0&&c!=0)
	    {
	    	if(a+b<=100&&a+c<=100&&b+c<=100&&a+b+c<=100)
	    		{
	    			printf(" %3d+%3d+%3d= ",a,b,c);
	    			count++;
	    			res=a+b+b;
					scanf("%d",&answer);
					if(answer == res)
					{
						sc++;
					}
				}
		}	    	
	    if(d==1&&a!=0&&b!=0&&c!=0)
	    {
	    	if(a+b<=100&&a-c>=0&&b-c>=0&&a+b-c>=0&&a+b-c<=100)
	    	{
	    		printf(" %3d+%3d-%3d= ",a,b,c);
	    		count++;
	    		res=a+b-c;
				scanf("%d",&answer);
				if(answer == res)
				{
					sc++;
				}
			}	    	
		}	    	
	    if(d==2&&a!=0&&b!=0&&c!=0)
	    {
	    	if(a+c<=100&&a-b>=0&&c-b>=0&&a-b+c>=0&&a-b+c<=100)
	    	{
	    		printf(" %3d-%3d+%3d= ",a,b,c);
				count++;
				res=a-b+c;
				scanf("%d",&answer);
				if(answer == res)
				{
					sc++;
				}
			}	    	
		}		    	
	    if(d==3&&a!=0&&b!=0&&c!=0)
	    {
	    	if(a-c>=0&&a-b>=0&&a-b-c>=0)
	    	{
	    		printf(" %3d-%3d-%3d= ",a,b,c);
	    		count++;
	    		res=a-b-c;
				scanf("%d",&answer);
				if(answer == res)
				{
					sc++;
				}
			}	    	
		}
		
		if(count == number)
			break;
	}
	return sc;
}

void prn(int number,int right)
{
	int score;
	int worth;
	int pj;
	worth = number-right;
	printf("正确%3d个，错误%3d个,得分：%d\n",right,worth,right*100/number);
	pj=(int)right*10/number;
	switch(pj)
	{
	case 10:
	case 9:
	case 8:printf("非常好！正确率高！\n");break;
	case 7:
	case 6:
	case 5:printf("不错！对了一半以上,继续加油！\n");break;
	case 4:
	case 3:
	case 2:printf("同学，还需要努力呀！正确率偏低呀。\n");break;
	case 1:
	case 0:printf("不用学了，回家种田吧\n");break;
	}
}

int main()
{
	int number;	
	int right;
	printf("输入你想练题的题数:");	
	scanf("%d",&number);
	right=data(number);
	prn(number,right);
	system("pause");
	return 0;
	 
} 
