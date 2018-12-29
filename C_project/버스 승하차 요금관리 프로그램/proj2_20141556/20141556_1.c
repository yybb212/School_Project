#include<stdio.h>
#include<stdlib.h>
#include<string.h>
enum type{credit,charge};

typedef struct{
	int id;//이용자 id
	char name[30];//이용자 이름
	int money;//이용자 잔액 or 누적금액
	enum type cardtype;//이용자 카드 종류
	char type[7];//이용자 종류
}user;
typedef struct _node{
	int id;
	char method[10];
	int stationid;
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int s;
	int fee;
	struct _node* link;
}node;//승(하)차에 대한 정보를 위한 리스트를 작성한다.
void addnode(node* head,int idnum,char* method,int stationid,int year,int month,int day,int hour,int minute,float s,int fee)//승(하)차를 할 때마다 받는 정보들을 리스트에 새로운 노드로 추가하는 함수
{
	node* pnew;
	node* temp;
	pnew=(node*)malloc(sizeof(node));
	pnew->id=idnum;
	strcpy(pnew->method,method);
	pnew->stationid=stationid;
	pnew->year=year;
	pnew->month=month;
	pnew->day=day;
	pnew->hour=hour;
	pnew->minute=minute;
	pnew->s=s;
	pnew->fee=fee;

	temp=head;
	if(head==NULL)
	{
		pnew->link=head;
		head=pnew;
	}
	else
	{
		while(temp->link!=NULL)
			temp=temp->link;
		temp->link=pnew;


	}

}


int main()
{
	node* head=NULL;//여러가지 변수 설정

	user* u;
	int* don;
	int* bun;
	char* method;
	char dump;
	char* card;

	int num,i,j,idnum,stationid,year,month,day,hour,minute,fee;
	int num2;
	//	int time_m,time_h;
	float s;
	FILE*fp1=fopen("customer.txt","r");
	FILE*fp2=fopen("customer.txt","r+");
	//	node* pnew;

	fscanf(fp1,"%d%c",&num,&dump);
	u=(user*)malloc(sizeof(user)*num);
	card=(char*)malloc(sizeof(char)*7);
	method=(char*)malloc(sizeof(char)*10);


	for(i=0;i<num;i++)//파일 입출력으로 사용자들의 정보들을 불러서 저장한다.
	{
		fscanf(fp1,"%d %*c %[^/] %*c %d %*c ",&(u[i].id),(u[i].name),&(u[i].money));
		fscanf(fp1,"%[^ ] %*c %s\n",card,(u+i)->type);
		if(strcmp(card,"credit")==0)
		{
			(u+i)->cardtype=0;
		}
		else if(strcmp(card,"charge")==0)
		{
			(u+i)->cardtype=1;
		}
		printf("%d / %s / %d / %d / %s\n",u[i].id,u[i].name,u[i].money,u[i].cardtype,u[i].type);

	}

	printf("승,하차 몇번 할꺼니? : ");//승하차를 몇번 할것인지 입력
	scanf("%d",&num2);
	if(num2<1)
	{
		printf("Fail!!\n");
		return 0;
	}
	don=(int*)malloc(sizeof(int)*(num2+1));//잔액 현황
	bun=(int*)malloc(sizeof(int)*(num2+1));//사용자 id현황
	j=0;
	for(i=0;i<num2;i++)//모니터로 승(하)차 정보를 입력받아 구조체에서 다시 재조정한다.
	{
		scanf("%d %*c %s %*c %d %*c %d%*c%d%*c%d %d%*c%d %*c %f %*c %d",&idnum,method,&stationid,&year,&month,&day,&hour,&minute,&s,&fee);//승차시 정보
		addnode(head,idnum,method,stationid,year,month,day,hour,minute,s,fee);
		if(u[idnum].cardtype==0)//신용카드일 경우
		{
			u[idnum].money+=fee;//구조체에서 잔액 혹은 누적액을 수정
			don[j]=u[idnum].money;//잔액을 배열에 저장
		}
		else//charge카드일 경우
		{
			u[idnum].money-=fee;
			if(u[idnum].money<0)
			{
				printf("FAIL\n");
				u[idnum].money+=fee;
				return 0;
			}
			don[j]=u[idnum].money;
		}
		bun[j]=idnum;
		j++;


	}
	j=0;
	printf("잔액결과 \n");
	for(i=0;i<num2;i++)
	{
		printf(" - %d : %d \n",bun[j],don[j]);
		j++;

	}

	fprintf(fp2,"%d\n",num);
	for(i=0;i<num;i++)
	{
		if(u[i].cardtype==0)
			fprintf(fp2,"%d / %s/ %d / credit / %s\n",u[i].id,u[i].name,u[i].money,u[i].type);
		else
			fprintf(fp2,"%d / %s/ %d / charge / %s\n",u[i].id,u[i].name,u[i].money,u[i].type);
	}
	
	
		


	fclose(fp1);
	fclose(fp2);
	free(u);
	free(card);
	free(method);
	free(bun);
	free(don);
	free(head);
	return 0;


}
