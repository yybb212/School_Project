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

typedef struct{
	char method[7];
	int idnum;
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int stationid;
	enum type cardtype;
	char type[6];
	int fee;
}reader_output;//reader_output.txt 파일에서부터 승 하차 정보를 저장할 구조체

int main()
{
	int count,i,num,j,k;
	int howmuch;//몇 번 돌릴 지
	int charge,inputid;
	int inputnum[3];
	char inputchar[10];
	char dump;
	char* card;
	char* inputmethod;
	card=(char*)malloc(sizeof(char)*7);
	inputmethod=(char*)malloc(sizeof(char)*7);
	user* u;
	reader_output* reader;
	FILE* fp1=fopen("customer.txt","r");
	FILE* fp2=fopen("customer.txt","r+");
	FILE* fp3=fopen("reader_output.txt","r");
	fscanf(fp1,"%d",&num);
	fscanf(fp1,"%c",&dump);

	//reader=(reader_output*)malloc(sizeof(reader_output));
	u=(user*)malloc(sizeof(user)*(num));
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
	//	printf("%d / %s / %d / %d / %s\n",u[i].id,u[i].name,u[i].money,u[i].cardtype,u[i].type);//잘 저장되었는지 확인

	}//

	fscanf(fp3,"%d%c",&count,&dump);
	reader=(reader_output*)malloc(sizeof(reader_output)*count);

	for(i=0;i<count;i++)//reader_output.txt 파일을 구조체에 저장한다.
	{
		fscanf(fp3,"%s %*c %d %*c %d%*c%d%*c%d %d%*c%d %*c %d %*c %s %*c %s %*c %d%c",reader[i].method,&(reader[i].idnum),&(reader[i].year),&(reader[i].month),&(reader[i].day),&(reader[i].hour),&(reader[i].minute),&(reader[i].stationid),card,reader[i].type,&(reader[i].fee),&dump);

		if(strcmp(card,"credit")==0)
			(reader+i)->cardtype=0;
		else
			(reader+i)->cardtype=1;

	}



	/*for(i=0;i<count;i++)//구조체에 잘 들어왔는지 확인
	  {
	  printf("%s / %d / %d.%d.%d %d:%d / %d / %d / %s / %d\n",reader[i].method,reader[i].idnum,reader[i].year,reader[i].month,reader[i].day,reader[i].hour,reader[i].minute,reader[i].stationid,reader[i].cardtype,reader[i].type,reader[i].fee);

	  }*/

	printf("몇번 입력? : ");
	scanf("%d",&howmuch);//몇번 입력받는지 입력
	for(k=0;k<howmuch;k++)//입력 받는 것을 배열에 따로따로 구별에서 저장한다.
	{
		printf("Input : ");
		j=0;
		for(i=0;i<3;i++)
		{
			scanf("%d",&inputnum[i]);
			while(1)
			{
				scanf("%c",&inputchar[j]);
				if(inputchar[j]=='/')
				{
					j++;
					break;
				}
				else if(inputchar[j]=='\n')
				{	j++;
					break;
				}
				j++;
			}
			if(inputnum[0]==3)
			{
				scanf("%s",inputmethod);
				break;
			}
			else if(inputchar[j-1]=='\n')
				break;
		}


		if(inputnum[0]==1)
			// menu가 1 이면 카드 충전을 시작한다. 단, 사용자의 카드가 charge일 경우에만.
		{
			inputid=inputnum[1];
			charge=inputnum[2];

			if(u[inputid].cardtype==1)//charge 일 경우 출력
			{
				printf("%d : %d, %d\n",inputid,u[inputid].money,(u[inputid].money)+charge);
				u[inputid].money+=charge;
			}
			else
			{
				printf("fail\n");
			}
		}

		else if(inputnum[0]==2)//menu가 2이면 credit 초기화를 시작한다. 단, 사용자의 카드가 credit일 경우에만.
		{
			for(i=0;i<num;i++)
			{
				if(u[i].cardtype==0)//credit일 경우
				{
					printf("%d : %s / %d\n",i,u[i].name,u[i].money);
					u[i].money=0;
				}
				else
				{		
				}
			}

		}
		else if(inputnum[0]==3)//last stop station 프로그램 실행
		{
			for(i=0;i<count;i++)//해당 교통수단 이용 내역 출력
			{
				if(strcmp(reader[i].method,inputmethod)==0)
				{
					printf("%d : %d\n",reader[i].idnum,reader[i].fee);

				}
			}

			for(i=0;i<num;i++)
			{
				if(u[i].cardtype==0)
				{
					printf("%d / %s / %d / credit / %s\n",i,u[i].name,u[i].money,u[i].type);
				}
			}
			for(i=0;i<count;i++)
			{
				if(strcmp(reader[i].method,"3")==0)//지하철인 경우에는 정산하지 않는다.
					continue;
				else
				{
					if(reader[i].cardtype==0)
					{
						u[reader[i].idnum].money+=reader[i].fee;
					}
					else
						u[reader[i].idnum].money-=reader[i].fee;
				}
			}





		}
	}


	fprintf(fp2,"%d\n",num);
	for(i=0;i<num;i++)
	{
		if(u[i].cardtype==0)
			fprintf(fp2,"%d / %s/ %d / credit / %s\n",u[i].id,u[i].name,u[i].money,u[i].type);
		else if(u[i].cardtype==1)
			fprintf(fp2,"%d / %s/ %d / charge / %s\n",u[i].id,u[i].name,u[i].money,u[i].type);
	}//다시 customer.txt 파일 업데이트
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);

	free(u);
	free(reader);
	return 0;
		
}
