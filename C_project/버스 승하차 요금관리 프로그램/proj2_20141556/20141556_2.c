#include<stdio.h>
#include<stdlib.h>
#include<string.h>
enum type{credit,charge}; 
typedef struct{
	int id;
	char name[21];
	int money;
	enum type cardtype;
	char type[6];
	int ride;
	float total_s;
}user;//customer 파일에서 가져온 사용자들 정보
typedef struct _node{
	int idnum;
	char method[7];
	int stationid;
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int transfer;
	int ride;//승하차 여부
	struct _node* link;
}NODE;//승하차 구현 리스트
typedef struct{
	int num;
	int stationid;
	char name[65];
	float s;
}b604_st;//버스 604번 DB
typedef struct{
	int num;
	int stationid;
	char name[65];
	float s;
}g5714_st;//버스 5714번 DB
typedef struct{
	int num;
	int stationid;
	char name[65];
	float s;
}t10_st;//버스 t10번 DB
typedef struct{
	int num;
	int stationid;
	char name[33];
	float s;
}sub3_st;//지하철 3호선 DB

NODE* head;

void addnode(int id,char* method,int stationid,int year,int month,int day,int hour,int minute,int transfer,int ride)//노드를 추가해주는 함수
{
	NODE* pnew;//새 노드 생성 후
	NODE* temp;
	pnew=(NODE*)malloc(sizeof(NODE));
	pnew->idnum=id;
	pnew->link=NULL;
	strcpy(pnew->method,method);
	pnew->stationid=stationid;
	pnew->year=year;
	pnew->month=month;
	pnew->day=day;
	pnew->hour=hour;
	pnew->minute=minute;
	pnew->transfer=transfer;
	pnew->ride=ride;// 여기까지 새 노드에 정보 입력
	temp=head;
	if(head==NULL)
	{
		
		head=pnew;
	
	}
	else
	{
	
		while(temp->link!=NULL)
		{
			temp=temp->link;
		}
		temp->link=pnew;
	}

//노드 추가
}

