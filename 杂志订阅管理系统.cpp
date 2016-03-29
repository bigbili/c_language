#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct customer//�ͻ���Ϣ�ṹ�� 
{
	char name[10];//����
	int num ;//���˼�����
	char pnb[12];//��ϵ�绰 
	struct customer * next;
	
}cus;

typedef struct magazine//��־��Ϣ�Ľṹ��
{
	char name[40];//����
	char no[7];//���6λ
	char type[10];//����
	float money;//���� 
	int dys;//������
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
/*��־����*/
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


/*������־��Ϣ*/
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

/*�����û���Ϣ*/
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


/*����Ա��¼�˶��˺�����ģ�� */
int login()
{
	char ad[]={"admin"}; //����Ա�˺� 
	char _ad[6];
	char password[]={"11111111"};//����Ա���� 
	char pw[10];
	int i=0;
	
	printf("    ����Ա�˺�:");
	fflush(stdin);
	gets(_ad);
	printf("    ����:");
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
			return 0;//�˺�����ʧ�� 
			
		if(strcmp(password,pw)==0)
			return 1;//��¼�ɹ� 
		else
			return 0;//������� 
}

/*����Ա����ģ��*/
int admin(mag * head_m,cus * head_c)
{
	while(1)
	{
		system("cls");
		printf("    *****************************************************************\n");
		printf("    **                          1:����                             **\n");
		printf("    **                          2:��־��Ϣ����                     **\n");
		printf("    **                          3:�ͻ���Ϣ����                     **\n");
		printf("    **                          0:�������˵�                       **\n");		
		printf("    *****************************************************************\n");
		printf("    ��ѡ��:");
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

/*����Ա��¼����ģ��*/ 
int administrators(mag * head_m,cus * head_c)
{
	int op=0;
	system("cls");
	printf("    *****************************************************************\n");

	op=login();//�����˺����벢������֤ 
	
	if(op==1)//��¼�ɹ� 
	{
		
		printf("                                                                     \n");
		printf("                                                                     \n");
		printf("    *****************************************************************\n");
		printf("    **                            wellcome!!                       **\n");
		printf("    **                          ����Ա��¼�ɹ���                   **\n");
		printf("    *****************************************************************\n"); 
		admin(head_m,head_c);
	}
	
	if(op==0)//��¼ʧ�� 
	{
		char sure;
		printf("    *****************************************************************\n");
		printf("    **                            ��¼ʧ�ܣ�                       **\n");
		printf("    **                         �˺Ż��������                      **\n"); 
		printf("    *****************************************************************\n");
		printf("    **                         ��������ص�¼                      **\n"); 
		printf("    **                         0���������˵�                       **\n");
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

/*�ͻ���Ϣ���*/ 
int add_cus(cus * head)
{
	cus * p = (cus *)malloc(sizeof(cus));
	system("cls");
	printf("    *****************************************************************\n");
	printf("    **                           ��ӿͻ���Ϣ                      **\n"); 	
	printf("    *****************************************************************\n");
	printf("    ����:");
	scanf("%s",p -> name);
	printf("    �绰:");
	scanf("%s",p -> pnb);
	p -> num = 0;//��������ʼΪ0 

	p -> next = head -> next;
	head -> next = p;
	
	save_c(head);//���� 
	
	printf("    *************************��ӳɹ���******************************\n");
	printf("\n");
	printf("    ---------------------�Ƿ������ӣ� y/n-------------------------- ");
	fflush(stdin);
	if(getchar()=='y')
		add_cus(head);
	else
		return 1;
}

/*�����ͻ�*/ 
void prn_cus(cus * head) 
{
	cus * p;
	p = head -> next; 
	printf("    ************************************************\n");
	printf("    ����          ��ϵ��ʽ         ������\n"); 
	while(p)
	{
		printf("    %-13s", p -> name);
		printf("%-20s", p -> pnb);
		printf("%d", p -> num);
		p = p -> next;
		printf("\n"); 
	}
}

/*���ҿͻ�*/
int search_cus(cus * head)
{
	int i = 0;
	cus * p = head -> next;
	printf("    *****************************************************************\n");
	printf("    �����ѯ������:");
	char name[10];
	scanf("%s",name);
	while(p)
	{
		if(strcmp(p -> name, name) == 0)
		{
			printf("    ����          ��ϵ��ʽ         ������\n"); 
			printf("    %-13s", p -> name);
			printf("%-20s", p -> pnb);
			printf("%d\n", p -> num);
			i++;
		}
		
		p = p -> next;		
	}
	if(i == 0)
	{
		printf("                               �Բ���δ�ҵ���\n");
	}
	return 0;
} 

/*�޸Ŀͻ���Ϣ*/ 
int revise_cus(cus * head)
{
	system("cls");
	printf("    *****************************************************************\n");
	printf("    ������Ҫ�޸ĵĿͻ����ƣ�");
	char name[10]; 
	scanf("%s",name);
	cus * p = head -> next;
	while(p)
	{
		if(strcmp(name,p -> name) == 0)
		{
			printf("    ************************************************\n");
	        printf("    ����          ��ϵ��ʽ         ������\n"); 
			printf("    %-13s", p -> name);
			printf("%-20s", p -> pnb);
			printf("%d\n", p -> num);
			printf("    -------------------------�Ƿ��޸�? y/n---------------------------");
			fflush(stdin);
			if(getchar()=='y')
			{
				int x;
				while(1)
				{
					printf("    *****************************************************************\n");
					printf("    **                          1:�޸Ŀͻ�����                     **\n");
					printf("    **                          2:�޸Ŀͻ���ϵ��ʽ                 **\n");
					printf("    **                          0:������һ��                       **\n");		
					printf("    *****************************************************************\n");
					printf("    -----------------------------------------------------------------\n");
					printf("    ��ѡ��:");
					scanf("%d",&x);
					switch(x)
					{
						case 1:{
							printf("    ������ĺ�����֣�");
							scanf("%s",p -> name);
							save_c(head);
							printf("    *************************�޸ĳɹ���******************************\n");
							printf("    ����          ��ϵ��ʽ         ������\n"); 
							printf("    %-13s", p -> name);
							printf("%-20s", p -> pnb);
							printf("%d\n", p -> num);
							break;
						}
						case 2:{
							printf("    ������ĺ����ϵ��ʽ��");
							scanf("%s", p -> pnb);
							save_c(head);
							printf("    *************************�޸ĳɹ���******************************\n");
							printf("    ����          ��ϵ��ʽ         ������\n"); 
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
				printf("    -------------------------ȡ���޸�-------------------------------\n");
				return 0;
			}	
		}
		p = p -> next; 
		if(p == NULL)
		{
			printf("    --------------------�޸�ʧ�ܣ�δ�ҵ��ô�-------------------------\n");
			printf("    ---------------------�Ƿ�����޸ģ� y/n-------------------------- ");
			fflush(stdin);			
			if(getchar()=='y')
				revise_cus(head);
			else
				return 0;
		}
	}
}
/*ɾ���ͻ���Ϣ*/
int del_cus(cus * head)
{
	printf("    ��ɾ���Ŀͻ�������");
	char name[10]; 
	scanf("%s",name); 
	cus * p = head -> next;
	cus * s = head;
	while(p)
	{
		if(strcmp(name,p -> name) == 0)
		{
			printf("    -------------------------�Ƿ�ɾ��? y/n---------------------------");
			fflush(stdin);
			if(getchar()=='y')
			{
				s -> next = p -> next;
				free(p);
				save_c(head);//��ʱ���� 
				printf("    *************************ɾ���ɹ���******************************\n");
				printf("\n");
				printf("    ---------------------�Ƿ����ɾ���� y/n-------------------------- ");
				fflush(stdin);
				if(getchar()=='y')
					del_cus(head);
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
				del_cus(head);
			else
				return 0;
		}
	}
}

/*�ͻ�����ģ��*/
int  user_info(cus * head)
{
	while(1)
	{
		system("cls");
		printf("    *****************************************************************\n");
		printf("    **                           �ͻ���Ϣ����                      **\n"); 
		printf("    *****************************************************************\n");
		printf("    **                          1:���ȫ���ͻ�                     **\n");
		printf("    **                          2:��ѯ�ͻ�                         **\n");
		printf("    **                          3:��ӿͻ�                         **\n");
		printf("    **                          4:�޸Ŀͻ���Ϣ                     **\n");
		printf("    **                          5:ɾ���ͻ�                         **\n");
		printf("    **                          0:�������˵�                       **\n");		
		printf("    *****************************************************************\n");
		printf("    ��ѡ��:");
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

/*������־*/ 
void prn_mag(mag * head) 
{
	mag * p;
	p = head -> next; 
	printf("***********************************************************\n");
	printf("����             ���        ����        ����        ������\n"); 
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

/*��־��ѯģ��*/
int s_m_na(mag * head,char * name)      //��־���� �ҳ�������ͬ������־ 
{
	mag * p = head -> next;
	int i = 0;
	printf("***********************************************************\n");
	printf("����             ���        ����        ����        ������\n"); 
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
		printf("                               �Բ���δ�ҵ���\n");
	}
	return 0;
		
} 
int s_m_t(mag * head,char * type)		//��־����  �ҳ��� ����ͬ���͵���־ 
{
	mag * p = head -> next;
	int i = 0;
	printf("***********************************************************\n");
	printf("����             ���        ����        ����        ������\n"); 
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
		printf("                               �Բ���δ�ҵ���\n");
	}
	return 0;
}
int s_m_m(mag * head,float money)		//��־�۸��оٳ����ڸ����۸�� 
{
	mag * p = head -> next;
	int i = 0;
	printf("***********************************************************\n");
	printf("����             ���        ����        ����        ������\n"); 
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
		printf("                               �Բ���δ�ҵ���\n");
	}
	return 0;
}
int s_m_no(mag * head,char * no)		//��־��� 
{
	mag * p = head -> next;
	int i = 0;
	printf("***********************************************************\n");
	printf("����             ���        ����        ����        ������\n"); 
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
		printf("                               �Բ���δ�ҵ���\n");
	}
	return 0;
}

/*��־��ѯ����ģ��*/
int search_mag(mag * head)
{
	
	while(1)
	{
		system("cls");
		printf("    *****************************************************************\n");
		printf("    **                          1:����־���ֲ�ѯ                   **\n");
		printf("    **                          2:����־���Ͳ�ѯ                   **\n");
		printf("    **                          3:����־�۸��ѯ                   **\n");
		printf("    **                          4:����־��Ų�ѯ                   **\n");
		printf("    **                          0:������һ��                       **\n");
		printf("    *****************************************************************\n");
		printf("    ��ѡ��:");
		int x;
		scanf("%d",&x);
		switch(x)
		{
			case 1:{
				printf("    �����ѯ������:");
				char name[40];
				scanf("%s",name);
				system("cls");
				s_m_na(head,name);
				break;
			}
			case 2:{
				printf("    �����ѯ������:");
				char type[10];
				scanf("%s",type);	
				system("cls");		
				s_m_t(head,type);
				break;
			}
			case 3:{
				printf("    �����ѯ�ļ۸����ֵ:");
				float money;
				scanf("%f",&money);
				system("cls");
				s_m_m(head,money);
				break;
			}
			case 4:{
				printf("    �����ѯ�ı��:");
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

/*��Ϣ����*/ 
void save_m(mag * head)//��־ 
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

void save_c(cus * head)//�ͻ� 
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

/*�����־��Ϣ*/
int add_mag(mag * head)
{
	mag * p = (mag *)malloc(sizeof(mag));
	system("cls");
	printf("    *****************************************************************\n");
	printf("    **                           �����־��Ϣ                      **\n"); 	
	printf("    *****************************************************************\n");
	printf("    ����:");
	scanf("%s",p -> name);
	printf("    ���:");
	scanf("%s",p -> no);
	printf("    ����:");
	scanf("%s",p -> type);
	printf("    ����:");
	scanf("%f",&(p -> money));
	p -> dys = 0;
	
	p -> next = head -> next;
	head -> next = p;
	
	//head = px(head);         //��ʱ���� 
	save_m(head);           //��ʱ���� 
	
	printf("    *************************��ӳɹ���******************************\n");
	printf("\n");
	printf("    ---------------------�Ƿ������ӣ� y/n-------------------------- ");
	fflush(stdin);
	if(getchar()=='y')
		add_mag(head);
	else
		return 1;
} 

/*�޸���־��Ϣ*/ 
int revise_mag(mag * head)
{
	system("cls");
	printf("    *****************************************************************\n");
	printf("    ������Ҫ�޸ĵ���־��ţ�");
	char no[7]; 
	scanf("%s",no);
	mag * p = head -> next;
	while(p)
	{
		if(strcmp(no,p -> no) == 0)
		{
			printf("***********************************************************\n");
			printf("����             ���        ����        ����        ������\n"); 
			printf("%-16s", p -> name);
			printf("%-13s", p -> no);
			printf("%-12s", p -> type);
			printf("%-14.2f", p -> money);
			printf("%d\n", p -> dys);
			printf("    -------------------------�Ƿ��޸�? y/n---------------------------");
			fflush(stdin);
			if(getchar()=='y')
			{
				int x;
				
				while(1)
				{
					printf("    *****************************************************************\n");
					printf("    **                          1:�޸���־����                     **\n");
					printf("    **                          2:�޸���־���                     **\n");
					printf("    **                          3:�޸���־����                     **\n");
					printf("    **                          4:�޸���־�۸�                     **\n");
					printf("    **                          0:������һ��                       **\n");		
					printf("    *****************************************************************\n");
					printf("    -----------------------------------------------------------------\n");
					printf("    ��ѡ��:");
					scanf("%d",&x);
					switch(x)
					{
						case 1:{
							printf("    ������ĺ�����֣�");
							scanf("%s",p -> name);
							
							save_m(head);            // ��ʱ���� 
							printf("    *************************�޸ĳɹ���******************************\n");
							printf("����             ���        ����        ����        ������\n"); 
							printf("%-16s", p -> name);
							printf("%-13s", p -> no);
							printf("%-12s", p -> type);
							printf("%-14.2f", p -> money);
							printf("%d\n", p -> dys);
		
							break;
						}
						case 2:{
							printf("    ������ĺ�ı�ţ�");
							scanf("%s", p -> no);
							
							save_m(head);            // ��ʱ���� 
						
							printf("    *************************�޸ĳɹ���******************************\n");
							printf("����             ���        ����        ����        ������ \n"); 
							printf("%-16s", p -> name);
							printf("%-13s", p -> no);
							printf("%-12s", p -> type);
							printf("%-14.2f", p -> money);
							printf("%d\n", p -> dys);
						
							break;
						}
						case 3:{
							printf("    ������ĺ�����ͣ�");
							scanf("%s", p -> type);
							save_m(head);// ��ʱ���� 
							printf("    *************************�޸ĳɹ���******************************\n");
							printf("����             ���        ����        ����        ������\n"); 
							printf("%-16s", p -> name);
							printf("%-13s", p -> no);
							printf("%-12s", p -> type);
							printf("%-14.2f", p -> money);
							printf("%d\n", p -> dys);
						
							break;
						}
						case 4:{
							printf("    ������ĺ�ļ۸�");
							scanf("%f", p -> money);
							save_m(head);// ��ʱ���� 
							printf("    *************************�޸ĳɹ���******************************\n");
							printf("����             ���        ����        ����        ������\n"); 
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
				printf("    -------------------------ȡ���޸�-------------------------------\n");
				return 0;
			}	
		}
		p = p -> next; 
		if(p == NULL)
		{
			printf("    --------------------�޸�ʧ�ܣ�δ�ҵ��ô�-------------------------\n");
			printf("    ---------------------�Ƿ�����޸ģ� y/n-------------------------- ");
			fflush(stdin);			
			if(getchar()=='y')
				revise_mag(head);
			else
				return 0;
		}
	}
}

/*ɾ����־��Ϣ*/
int del_mag(mag * head)
{
	system("cls");
	printf("    *****************************************************************\n");
	printf("    ��ɾ������־��ţ�");
	char no[7]; 
	scanf("%s",no); 
	mag * p = head -> next;
	mag * s = head;
	while(p)
	{
		if(strcmp(no,p -> no) == 0)
		{
			printf("    -------------------------�Ƿ�ɾ��? y/n---------------------------");
			fflush(stdin);
			if(getchar()=='y')
			{
				s -> next = p -> next;
				free(p);
				save_m(head);            //��ʱ���� 
				printf("    *************************ɾ���ɹ���******************************\n");
				printf("\n");
				printf("    ---------------------�Ƿ����ɾ���� y/n-------------------------- ");
				fflush(stdin);
				if(getchar()=='y')
					del_mag(head);
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
				del_mag(head);
			else
				return 0;
		}
	}
}

/*��־����ģ��*/
int magazine_info(mag * head)
{
	while(1)
	{
		system("cls");
		printf("    *****************************************************************\n");
		printf("    **                           ��־��Ϣ����                      **\n"); 
		printf("    *****************************************************************\n");
		printf("    **                          1:���ȫ����־                     **\n");
		printf("    **                          2:��ѯ��־                         **\n");
		printf("    **                          3:�����־                         **\n");
		printf("    **                          4:�޸���־��Ϣ                     **\n");
		printf("    **                          5:ɾ����־                         **\n");
		printf("    **                          0:������һ��                       **\n");		
		printf("    *****************************************************************\n");
		printf("    ��ѡ��:");
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

/*���Ľ���ģ��*/
int subscribe(mag * head_m, cus * head_c) 
{
	while(1)
	{
		
		system("cls");
		printf("    *****************************************************************\n");
		printf("    **                           ������־                          **\n"); 
		printf("    *****************************************************************\n");
		printf("    **                           1:����                            **\n");
		printf("    **                           2:�˶�                            **\n");
		printf("    **                           0:������һ��                      **\n");
		printf("    *****************************************************************\n");
		printf("    ��ѡ��:");
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

/*�˶�ģ�� */
int td(mag * head_m, cus * head_c)
{
	system("cls");
	char no[7]; 
	printf("    ������Ҫ�˶�����־���:");
	scanf("%s",no); 
	mag * p = head_m -> next;
	while(p)
	{
		if(strcmp(no,p -> no) == 0&&p -> dys != 0)
		{
			printf("***********************************************************\n");
			printf("����             ���        ����        ����        ������\n"); 
			printf("%-16s", p -> name);
			printf("%-13s", p -> no);
			printf("%-12s", p -> type);
			printf("%-14.2f", p -> money);
			printf("%d\n", p -> dys);
			
			printf("    ������Ҫ�˶��Ŀͻ�����:");
			char name[10];
			scanf("%s",name);
			cus * s = head_c -> next;
			while(s)
			{
				if(strcmp(s -> name, name) == 0&&s -> num != 0)
				{
					p -> dys--;
					s -> num--;
					
					//head_m= px(head_m);         //��ʱ���� 
					save_m(head_m);			//��ʱ���� 
					save_c(head_c);			//��ʱ���� 
					printf("    -------------------------�˶��ɹ���-------------------------\n");
					return 0;
				}
				s = s -> next;
				if(s == NULL)
				{
					printf("    ---------------------�˶�ʧ�ܣ�δ�ҵ��ÿͻ����߸ÿͻ�û����-----\n");
					printf("    ---------------------�Ƿ�����˶��� y/n-------------------------- ");
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
			printf("    ---------------------�˶�ʧ�ܣ�δ�ҵ�����־���߸���־û����-----\n");
			printf("    ---------------------�Ƿ�����˶��� y/n-------------------------- ");
			fflush(stdin);			
			if(getchar()=='y')
				td(head_m,head_c);
			else
				return 0;
		}
	}
} 

/*����ģ�� */
int dy(mag * head_m, cus * head_c)
{
	system("cls");
	char no[7]; 
	printf("    ������Ҫ���ĵ���־���:");
	scanf("%s",no); 
	mag * p = head_m -> next;
	while(p)
	{
		if(strcmp(no,p -> no) == 0)
		{
			printf("***********************************************************\n");
			printf("����             ���        ����        ����        ������\n"); 
			printf("%-16s", p -> name);
			printf("%-13s", p -> no);
			printf("%-12s", p -> type);
			printf("%-14.2f", p -> money);
			printf("%d\n", p -> dys);
			printf("    ������Ҫ���ĵĿͻ�����:");
			char name[10];
			scanf("%s",name);
			cus * s = head_c -> next;
			while(s)
			{
				if(strcmp(s -> name, name) == 0)
				{
					p -> dys++;
					s -> num++;
					//head_m = px(head_m);         //��ʱ���� 
					save_m(head_m);			// ��ʱ���� 
					save_c(head_c);			//��ʱ���� 
					printf("    -------------------------���ĳɹ���-------------------------\n");
					return 0; 
				}
				s = s -> next;
				if(s == NULL)
				{
					printf("    --------------------����ʧ�ܣ�δ�ҵ��ÿͻ�-----------------------\n");
					printf("    ---------------------�Ƿ�������ģ� y/n-------------------------- ");
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
			printf("    --------------------����ʧ�ܣ�δ�ҵ�����־-----------------------\n");
			printf("    ---------------------�Ƿ�������ģ� y/n-------------------------- ");
			fflush(stdin);			
			if(getchar()=='y')
				dy(head_m,head_c);
			else
				return 0;
		}
	}
	
} 

/*�û���¼����ģ��*/
int user(mag * head)
{
	int x;
	
	while(1)
	{
		system("cls");
		printf("                                                                     \n");
		printf("                                                                     \n");
		printf("    *****************************************************************\n");
		printf("    **                        ��ͨ�û���¼�ɹ���                   **\n");
		printf("    *****************************************************************\n");
		printf("    **                          1:��ѯ��־                         **\n");
		printf("    **                          0:�������˵�                       **\n");
		printf("    *****************************************************************\n");
		printf("    ��ѡ��");
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

/*�ͷ�����*/ 
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

/*������*/ 
int main()
{
	mag * head_m = (mag *)malloc(sizeof(mag));;
	cus * head_c = (cus *)malloc(sizeof(cus));;
	head_m -> next = NULL;
	head_c -> next = NULL;
	
	head_c = load2(head_c);//����ͻ���Ϣ 
	head_m = load1(head_m);//������־��Ϣ 
	//head_m = px(head_m);         //��ʼ���� 
	int x;
	while(1)
	{
		
		printf("                                                                     \n");
		printf("                                                                     \n");
		printf("    *****************************************************************\n");
		printf("    **                            wellcome!!                       **\n");
		printf("    *****************************************************************\n");
		printf("    **                          1������Ա��¼                      **\n");
		printf("    **                          2: �û���¼                        **\n");
		printf("    **                          0: �˳�ϵͳ                        **\n");
		printf("    *****************************************************************\n");
		printf("    ��ѡ��:");
		scanf("%d",&x);getchar(); 
		switch(x)
		{
			case 1:administrators(head_m,head_c);break;//����Ա��¼ 
			case 2:user(head_m);break;//��ͨ�û���¼ 
			case 0:{
				m_free(head_m);
				free(head_m);
				c_free(head_c);
				free(head_c);
				printf("    *****************************************************************\n");
				printf("    **                         ллʹ�ã�                          **\n");
				printf("    **                         �����ߣ�����                        **\n");
				printf("    *****************************************************************\n");
				printf("    ");
				system("pause");				
				exit(0);
				;break;
			}
			default:printf("    ---------------------���������������--------------------------\n");break; 
		}
		printf("    ");
		system("pause");
		system("cls");
	}
}
