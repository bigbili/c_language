#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct customer//客户信息结构体 
{
	char name[10];//姓名
	int num ;//订了几本书
	char pnb[12];//联系电话 
	struct customer * next;
	
}cus;

typedef struct magazine//杂志信息的结构体
{
	char name[40];//名字
	char no[7];//编号6位
	char type[10];//类型
	float money;//定价 
	int dys;//订阅数
	struct magazine * next;
}mag;


mag * load1(mag * head);
cus * load2(cus * head);
int login();
int admin(mag * head_m,cus * head_c);
int administrators(mag * head_m,cus * head_c);
int dy(mag * head_m, cus * head_c);
int td(mag * head_m, cus * head_c); 

int s_m_na(mag * head,char * name);
int s_m_t(mag * head,char * type);
int s_m_m(mag * head,float money);
int s_m_no(mag * head,char * no);
int search_mag(mag * head);
int magazine_info(mag * head);
int add_mag(mag * head);
int del_mag(mag * head);
int revise_mag(mag * head);
void prn_mag(mag * head) ;

void prn_cus(cus * head);
int revise_cus(cus * head);
int del_cus(cus * head);
int add_cus(cus * head);
int  user_info(cus * head);

int subscribe(mag * head_m, cus * head_c);

void save_m(mag * head);
void save_c(cus * head);
mag *px (mag *head);
int user(mag * head);
//********************************************************
//********************************************************
/*杂志排序*/
mag *px (mag *head)
{
	mag * p,* s;
	p = head -> next;
	while(p->next)
	{
		if(p -> dys >p -> next -> dys)
			s = p;
		else
			s = p -> next;
		
	}
} 


/*导入杂志信息*/
mag * load1(mag * head)
{
	FILE * fp;	
	fp = fopen("magazine.dat","r");
	while(!feof(fp))
	{
		mag * p = (mag *)malloc(sizeof(mag));
		fread(p,sizeof(mag),1,fp);
		
		if(feof(fp))
		{
			free(p);
			break;
		}
		
		p -> next = head -> next;
		head -> next = p;
	}
	fclose(fp);
	return head;
}

/*导入用户信息*/
cus * load2(cus * head)
{
	FILE * fp;	
	fp = fopen("user.dat","r");
	
	while(!feof(fp))
	{
		cus * p = (cus *)malloc(sizeof(cus));
		fread(p,sizeof(cus),1,fp);
		
		if(feof(fp))
		{
			free(p);
			break;
		}
		
		p -> next = head -> next;
		head -> next = p;
	}
	fclose(fp);
	return head;
}


/*管理员登录核对账号密码模块 */
int login()
{
	char ad[]={"admin"}; //管理员账号 
	char _ad[6];
	char password[]={"11111111"};//管理员密码 
	char pw[10];
	int i=0;
	
	printf("    管理员账号:");
	fflush(stdin);
	gets(_ad);
	printf("    密码:");
	fflush(stdin);
	while(i<10)
	{
		fflush(stdin);
		pw[i]=getch();
		if (pw[i] == '\r') break;  
		if (pw[i] == '\b') 
		{ 
			i=i-1; 
			printf("\b \b"); 
		} 
		else 
		{
			i=i+1;
			printf("*");
		}
	}
		pw[i]='\0';
		printf("\n");
		
		if(strcmp(ad,_ad)!=0)
			return 0;//账号输入失败 
			
		if(strcmp(password,pw)==0)
			return 1;//登录成功 
		else
			return 0;//密码错误 
}

/*管理员功能模块*/
int admin(mag * head_m,cus * head_c)
{
	while(1)
	{
		system("cls");
		printf("    *****************************************************************\n");
		printf("    **                          1:订阅                             **\n");
		printf("    **                          2:杂志信息管理                     **\n");
		printf("    **                          3:客户信息管理                     **\n");
		printf("    **                          0:返回主菜单                       **\n");		
		printf("    *****************************************************************\n");
		printf("    请选择:");
		int x;
		scanf("%d",&x);
		switch(x)
		{
			case 1:subscribe(head_m,head_c);break;
			case 2:magazine_info(head_m);break;
			case 3:user_info(head_c);break;
			case 0:return 0;
			default:admin(head_m,head_c);	
		}
		printf("    ");
		system("pause");
		system("cls");
	}
}