int main()
{	//여러가지 변수 설정
	int num,i,j,id,stationid,year,month,day,hour,minute,transfer,ride;
	int count;
	int transfer2[50];
	int idnum[50];
	int fee[50];

	int ontransfer[50];//환승 상태를 나타내는 변수
	//float total_s[50];
	char* method;
	char dump;
	char* card;
	int pre_s;
	int po_s;
	float real_s[50];
	head=NULL;
	NODE* temp;
	NODE* del;
	user* u;
	
	b604_st* b;//교통수단 구조체 변수 설정
	g5714_st* g;
	t10_st* t;
	sub3_st* subway;
	method=(char*)malloc(sizeof(char)*8);
	int bnum,gnum,tnum,snum;
	card=(char*)malloc(sizeof(char)*8);
	FILE* cus=fopen("customer.txt","r");
	FILE* fp2=fopen("customer.txt","r+");//업데이트 할 때 필요한 포인터	
	FILE* b604=fopen("bus_b604.txt","r");
	FILE* g5714=fopen("bus_g5714.txt","r");
	FILE* t10=fopen("bus_t10.txt","r");
	FILE* sub=fopen("subway_line3.txt","r");
	FILE* out=fopen("reader_output.txt","w");
	for(i=0;i<50;i++)
	{
		real_s[i]=0;
		fee[i]=0;
	}
	fscanf(cus,"%d",&num);//정보를 다 받는다 (customer.txt)와 여러 교통수단
	fscanf(cus,"%c",&dump);
	u=(user*)malloc(sizeof(user)*(num+1));
	
	fscanf(b604,"%d",&bnum);
	fscanf(b604,"%c",&dump);
	b=(b604_st*)malloc(sizeof(b604_st)*(bnum+1));
	fscanf(g5714,"%d",&gnum);
	fscanf(g5714,"%c",&dump);
	g=(g5714_st*)malloc(sizeof(g5714_st)*(gnum+1));	
	fscanf(t10,"%d",&tnum);
	fscanf(t10,"%c",&dump);
	t=(t10_st*)malloc(sizeof(t10_st)*(tnum+1));
	fscanf(sub,"%d",&snum);
	fscanf(sub,"%c",&dump);
	subway=(sub3_st*)malloc(sizeof(sub3_st)*(snum+1));
	
	for(i=0;i<num;i++)//파일 입출력으로 사용자들의 정보들을 불러서 저장한다.
	{
		fscanf(cus,"%d %*c %[^/] %*c %d %*c ",&(u[i].id),(u[i].name),&(u[i].money));
		fscanf(cus,"%[^ ] %*c %s\n",card,(u+i)->type);
		if(strcmp(card,"credit")==0)
		{
			(u+i)->cardtype=0;
		}
		else if(strcmp(card,"charge")==0)
		{
			(u+i)->cardtype=1;
		}


	}//여기까지 사용자 정보 입력 받음
	//여기부터 버스 DB 구축
	for(i=0;i<bnum;i++)
	{
		fscanf(b604,"%d %*c %d %*c %[^/] %*c %f\n",&(b[i].num),&(b[i].stationid),(b[i].name),&(b[i].s));
	
	
	}


	for(i=0;i<gnum;i++)
	{
		fscanf(g5714,"%d %*c %d %*c %[^/] %*c %f\n",&(g[i].num),&(g[i].stationid),(g[i].name),&(g[i].s));
		
	}


	for(i=0;i<tnum;i++)
	{
		fscanf(t10,"%d %*c %d %*c %[^/] %*c %f\n",&(t[i].num),&(t[i].stationid),(t[i].name),&(t[i].s));
	
	}
	

	for(i=0;i<snum;i++)
	{
		fscanf(sub,"%d %*c %d %*c %[^/] %*c %f\n",&(subway[i].num),&(subway[i].stationid),(subway[i].name),&(subway[i].s));
		
	}
	//여기까지 모든 버스와 지하철의 정보를 구조체 안에 저장함.

	printf("승(하)차 몇번을 할꺼니? : ");
	scanf("%d",&count);//승하차 개수
	if(count<=0)
	{
		printf("Error\n");
		return 0;
	}
	for(i=0;i<count;i++)
	{
		scanf("%d %*c %s %*c %d %*c %d%*c%d%*c%d %d%*c%d %*c %d %*c %d",&id,method,&stationid,&year,&month,&day,&hour,&minute,&transfer,&ride);
		addnode(id,method,stationid,year,month,day,hour,minute,transfer,ride);

	}
	temp=head;

	for(i=0;i<count;i++)
	{
		idnum[i]=temp->idnum;

		if(temp->ride==0)//승차 시
		{

			if(strcmp(temp->method,"b604")==0)
			{
				for(j=0;j<bnum;j++)
				{
					if(temp->stationid==b[j].stationid)
					{
						pre_s=j;//정류장 인덱스 저장
						break;
					}
				}
				if(strcmp(u[idnum[i]].type,"adult")==0)
					fee[i]=1050;
				else if(strcmp(u[idnum[i]].type,"teens")==0)
					fee[i]=720;
				else if(strcmp(u[idnum[i]].type,"child")==0)
					fee[i]=450;
			}
			else if(strcmp(temp->method,"g5714")==0)
			{
				for(j=0;j<gnum;j++)
				{
					if(temp->stationid==g[j].stationid)
					{
						pre_s=j;//정류장 인덱스 저장
						break;
					}
				}
				if(strcmp(u[idnum[i]].type,"adult")==0)
					fee[i]=1050;
				else if(strcmp(u[idnum[i]].type,"teens")==0)
					fee[i]=720;
				else if(strcmp(u[idnum[i]].type,"child")==0)
					fee[i]=450;
			}
			else if(strcmp(temp->method,"t10")==0)
			{
				for(j=0;j<tnum;j++)
				{
					if(temp->stationid==t[j].stationid)
					{
						pre_s=j;//정류장 인덱스 저장
						break;
					}
				}
				if(strcmp(u[idnum[i]].type,"adult")==0)
					fee[i]=850;
				else if(strcmp(u[idnum[i]].type,"teens")==0)
					fee[i]=560;
				else if(strcmp(u[idnum[i]].type,"child")==0)
					fee[i]=350;
			}
			else if(strcmp(temp->method,"3")==0)
			{
				for(j=0;j<snum;j++)
				{
					if(temp->stationid==subway[j].stationid)
					{
						pre_s=j;//정류장 인덱스 저장
						break;
					}
				}
				if(strcmp(u[idnum[i]].type,"adult")==0)
					fee[i]=1050;
				else if(strcmp(u[idnum[i]].type,"teens")==0)
					fee[i]=720;
				else if(strcmp(u[idnum[i]].type,"child")==0)
					fee[i]=450;
			}
		}
		else if(temp->ride==1)//하차시
		{
			if(strcmp(temp->method,"b604")==0)
			{
				for(j=0;j<bnum;j++)
				{
					if(temp->stationid==b[j].stationid)
					{
						po_s=j;
						break;
					}
				}
				for(j=pre_s+1;j<po_s+1;j++)
				{
					real_s[i]+=b[j].s;//여기서 승 하차시 이동거리 계산
				
				}
				if(real_s[i]>10)
				{
					fee[i]=((int)(((real_s[i]-10)/5)+1))*100;//추가 요금 계산
				}
			}
			if(strcmp(temp->method,"g5714")==0)
			{
				for(j=0;j<gnum;j++)
				{
					if(temp->stationid==g[j].stationid)
					{
						po_s=j;
						break;
					}
				}
				for(j=pre_s+1;j<po_s+1;j++)
				{
					real_s[i]+=g[j].s;
				}
				if(real_s[i]>10)
				{
					fee[i]=((int)(((real_s[i]-10)/5)+1))*100;
				
				}

			}
			if(strcmp(temp->method,"t10")==0)
			{
				for(j=0;j<tnum;j++)
				{
					if(temp->stationid==t[j].stationid)
					{
						po_s=j;
						break;
					}
				}
				for(j=pre_s+1;j<po_s+1;j++)
				{
					real_s[i]+=t[j].s;
				}
				if(real_s[i]>10)
				{
					fee[i]=((int)(((real_s[i]-10)/5)+1))*100;
				}

			}

			if(strcmp(temp->method,"3")==0)
			{
				for(j=0;j<snum;j++)
				{
					if(temp->stationid==subway[j].stationid)
					{
						po_s=j;
						break;
					}
				}
				for(j=pre_s+1;j<po_s+1;j++)
				{
					real_s[i]+=subway[j].s;
				}
				if(real_s[i]>10&&real_s[i]<=40)
				{
					fee[i]=((int)((real_s[i]-10)/5)+1)*100;
				}
				if(real_s[i]>40)
				{
					fee[i]=((int)((real_s[i]-40)/10)+1)*100;
					fee[i]+=600;
				}




			}
		}
		if(temp->link==NULL)
		{
			break;
		}
		temp=temp->link;
		
	}
	temp=head;
	//환승

			

	
	for(i=0;i<count;i++)//변수에 대입, 배열로 쉽게 풀기 위해
	{
		transfer2[i]=temp->transfer;
		if(temp->link==NULL)
			break;
		temp=temp->link;
	}

		
	/*
	temp=head;
	for(i=0;i<count;i++)
	{
		if(idnum[i]==idnum[i+1])
		{
			if(transfer2[i]+1==transfer2[i+1])
			{
				total_s[idnum[i]]+=real_s[i+1];
	 */
	for(i=0;i<count;i++)
		ontransfer[i]=0;

	for(i=0;i<count;i++)
	{
		if(idnum[i]==idnum[i+1])
		{
			if(transfer2[i]+1==transfer2[i+1])//환승할 경우
			{
				ontransfer[i+1]=1;//1은 환승 중이라는 것을 뜻한다.
				ontransfer[i+2]=1;
			}
		}
	}


	//환승
	temp=head;
	for(i=0;i<count;i++)
	{
		if(temp->idnum==temp->link->idnum)
		{		
			if(strcmp(temp->method,"3")==0)
			{
				if(strcmp(temp->link->method,"3")==0)
				{
					break;
				}
			}//지하철 ->지하철 일경우break
			{
				if(temp->link->transfer>5)//환승횟수가 6회이상이면 다시처음부터
					break;
				else if(temp->link->transfer==temp->transfer+1)
				{
					fee[i+1]=0;
					if(ontransfer[i]==0)
					{
						fee[i]=0;
						if(strcmp(temp->method,"3")==0)
						{
							if(real_s[i]>10)
							{
								fee[i]=((int)((real_s[i]-10)/5)+1)*100;
								fee[i+2]=((int)((real_s[i]+real_s[i+2]-10)/5)+1)*100-fee[i];
							}
							else
							{
								fee[i]=0;
							}
						}
						else
						{
						fee[i+2]=((int)((real_s[i]+real_s[i+2]-10)/5)+1)*100;
						}
					}
					else
					{
						if(fee[i]>=100)
						{
							fee[i+2]=(int)(((real_s[i]+real_s[i+2])-((fee[i]/100))*10)/5)*100;
						}
						else
						{
							fee[i+2]=((int)((real_s[i]+real_s[i+2]-10)/5))*100;
						}
					}
				}
				else
				{
					if(temp->ride==0)
					{
					if(ontransfer[i]==0)
					{
						fee[i+1]=0;
					}
					}
				}
			}
		}
		if(temp->link->link==NULL)
			break;
		temp=temp->link;
	}//

	//승차2

	temp=head;
	for(i=0;i<count;i++)
	{
		if(u[idnum[i]].cardtype==1)
		{
			if(u[idnum[i]].money-fee[i]<0)
			{
				printf("잔액 부족\n");
				continue;
			}
			else
			{
				printf("%d : %d, %d, %.1f \n",idnum[i],fee[i],u[idnum[i]].money-fee[i],real_s[i]);
			//if(strcmp(temp->method,"3")==0)
				u[idnum[i]].money-=fee[i];
			}
		}
		else
		{
			printf("%d : %d, %d, %.1f \n",idnum[i],fee[i],u[idnum[i]].money+fee[i],real_s[i]);
			//if(strcmp(temp->method,"3")==0)
				u[idnum[i]].money+=fee[i];
		}
		if(temp->link==NULL)
			break;
		temp=temp->link;

	} //출력
	temp=head;
	for(i=0;i<count;i++)//지하철일 경우만 업데이트 해야하므로 지하철이 아닌 경우는 다시 요금을 원상태로 돌려준다.
	{
		if(u[idnum[i]].cardtype==1)
		{
			if(strcmp(temp->method,"3")==0)
				continue;
			else
			{
				u[idnum[i]].money+=fee[i];
			}
		}
		else
		{
			if(strcmp(temp->method,"3")==0)
				continue;
			else
			{
				u[idnum[i]].money-=fee[i];
			}
		}
	}
	



	//customer 파일 업데이트
	fprintf(fp2,"%d\n",num);
	for(i=0;i<num;i++)
	{
		if(u[i].cardtype==0)
			fprintf(fp2,"%d / %s/ %d / credit / %s\n",u[i].id,u[i].name,u[i].money,u[i].type);
		else
			fprintf(fp2,"%d / %s/ %d / charge / %s\n",u[i].id,u[i].name,u[i].money,u[i].type);
	}

	//


	//reader_output.txt 파일 만들기
	temp=head;
	fprintf(out,"%d\n",count);
	for(i=0;i<count;i++)
	{
		if(u[idnum[i]].cardtype==0)
		{
			fprintf(out,"%s / %d / %d.%d.%d %d:%d / %d / credit / %s / %d\n",temp->method,idnum[i],temp->year,temp->month,temp->day,temp->hour,temp->minute,temp->stationid,u[idnum[i]].type,fee[i]);
		}
		else
		{
			fprintf(out,"%s / %d / %d.%d.%d %d:%d / %d / charge / %s / %d\n",temp->method,idnum[i],temp->year,temp->month,temp->day,temp->hour,temp->minute,temp->stationid,u[idnum[i]].type,fee[i]);
		}
		if(temp->link==NULL)
			break;
		temp=temp->link;
	}//reader_output.txt 파일 생성
	temp=head;

	for(i=0;i<count-1;i++)
	{
		temp=del;
		free(del);
		del=temp->link;
	}


	fclose(cus);
	fclose(fp2);
	fclose(b604);
	fclose(g5714);
	fclose(t10);
	fclose(sub);
	fclose(out);
	free(method);
	free(card);
	free(u);
	free(g);
	free(t);
	free(subway);

	return 0;
}