/*管理员登录交互模块*/ 
int administrators(mag * head_m,cus * head_c)
{
	int op=0;
	system("cls");
	printf("    *****************************************************************\n");

	op=login();//输入账号密码并进行验证 
	
	if(op==1)//登录成功 
	{
		
		printf("                                                                     \n");
		printf("                                                                     \n");
		printf("    *****************************************************************\n");
		printf("    **                            wellcome!!                       **\n");
		printf("    **                          管理员登录成功！                   **\n");
		printf("    *****************************************************************\n"); 
		admin(head_m,head_c);
	}
	
	if(op==0)//登录失败 
	{
		char sure;
		printf("    *****************************************************************\n");
		printf("    **                            登录失败！                       **\n");
		printf("    **                         账号或密码错误                      **\n"); 
		printf("    *****************************************************************\n");
		printf("    **                         任意键返回登录                      **\n"); 
		printf("    **                         0：返回主菜单                       **\n");
		printf("    *****************************************************************\n");
		printf("    ");
		
		fflush(stdin);
		scanf("%c",&sure);
			
	
		if(sure=='0')
		{
			return 0;
		}
		else
		{
			administrators(head_m,head_c);
		}		
	}
}

/*客户信息添加*/ 
int add_cus(cus * head)
{
	cus * p = (cus *)malloc(sizeof(cus));
	system("cls");
	printf("    *****************************************************************\n");
	printf("    **                           添加客户信息                      **\n"); 	
	printf("    *****************************************************************\n");
	printf("    名字:");
	scanf("%s",p -> name);
	printf("    电话:");
	scanf("%s",p -> pnb);
	p -> num = 0;//订阅数初始为0 

	p -> next = head -> next;
	head -> next = p;
	
	save_c(head);//存盘 
	
	printf("    *************************添加成功！******************************\n");
	printf("\n");
	printf("    ---------------------是否继续添加？ y/n-------------------------- ");
	fflush(stdin);
	if(getchar()=='y')
		add_cus(head);
	else
		return 1;
}

/*遍历客户*/ 
void prn_cus(cus * head) 
{
	cus * p;
	p = head -> next; 
	printf("    ************************************************\n");
	printf("    名字          联系方式         订阅数\n"); 
	while(p)
	{
		printf("    %-13s", p -> name);
		printf("%-20s", p -> pnb);
		printf("%d", p -> num);
		p = p -> next;
		printf("\n"); 
	}
}

/*查找客户*/
int search_cus(cus * head)
{
	int i = 0;
	cus * p = head -> next;
	printf("    *****************************************************************\n");
	printf("    输入查询的姓名:");
	char name[10];
	scanf("%s",name);
	while(p)
	{
		if(strcmp(p -> name, name) == 0)
		{
			printf("    名字          联系方式         订阅数\n"); 
			printf("    %-13s", p -> name);
			printf("%-20s", p -> pnb);
			printf("%d\n", p -> num);
			i++;
		}
		
		p = p -> next;		
	}
	if(i == 0)
	{
		printf("                               对不起，未找到！\n");
	}
	return 0;
} 

/*修改客户信息*/ 
int revise_cus(cus * head)
{
	system("cls");
	printf("    *****************************************************************\n");
	printf("    输入想要修改的客户名称：");
	char name[10]; 
	scanf("%s",name);
	cus * p = head -> next;
	while(p)
	{
		if(strcmp(name,p -> name) == 0)
		{
			printf("    ************************************************\n");
	        printf("    名字          联系方式         订阅数\n"); 
			printf("    %-13s", p -> name);
			printf("%-20s", p -> pnb);
			printf("%d\n", p -> num);
			printf("    -------------------------是否修改? y/n---------------------------");
			fflush(stdin);
			if(getchar()=='y')
			{
				int x;
				while(1)
				{
					printf("    *****************************************************************\n");
					printf("    **                          1:修改客户名字                     **\n");
					printf("    **                          2:修改客户联系方式                 **\n");
					printf("    **                          0:返回上一级                       **\n");		
					printf("    *****************************************************************\n");
					printf("    -----------------------------------------------------------------\n");
					printf("    请选择:");
					scanf("%d",&x);
					switch(x)
					{
						case 1:{
							printf("    输入更改后的名字：");
							scanf("%s",p -> name);
							save_c(head);
							printf("    *************************修改成功！******************************\n");
							printf("    名字          联系方式         订阅数\n"); 
							printf("    %-13s", p -> name);
							printf("%-20s", p -> pnb);
							printf("%d\n", p -> num);
							break;
						}
						case 2:{
							printf("    输入更改后的联系方式：");
							scanf("%s", p -> pnb);
							save_c(head);
							printf("    *************************修改成功！******************************\n");
							printf("    名字          联系方式         订阅数\n"); 
							printf("    %-13s", p -> name);
							printf("%-20s", p -> pnb);
							printf("%d\n", p -> num);
							break;
						}				
						case 0:{
							return 0;
							break;
						}
					}
					
				}
			}
			else
			{
				printf("    -------------------------取消修改-------------------------------\n");
				return 0;
			}	
		}
		p = p -> next; 
		if(p == NULL)
		{
			printf("    --------------------修改失败！未找到该词-------------------------\n");
			printf("    ---------------------是否继续修改？ y/n-------------------------- ");
			fflush(stdin);			
			if(getchar()=='y')
				revise_cus(head);
			else
				return 0;
		}
	}
}
/*删除客户信息*/
int del_cus(cus * head)
{
	printf("    想删除的客户姓名：");
	char name[10]; 
	scanf("%s",name); 
	cus * p = head -> next;
	cus * s = head;
	while(p)
	{
		if(strcmp(name,p -> name) == 0)
		{
			printf("    -------------------------是否删除? y/n---------------------------");
			fflush(stdin);
			if(getchar()=='y')
			{
				s -> next = p -> next;
				free(p);
				save_c(head);//及时存盘 
				printf("    *************************删除成功！******************************\n");
				printf("\n");
				printf("    ---------------------是否继续删除？ y/n-------------------------- ");
				fflush(stdin);
				if(getchar()=='y')
					del_cus(head);
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
				del_cus(head);
			else
				return 0;
		}
	}
}

/*客户管理模块*/
int  user_info(cus * head)
{
	while(1)
	{
		system("cls");
		printf("    *****************************************************************\n");
		printf("    **                           客户信息管理                      **\n"); 
		printf("    *****************************************************************\n");
		printf("    **                          1:浏览全部客户                     **\n");
		printf("    **                          2:查询客户                         **\n");
		printf("    **                          3:添加客户                         **\n");
		printf("    **                          4:修改客户信息                     **\n");
		printf("    **                          5:删除客户                         **\n");
		printf("    **                          0:返回主菜单                       **\n");		
		printf("    *****************************************************************\n");
		printf("    请选择:");
		int x;
		scanf("%d",&x);
		switch(x)
		{
			case 1:prn_cus(head);break;
			case 2:search_cus(head);break;
			case 3:add_cus(head);break;
			case 4:revise_cus(head);break;
			case 5:del_cus(head);break;
			case 0:return 0;
		}
		printf("    ");
		system("pause");
		system("cls");
	}	
}

/*遍历杂志*/ 
void prn_mag(mag * head) 
{
	mag * p;
	p = head -> next; 
	printf("***********************************************************\n");
	printf("名字             编号        类型        定价        订阅数\n"); 
	while(p)
	{
		printf("%-16s", p -> name);
		printf("%-13s", p -> no);
		printf("%-12s", p -> type);
		printf("%-14.2f", p -> money);
		printf("%d", p -> dys);
		p = p -> next;
		printf("\n"); 
	}
}

/*杂志查询模块*/
int s_m_na(mag * head,char * name)      //杂志名字 找出与输入同名的杂志 
{
	mag * p = head -> next;
	int i = 0;
	printf("***********************************************************\n");
	printf("名字             编号        类型        定价        订阅数\n"); 
	while(p)
	{
		if(strcmp(p -> name, name) == 0)
		{
			
			printf("%-16s", p -> name);
			printf("%-13s", p -> no);
			printf("%-12s", p -> type);
			printf("%-14.2f", p -> money);
			printf("%d", p -> dys);
			printf("\n");
			i++;
		}
		p = p -> next;
	}
	if(i == 0)
	{
		printf("    ***********************************************************************\n");
		printf("                               对不起，未找到！\n");
	}
	return 0;
		
} 
int s_m_t(mag * head,char * type)		//杂志类型  找出与 输入同类型的杂志 
{
	mag * p = head -> next;
	int i = 0;
	printf("***********************************************************\n");
	printf("名字             编号        类型        定价        订阅数\n"); 
	while(p)
	{
		if(strcmp(p -> type, type) == 0)
		{
			
			printf("%-16s", p -> name);
			printf("%-13s", p -> no);
			printf("%-12s", p -> type);
			printf("%-14.2f", p -> money);
			printf("%d", p -> dys);
			printf("\n");
			i++;
		}
		p = p -> next;
	}
	if(i == 0)
	{
		printf("    ***********************************************************************\n");
		printf("                               对不起，未找到！\n");
	}
	return 0;
}
int s_m_m(mag * head,float money)		//杂志价格，列举出低于给出价格的 
{
	mag * p = head -> next;
	int i = 0;
	printf("***********************************************************\n");
	printf("名字             编号        类型        定价        订阅数\n"); 
	while(p)
	{
		if(money >= p -> money)
		{
			
			printf("%-16s", p -> name);
			printf("%-13s", p -> no);
			printf("%-12s", p -> type);
			printf("%-14.2f", p -> money);
			printf("%d", p -> dys);		
			printf("\n");
			i++;
		}
		p = p -> next;
	}
	if(i == 0)
	{
		printf("    ***********************************************************************\n");
		printf("                               对不起，未找到！\n");
	}
	return 0;
}
int s_m_no(mag * head,char * no)		//杂志编号 
{
	mag * p = head -> next;
	int i = 0;
	printf("***********************************************************\n");
	printf("名字             编号        类型        定价        订阅数\n"); 
	while(p)
	{
		if(strcmp(p -> no, no) == 0)
		{
			
			printf("%-16s", p -> name);
			printf("%-13s", p -> no);
			printf("%-12s", p -> type);
			printf("%-14.2f", p -> money);
			printf("%d\n", p -> dys);
			i++;
		}
		p = p -> next;
	}
	if(i == 0)
	{
		printf("    ***********************************************************************\n");
		printf("                               对不起，未找到！\n");
	}
	return 0;
}

/*杂志查询界面模块*/
int search_mag(mag * head)
{
	
	while(1)
	{
		system("cls");
		printf("    *****************************************************************\n");
		printf("    **                          1:按杂志名字查询                   **\n");
		printf("    **                          2:按杂志类型查询                   **\n");
		printf("    **                          3:按杂志价格查询                   **\n");
		printf("    **                          4:按杂志编号查询                   **\n");
		printf("    **                          0:返回上一层                       **\n");
		printf("    *****************************************************************\n");
		printf("    请选择:");
		int x;
		scanf("%d",&x);
		switch(x)
		{
			case 1:{
				printf("    输入查询的名字:");
				char name[40];
				scanf("%s",name);
				system("cls");
				s_m_na(head,name);
				break;
			}
			case 2:{
				printf("    输入查询的类型:");
				char type[10];
				scanf("%s",type);	
				system("cls");		
				s_m_t(head,type);
				break;
			}
			case 3:{
				printf("    输入查询的价格最大值:");
				float money;
				scanf("%f",&money);
				system("cls");
				s_m_m(head,money);
				break;
			}
			case 4:{
				printf("    输入查询的编号:");
				char no[7];
				scanf("%s",no);	
				system("cls");		
				s_m_no(head,no);
				break;
			}
			case 0:{
				return 0;
				break;
			}
		}
		printf("    ");
		system("pause");
		system("cls");
	}
}

/*信息存盘*/ 
void save_m(mag * head)//杂志 
{
	FILE * fp;	
	fp = fopen("magazine.dat","w");
	mag * p = head -> next;
	while(p)
	{
		fwrite(p,sizeof(mag),1,fp);
		p = p -> next;
	}
	fclose(fp);
}

void save_c(cus * head)//客户 
{
	FILE * fp;	
	fp = fopen("user.dat","w");
	cus * p = head -> next;
	while(p)
	{
		fwrite(p,sizeof(cus),1,fp);
		p = p -> next;
	}
	fclose(fp);
}

/*添加杂志信息*/
int add_mag(mag * head)
{
	mag * p = (mag *)malloc(sizeof(mag));
	system("cls");
	printf("    *****************************************************************\n");
	printf("    **                           添加杂志信息                      **\n"); 	
	printf("    *****************************************************************\n");
	printf("    名字:");
	scanf("%s",p -> name);
	printf("    编号:");
	scanf("%s",p -> no);
	printf("    类型:");
	scanf("%s",p -> type);
	printf("    定价:");
	scanf("%f",&(p -> money));
	p -> dys = 0;
	
	p -> next = head -> next;
	head -> next = p;
	
	//head = px(head);         //及时排序 
	save_m(head);           //及时存盘 
	
	printf("    *************************添加成功！******************************\n");
	printf("\n");
	printf("    ---------------------是否继续添加？ y/n-------------------------- ");
	fflush(stdin);
	if(getchar()=='y')
		add_mag(head);
	else
		return 1;
} 

/*修改杂志信息*/ 
int revise_mag(mag * head)
{
	system("cls");
	printf("    *****************************************************************\n");
	printf("    输入想要修改的杂志编号：");
	char no[7]; 
	scanf("%s",no);
	mag * p = head -> next;
	while(p)
	{
		if(strcmp(no,p -> no) == 0)
		{
			printf("***********************************************************\n");
			printf("名字             编号        类型        定价        订阅数\n"); 
			printf("%-16s", p -> name);
			printf("%-13s", p -> no);
			printf("%-12s", p -> type);
			printf("%-14.2f", p -> money);
			printf("%d\n", p -> dys);
			printf("    -------------------------是否修改? y/n---------------------------");
			fflush(stdin);
			if(getchar()=='y')
			{
				int x;
				
				while(1)
				{
					printf("    *****************************************************************\n");
					printf("    **                          1:修改杂志名字                     **\n");
					printf("    **                          2:修改杂志编号                     **\n");
					printf("    **                          3:修改杂志类型                     **\n");
					printf("    **                          4:修改杂志价格                     **\n");
					printf("    **                          0:返回上一级                       **\n");		
					printf("    *****************************************************************\n");
					printf("    -----------------------------------------------------------------\n");
					printf("    请选择:");
					scanf("%d",&x);
					switch(x)
					{
						case 1:{
							printf("    输入更改后的名字：");
							scanf("%s",p -> name);
							
							save_m(head);            // 及时存盘 
							printf("    *************************修改成功！******************************\n");
							printf("名字             编号        类型        定价        订阅数\n"); 
							printf("%-16s", p -> name);
							printf("%-13s", p -> no);
							printf("%-12s", p -> type);
							printf("%-14.2f", p -> money);
							printf("%d\n", p -> dys);
		
							break;
						}
						case 2:{
							printf("    输入更改后的编号：");
							scanf("%s", p -> no);
							
							save_m(head);            // 及时存盘 
						
							printf("    *************************修改成功！******************************\n");
							printf("名字             编号        类型        定价        订阅数 \n"); 
							printf("%-16s", p -> name);
							printf("%-13s", p -> no);
							printf("%-12s", p -> type);
							printf("%-14.2f", p -> money);
							printf("%d\n", p -> dys);
						
							break;
						}
						case 3:{
							printf("    输入更改后的类型：");
							scanf("%s", p -> type);
							save_m(head);// 及时存盘 
							printf("    *************************修改成功！******************************\n");
							printf("名字             编号        类型        定价        订阅数\n"); 
							printf("%-16s", p -> name);
							printf("%-13s", p -> no);
							printf("%-12s", p -> type);
							printf("%-14.2f", p -> money);
							printf("%d\n", p -> dys);
						
							break;
						}
						case 4:{
							printf("    输入更改后的价格：");
							scanf("%f", p -> money);
							save_m(head);// 及时存盘 
							printf("    *************************修改成功！******************************\n");
							printf("名字             编号        类型        定价        订阅数\n"); 
							printf("%-16s", p -> name);
							printf("%-13s", p -> no);
							printf("%-12s", p -> type);
							printf("%-14.2f", p -> money);
							printf("%d\n", p -> dys);
					
							break;
						}
					
						case 0:{
							return 0;
							break;
						}
					}
				}
			}
			else
			{
				printf("    -------------------------取消修改-------------------------------\n");
				return 0;
			}	
		}
		p = p -> next; 
		if(p == NULL)
		{
			printf("    --------------------修改失败！未找到该词-------------------------\n");
			printf("    ---------------------是否继续修改？ y/n-------------------------- ");
			fflush(stdin);			
			if(getchar()=='y')
				revise_mag(head);
			else
				return 0;
		}
	}
}

/*删除杂志信息*/
int del_mag(mag * head)
{
	system("cls");
	printf("    *****************************************************************\n");
	printf("    想删除的杂志编号：");
	char no[7]; 
	scanf("%s",no); 
	mag * p = head -> next;
	mag * s = head;
	while(p)
	{
		if(strcmp(no,p -> no) == 0)
		{
			printf("    -------------------------是否删除? y/n---------------------------");
			fflush(stdin);
			if(getchar()=='y')
			{
				s -> next = p -> next;
				free(p);
				save_m(head);            //及时存盘 
				printf("    *************************删除成功！******************************\n");
				printf("\n");
				printf("    ---------------------是否继续删除？ y/n-------------------------- ");
				fflush(stdin);
				if(getchar()=='y')
					del_mag(head);
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
				del_mag(head);
			else
				return 0;
		}
	}
}

/*杂志管理模块*/
int magazine_info(mag * head)
{
	while(1)
	{
		system("cls");
		printf("    *****************************************************************\n");
		printf("    **                           杂志信息管理                      **\n"); 
		printf("    *****************************************************************\n");
		printf("    **                          1:浏览全部杂志                     **\n");
		printf("    **                          2:查询杂志                         **\n");
		printf("    **                          3:添加杂志                         **\n");
		printf("    **                          4:修改杂志信息                     **\n");
		printf("    **                          5:删除杂志                         **\n");
		printf("    **                          0:返回上一级                       **\n");		
		printf("    *****************************************************************\n");
		printf("    请选择:");
		int x;
		scanf("%d",&x);
		switch(x)
		{
			case 1:prn_mag(head);break;
			case 2:search_mag(head);break;
			case 3:add_mag(head);break;
			case 4:revise_mag(head);break;
			case 5:del_mag(head);break;
			case 0:return 0;
		}
		printf("    ");
		system("pause");
		system("cls");
	}	
}

/*订阅交互模块*/
int subscribe(mag * head_m, cus * head_c) 
{
	while(1)
	{
		
		system("cls");
		printf("    *****************************************************************\n");
		printf("    **                           订阅杂志                          **\n"); 
		printf("    *****************************************************************\n");
		printf("    **                           1:订阅                            **\n");
		printf("    **                           2:退订                            **\n");
		printf("    **                           0:返回上一级                      **\n");
		printf("    *****************************************************************\n");
		printf("    请选择:");
		int x;
		scanf("%d",&x);
		switch(x)
		{
			case 1:{
				dy(head_m,head_c);
				break;
			}
			case 2:{
				td(head_m,head_c);
				break;
			}
			case 0:{
				return 0;
				break;
			}
		}
		printf("    ");
		system("pause");
		system("cls");
	}
}

/*退订模块 */
int td(mag * head_m, cus * head_c)
{
	system("cls");
	char no[7]; 
	printf("    请输入要退订的杂志编号:");
	scanf("%s",no); 
	mag * p = head_m -> next;
	while(p)
	{
		if(strcmp(no,p -> no) == 0&&p -> dys != 0)
		{
			printf("***********************************************************\n");
			printf("名字             编号        类型        定价        订阅数\n"); 
			printf("%-16s", p -> name);
			printf("%-13s", p -> no);
			printf("%-12s", p -> type);
			printf("%-14.2f", p -> money);
			printf("%d\n", p -> dys);
			
			printf("    请输入要退订的客户姓名:");
			char name[10];
			scanf("%s",name);
			cus * s = head_c -> next;
			while(s)
			{
				if(strcmp(s -> name, name) == 0&&s -> num != 0)
				{
					p -> dys--;
					s -> num--;
					
					//head_m= px(head_m);         //及时排序 
					save_m(head_m);			//及时存盘 
					save_c(head_c);			//及时存盘 
					printf("    -------------------------退订成功！-------------------------\n");
					return 0;
				}
				s = s -> next;
				if(s == NULL)
				{
					printf("    ---------------------退订失败！未找到该客户或者该客户没订阅-----\n");
					printf("    ---------------------是否继续退订？ y/n-------------------------- ");
					fflush(stdin);			
					if(getchar()=='y')
						td(head_m,head_c);
					else
						return 0;
				}
			}
		}
		p = p -> next;
		if(p == NULL)
		{
			printf("    ---------------------退订失败！未找到该杂志或者该杂志没订阅-----\n");
			printf("    ---------------------是否继续退订？ y/n-------------------------- ");
			fflush(stdin);			
			if(getchar()=='y')
				td(head_m,head_c);
			else
				return 0;
		}
	}
} 

/*订阅模块 */
int dy(mag * head_m, cus * head_c)
{
	system("cls");
	char no[7]; 
	printf("    请输入要订阅的杂志编号:");
	scanf("%s",no); 
	mag * p = head_m -> next;
	while(p)
	{
		if(strcmp(no,p -> no) == 0)
		{
			printf("***********************************************************\n");
			printf("名字             编号        类型        定价        订阅数\n"); 
			printf("%-16s", p -> name);
			printf("%-13s", p -> no);
			printf("%-12s", p -> type);
			printf("%-14.2f", p -> money);
			printf("%d\n", p -> dys);
			printf("    请输入要订阅的客户姓名:");
			char name[10];
			scanf("%s",name);
			cus * s = head_c -> next;
			while(s)
			{
				if(strcmp(s -> name, name) == 0)
				{
					p -> dys++;
					s -> num++;
					//head_m = px(head_m);         //及时排序 
					save_m(head_m);			// 及时存盘 
					save_c(head_c);			//及时存盘 
					printf("    -------------------------订阅成功！-------------------------\n");
					return 0; 
				}
				s = s -> next;
				if(s == NULL)
				{
					printf("    --------------------订阅失败！未找到该客户-----------------------\n");
					printf("    ---------------------是否继续订阅？ y/n-------------------------- ");
					fflush(stdin);			
					if(getchar()=='y')
						dy(head_m,head_c);
					else
						return 0;
				}
			}
		}
		p = p -> next;
		if(p == NULL)
		{
			printf("    --------------------订阅失败！未找到该杂志-----------------------\n");
			printf("    ---------------------是否继续订阅？ y/n-------------------------- ");
			fflush(stdin);			
			if(getchar()=='y')
				dy(head_m,head_c);
			else
				return 0;
		}
	}
	
} 

/*用户登录交互模块*/
int user(mag * head)
{
	int x;
	
	while(1)
	{
		system("cls");
		printf("                                                                     \n");
		printf("                                                                     \n");
		printf("    *****************************************************************\n");
		printf("    **                        普通用户登录成功！                   **\n");
		printf("    *****************************************************************\n");
		printf("    **                          1:查询杂志                         **\n");
		printf("    **                          0:返回主菜单                       **\n");
		printf("    *****************************************************************\n");
		printf("    请选择：");
		scanf("%d",&x);
		switch(x)
		{	
			case 1:search_mag(head);break;
			case 0:return 0;break;
			default :break;
		}
		printf("    ");
		system("pause");
		system("cls");
	}
}

/*释放链表*/ 
void m_free(mag * head)
{
	mag *current=head->next;
	mag *tmp;
	while(current)
	{
		tmp=current->next; 
		free(current);
		current=tmp;
	}
}
void c_free(cus * head)
{
	cus *current=head->next;
	cus *tmp;
	while(current)
	{
		tmp=current->next; 
		free(current);
		current=tmp;
	}
}

/*主函数*/ 
int main()
{
	mag * head_m = (mag *)malloc(sizeof(mag));;
	cus * head_c = (cus *)malloc(sizeof(cus));;
	head_m -> next = NULL;
	head_c -> next = NULL;
	
	head_c = load2(head_c);//载入客户信息 
	head_m = load1(head_m);//载入杂志信息 
	//head_m = px(head_m);         //起始排序 
	int x;
	while(1)
	{
		
		printf("                                                                     \n");
		printf("                                                                     \n");
		printf("    *****************************************************************\n");
		printf("    **                            wellcome!!                       **\n");
		printf("    *****************************************************************\n");
		printf("    **                          1：管理员登录                      **\n");
		printf("    **                          2: 用户登录                        **\n");
		printf("    **                          0: 退出系统                        **\n");
		printf("    *****************************************************************\n");
		printf("    请选择:");
		scanf("%d",&x);getchar(); 
		switch(x)
		{
			case 1:administrators(head_m,head_c);break;//管理员登录 
			case 2:user(head_m);break;//普通用户登录 
			case 0:{
				m_free(head_m);
				free(head_m);
				c_free(head_c);
				free(head_c);
				printf("    *****************************************************************\n");
				printf("    **                         谢谢使用！                          **\n");
				printf("    **                         制作者：郭鑫                        **\n");
				printf("    *****************************************************************\n");
				printf("    ");
				system("pause");				
				exit(0);
				;break;
			}
			default:printf("    ---------------------输入错误！重新输入--------------------------\n");break; 
		}
		printf("    ");
		system("pause");
		system("cls");
	}
}
