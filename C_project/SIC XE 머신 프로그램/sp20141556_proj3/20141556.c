#include"20141556.h"
int end;
int main()
{
	
	int i,j;//변수들 초기화
	savenum=0;
	realend=0;
	tempend=0;
	realstart=1;
	progAddr=0;
	bphead=NULL;
	A=0;
	X=0;
	L=0;
	PC=0;
	B=0;
	S=0;
	T=0;
	for(i=0;i<=1048575;i++)//메모리 내용 초기화
	{
		m[i][0]='0';
		m[i][1]='0';
		m[i][2]='\0';
	}

	head=NULL;//linked list 구현을 위한 head 포인터 초기화
	char* input2;//입력되는 명령어
	char* inputn;
	char* input;
	char enter;
	char d[4];
	//여기서부터 hash table에 opcode 파일입력
	FILE* p=fopen("opcode.txt","rt");//해쉬 테이블을 위한 파일 입력
	for(i=0;i<20;i++)
	{
		table[i]=(hnode*)malloc(sizeof(hnode));//메모리 할당
		strcpy(table[i]->op,"--");
	}
	for(i=0;;i++)
	{
		hnode* new;//새로운 노드
		new=(hnode*)malloc(sizeof(hnode));
		new->link=NULL;
		if(fscanf(p,"%s %s %s%c",new->op,new->ins,d,&enter)==EOF)
			break;
		sscanf(d,"%d",&(new->num));
		addtable(new);//해쉬 테이블에 추가

	}
	fclose(p);//종료
	while(1){//반복한다
		printf("sicsim> ");//명령어를 입력받는다.
		input2=(char*)malloc(sizeof(char)*256);
		input=(char*)malloc(sizeof(char)*256);
		for(i=0;;i++)//history에 저장을 위해 공백도 다 입력받는다.
		{
			scanf("%c",input2+i);
			if(input2[i]=='\n')
				break;
		}
		input2[i]='\0';
		inputn=rmspace(input2);//공백을 지워준다.
		char* start;//dump에서 첫번째 주소를 위한 변수
		char* end;//마찬가지로 두번째 주소를 위한 변수.
		start=(char*)malloc(sizeof(char)*20);//메모리 할당
		end=(char*)malloc(sizeof(char)*20);
		start[0]='*';//이 작업은 start만 받았는지 아니면 둘다 받았는지 아니면 아무것도 안받았는지 확인하기 위한 것임
		end[0]='*';
		sscanf(input2,"%s",input);//앞에 한단어만 추려낸다.
		//sscanf(input2,"%s %2[^,] %*c %s",input,start,end);
		if(strcmp(input,"help")==0||strcmp(input,"h")==0)//help 명령어 수행
		{
			if(strcmp(input,"help")==0)//예외 작업
			{
				if(inputn[4]!='\0')
				{
					printf("Error\n");
					continue;
				}
			}
			else if(strcmp(input,"h")==0)//예외 작업
				if(inputn[1]!='\0')
				{
					printf("Error\n");
					continue;
				}

			printf("h[elp]\n");
			printf("d[ir]\n");
			printf("q[uit]\n");
			printf("hi[story]\n");
			printf("du[mp] [start, end]\n");
			printf("e[dit] address, value\n");
			printf("f[ill] start, end, value\n");
			printf("reset\n");
			printf("opcode mnemonic\n");
			printf("opcodelist\n");
			printf("assemble filename\n");
			printf("type filename\n");
			printf("symbol\n");
			addh(input2);//linked list에 추가
		}
		else if(strcmp(input,"dir")==0||strcmp(input,"d")==0)//dir 명령어 수행
		{
			if(strcmp(input,"dir")==0){//예외 작업
				if(inputn[3]!='\0')
				{
					printf("Error\n");
					continue;
				}
			}
			else if(strcmp(input,"d")==0)//예외 작업
			{
				if(inputn[1]!='\0')
				{
					printf("Error\n");
					continue;
				}
			}
			DIR* d;
			struct dirent *f;//파일 정보를 얻기위한 변수
			struct stat info;
			d=opendir(".");//현재 위치 디렉토리를 열어준다.
			if(!d)continue;//오류일경우 명령어를 다시 받는다.
			while(1)
			{
				f=readdir(d);//현재 디렉토리 환경을 f 변수에 저장
				if(!f)break;
				stat(f->d_name,&info);//파일 정보를 입력받는다.
				if(info.st_mode==16877)
					printf("%s\t/",f->d_name);//디렉토리 파일일 경우 /출력
				else if((S_IEXEC & info.st_mode)==S_IEXEC)//실행 파일일 경우 *출력
					printf("%s*\t",f->d_name);
				else
					printf("%s\t",f->d_name);//그 무엇도 아닐때 그냥 출력

			}
			closedir(d);//함수종류
			printf("\n");
			addh(input2);//linked list에 명령어 추가
		}
		else if(strcmp(input,"quit")==0||strcmp(input,"q")==0)//quit 명령어 수행
		{
			if(strcmp(input,"quit")==0)//예외 작업
			{
				if(inputn[4]!='\0')
				{
					printf("Error\n");
					continue;
				}
			}
			else if(strcmp(input,"q")==0)//예외작업
			{
				if(inputn[1]!='\0')
				{
					printf("Error\n");
					continue;
				}
			}
			break;
		}
		else if(strcmp(input,"history")==0||strcmp(input,"hi")==0)//history 명령어 수행
		{
			if(strcmp(input,"history")==0){//예외 작업
				if(inputn[7]!='\0')
				{
					printf("Error\n");
					continue;
				}
			}
			else if(strcmp(input,"hi")==0){//예외 작업
				if(inputn[2]!='\0')
				{
					printf("Error\n");
					continue;
				}
			}

			addh(input2);//history 또한 명령어므로 사용 내역에 추가
			printh();//history에 저장된 노드들 출력

		}
		else if(strcmp(input,"dump")==0||strcmp(input,"du")==0)//dump 명령어를 입력받을 경우
		{
			int error1=0;
			int error2=0;
			char comma='\0';
			char junk[2]={'\0','\0'};
			sscanf(input2,"%s %[^,] %c %s %s",input,start,&comma,end,junk);
			if(comma==',')//콤마가 있을경우 start end 둘다 있는지 확인
			{
				if(junk[0]!='\0'){//쭈우욱 예외 작업들이다.
					printf("Error\n");
					continue;
				}
				start=changestart(start);//오류 검사를 위한 변형
				error1=checkin2(start);//첫번째 오류 검사
				error2=checkin2(end);
				if(error1+error2!=0)
				{
					printf("Error\n");
					continue;
				}
				error1=0;
				error2=0;
				error1=checkin(start);//두번째 오류검사
				error2=checkin(end);
				if(error1+error2!=0)
				{
					printf("Error\n");
					continue;
				}
				if(to10(start)>to10(end))
				{
					printf("Error\n");
					continue;
				}
				int one,two;
				int lineone,linetwo;//첫 줄과 마지막 줄
				one=to10(start);
				two=to10(end);
				if(two>=1048576)//메모리 경계를 넘어갈 경우
					two=1048575;
				lineone=(one/16);//첫번째로 출력하는 공간
				linetwo=(two/16);//마지막으로 출력하는 공간
				
				for(i=lineone;i<=linetwo;i++)//줄수만큼 돌려준다.
				{
					printf("%05X ",i*16);
					for(j=i*16;j<=i*16+15;j++)
					{
						if(j>=one&&j<=two)//출력 범위일 경우
							printf("%02X ",to10(m[j]));//16진수로 출력해준다.
						else
							printf("   ");
					}
					printf("; ");
					for(j=i*16;j<=i*16+15;j++)//메모리 내용에 해당하는 문자를 출력한다.
					{
						if(j>=one&&j<=two)
						{
							if(to10(m[j])>=32&&to10(m[j])<=126)//출력 범위일때
								printf("%c",to10(m[j]));
							else
								printf(".");
						}
						else
							printf(".");
					}
					printf("\n");
				}
				if(two==1048575)//Boundary를 넘어갈 경우이다.
					savenum=0;
				else
					savenum=to10(end)+1;
				
			}
			else if(start[0]=='*')// dump만 입력받을 경우
			{
				if(inputn[4]==','||inputn[2]==',')//예외 작업
				{
					printf("Error\n");
					continue;
				}//savenum이 출발 지점
				int lineone,linetwo;
				lineone=savenum/16;
				int two=savenum+159;
				if(two>=1048576)//Boundary check
					two=1048575;
				linetwo=(two)/16;
				
				for(i=lineone;i<=linetwo;i++)
				{
					printf("%05X ",i*16);//16진수 출력
					for(j=i*16;j<=i*16+15;j++)
					{
						if(j>=savenum&&j<=two)//범위 내일 경우 출력
							printf("%02X ",to10(m[j]));
						else
							printf("   ");
					}
					printf("; ");
					for(j=i*16;j<=i*16+15;j++)
					{
						if(j>=savenum&&j<=two)
						{
							if(to10(m[j])>=32&&to10(m[j])<=126)//마찬가지로 범위 내일 경우 출력
								printf("%c",to10(m[j]));
							else
								printf(".");
						}
						else
							printf(".");
					}
					printf("\n");
				}
				if(two==1048575)//Boundary를 넘길 경우 작업
					savenum=0;
				else
					savenum=savenum+160;

			}
			else if(start[0]!='*' && end[0]=='*')//start 하나만 입력받을 경우
			{
				error1=0;
				error1=checkin(start);
				if(error1==1)
				{
					printf("Error\n");
					continue;
				}
				int lineone,linetwo;savenum=to10(start);//위 내용들과 같은 작업들이다.
				int two=to10(start)+159;
				if(two>=1048576)
					two=1048575;
				lineone=to10(start)/16;
				linetwo=(two)/16;
				for(i=lineone;i<=linetwo;i++)
				{
					printf("%05X ",(i*16));
					for(j=i*16;j<=i*16+15;j++)
					{
						if(j>=savenum&&j<=two)
							printf("%02X ",to10(m[j]));
						else
							printf("   ");
					}
					printf("; ");
					for(j=i*16;j<=i*16+15;j++)
					{
						if(j>=savenum&&j<=two)
						{
							if(to10(m[j])>=32&&to10(m[j])<=126)
								printf("%c",to10(m[j]));
							else
								printf(".");
						}
						else
							printf(".");
					}
					printf("\n");
				}
				if(two==1048575)
					savenum=0;
				else
					savenum=savenum+160;
			}
			addh(input2);//history에 추가해준다.

		}
		else if(strcmp(input,"edit")==0||strcmp(input,"e")==0)//메모리 내용을 원하는 16진수로 바꿔줄때
		{
			int error1=0;
			int error2=0;
			char* add=(char*)malloc(sizeof(char)*6);//바꿀 주소이다.
			char* value=(char*)malloc(sizeof(char)*3);//바꿀 메모리 내용이다.
			char comma='\0';
			char junk[2]={'\0','\0'};
			sscanf(input2,"%s %[^,] %c %s %s",input,add,&comma,value,junk);//dump와 마찬가지 방법으로 인자들을 입력받는다.
			if(comma==',')
			{
				if(junk[0]!='\0')//예외 처리이다.
				{
					printf("Error\n");
					continue;
				}
				add=changestart(add);
				error1=checkin2(add);
				error2=checkin2(value);
				if(error1+error2!=0)//오류 처리
				{
					printf("Error\n");
					continue;
				}
				error1=0;error2=0;
				error1=checkin(add);
				error2=checkin(value);
				if(error1+error2!=0)
				{
					printf("Error\n");
					continue;
				}
				strcpy(m[to10(add)],value);//원하는 내용으로 바꿔준다.
			}
			else 
			{
				printf("Error\n");
				continue;
			}
			addh(input2);//history에 추가해준다.
		}

		else if(strcmp(input,"fill")==0||strcmp(input,"f")==0)//start번지부터 end 번지까지의 값을 value에 지정된 값으로 변경해주는 함수
		{
			int error1=0;
			int error2=0;
			int error3=0;
			char a,b;a='\0';b='\0';
			char junk[2]={'\0','\0'};
			char* value=(char*)malloc(sizeof(char)*3);
			sscanf(input2,"%s %[^,] %c %[^,] %c %s %s",input,start,&a,end,&b,value,junk);
			if(a==','&&b==',')//제대로 입력되었을 때
			{
				if(junk[0]!='\0')//오류 검사
				{
					printf("Error\n");
					continue;
				}
				start=changestart(start);
				end=changestart(end);
				error1=checkin2(start);
				error2=checkin2(end);
				error3=checkin2(value);
				if(error1+error2+error3!=0)//오류 검사
				{
					printf("Error\n");
					continue;
				}
				error1=0;error2=0;error3=0;
				error1=checkin(start);
				error2=checkin(end);
				error3=checkin(value);
				if(error1+error2+error3!=0)//계속 되는오류 검사
				{
					printf("Error\n");
					continue;
				}
				if(to10(start)>to10(end))//예외 처리
				{
					printf("Error\n");
					continue;
				}
				if(strlen(value)>=3)
				{
					printf("Error\n");
					continue;
				}
				//여기까지가 문법이나 이상한 오류 검사하는 과정

				for(i=to10(start);i<=to10(end);i++)//바꿔준다. 
				{
					strcpy(m[i],value);
				}
			}
			else
			{
				printf("Error\n");
				continue;
			}
			addh(input2);//history에 추가해준다.
		}
		else if(strcmp(input,"reset")==0)//모든 메모리를 0으로 만들고 싶을 때
		{
			if(inputn[5]!='\0')//오류 검사
			{
				printf("Error\n");
				continue;
			}

			for(i=0;i<=1048575;i++)//모든 메모리를 바꿔준다.
			{
				strcpy(m[i],"00");
			}
			addh(input2);//history에 추가
		}
		else if(strcmp(input,"opcode")==0)//opcode 명령어일 때
		{
			char m[8];
			char junk[2]={'\0','\0'};
			sscanf(input2,"%s %s %s",input,m,junk);

			if(junk[0]!='\0')//오류 검사
			{
				printf("Error\n");
				continue;
			}
			if(findandprint(m)==0)//만약 출력할 명령어가 없을 경우이다. Invlalid 
				continue;
			addh(input2);

		}
		else if(strcmp(input,"opcodelist")==0)//Hash table에 저장된 opcode들을 순서대로 출력해준다.
		{
			if(strcmp(inputn,"opcodelist")!=0)//오류 처리
			{
				printf("Error\n");
				continue;
			}
			printtable();//출력해준다.
			addh(input2);//history에 넣어준다.
		}	
		else if(strcmp(input,"type")==0)//type일 경우 파일 내용 전체 출력
		{
			char junk[2]={'\0','\0'};
			char file[30];
			sscanf(input2,"%s %s %s",input,file,junk);//파일 이름을 뽑아낸다.
			if(junk[0]!='\0')//에러체크
			{
				printf("Error\n");
				continue;
			}
			int k;
			int commacount=0;//comma개수를 세주는 변수
			for(k=1;k<=strlen(file)-2;k++)
			{
				if(file[k]=='.')
					commacount++;
			}
			if((commacount!=1||file[0]=='.')||file[strlen(file)-1]=='.')
			{
				printf("Error\n");
				continue;
			}
				
				
			FILE* p=fopen(file,"r");
			if(p==NULL)//그 파일이 없을 때이다.
			{
				printf("No file\n");
				addh(input2);
				continue;
			}
			char c;
			while((fscanf(p,"%c",&c)!=EOF))//끝까지 출력해준다.
			{
				printf("%c",c);
			}
			printf("\n");
			fclose(p);
			addh(input2);
		}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
		else if(strcmp(input,"symbol")==0)//symbol 명령어 입력할때
		{
			if(strcmp(inputn,"symbol")!=0){//오류 체크
				printf("Error\n");
				continue;
			}
			if(stable==NULL)//테이블이 비어있을경우이다.
			{
				printf("Empty table\n");
				addh(input2);
				continue;
			}
			/*
			for(i=0;i<=endd;i++)//저장할 SYMBOL이경우에만 table에 추가해준다.
			{
				if(((sou+i)->one[0]<'A'||(sou+i)->one[0]>'Z'))
				{
					continue;
				}
				else
				{
					addsymbol(i);//해당 데이터를 저장
				}
			}*/
			printsymbol();//symbol table을 출력해준다.
				//free(sou);
			addh(input2);
		}
		else if(strcmp(input,"assemble")==0)//어셈 파일을 분석해 lst와 obj파일을 생성해준다.
		{
			char junk[2]={'\0','\0'};
			char file[30];
			sscanf(input2,"%s %s %s",input,file,junk);//마찬가지로 이름을 뽑아준다.
			if(junk[0]!='\0')//에러체크
			{
				printf("Error\n");
				continue;
			}
			FILE* p=fopen(file,"r");
			if(p==NULL)//에러체크
			{
				printf("Error\n");
				continue;
			}
			char name[30];//lst파일을 위한 변수
			char name2[30];//obj 파일을 위한 변수
			sscanf(file,"%[^.]",name);//lst
			sscanf(file,"%[^.]",name2);
			strcat(name,".lst");
			strcat(name2,".obj");
			//FILE* q=fopen(name,"w");
			//FILE* r=fopen(name2,"w");
			printf("\toutput file : [%s], [%s]\n",name,name2);

			char enter;
			int start;
			sou=(asmm*)malloc(sizeof(asmm)*2);
			char starts[31];//어셈 파일의 첫 줄을 받을 문자열이다.
			fscanf(p,"%[^\n]%*c",starts);
			sscanf(starts,"%s %s %s",sou->one,sou->two,sou->three);
			if(sou->three[0]=='\0')//Start가 존재하지 않을 때이다.
				start=0;//0으로 설정
			else
				sscanf(sou->three,"%d",&start);

			if(strcmp(sou->two,"START")!=0&&find(sou->two)==1)//START가 없고 바로 코드가 시작될 경우
			{
				sou->line=5;
				start=0;
				sou->loc=start;
			}
			else{
				sou->line=5;
				sou->loc=start;
				//fprintf(q,"%5d\t%04X  %-10s %-8s %-9s\n",sou->line,sou->loc,sou->one,sou->two,sou->three);
			}
			i=1;

			erflag=0;
			while(1)
			{
				if(erflag==1)
					break;
				
				sou=(asmm*)realloc(sou,sizeof(asmm)*(i+2));//메모리 할당
				(sou+i)->one[0]='\0';
				(sou+i)->two[0]='\0';
				(sou+i)->three[0]='\0';
				char temp[10];
				char temp2[10];
				fscanf(p,"%s",temp2);
				if(temp2[0]=='+')//앞에 +가 붙어있을 경우
					strcpy(temp,temp2+1);
				else
					strcpy(temp,temp2);
				if(strcmp(temp,".")==0)//빈줄일때, 주석처리된 줄일 때이다.
				{
					fscanf(p,"%c",&enter);
					((sou+i)->one)[0]='.';
					if(enter=='\n')
					{
						strcpy((sou+i)->junk,"\0");
					}
					else
					{
						fscanf(p,"%[^\n]%c",(sou+i)->junk,&enter);
					}
					(sou+i)->line=i*5+5;	
					(sou+i)->loc=-1;
					//fprintf(q,"%5d\t      .%s\n",(sou+i)->line,(sou+i)->junk);
					i++;
					continue;
				}
				if(strcmp(temp,"END")==0)//끝 줄일 경우
				{
					(sou+i)->line=5*i+5;
					(sou+i)->loc=start;//location이 없는경우 -1
					strcpy((sou+i)->two,temp);
					fscanf(p,"%s",(sou+i)->three);
					endd=i;
					
					//fprintf(q,"%5d\t                 %-8s %-9s",(sou+i)->line,(sou+i)->two,(sou+i)->three);
					break;
				}
				if(strcmp(temp,"BASE")==0)//Base일 경우이다.
				{
					strcpy((sou+i)->two,temp);
					(sou+i)->loc=-1;
					fscanf(p,"%s%c",(sou+i)->three,&enter);
				}
				else if(find(temp)==0)//Hash table에 없을 경우,first일 경우
				{
					strcpy((sou+i)->one,temp);
					fscanf(p,"%s",(sou+i)->two);
					if((strcmp((sou+i)->two,"COMPR")==0||strcmp((sou+i)->two,"STCH")==0)||strcmp((sou+i)->two,"LDCH")==0)//콤마가 필요할 경우
					{
						fscanf(p,"%[^,] %c %s%c",temp,&((sou+i)->comma),(sou+i)->four,&enter);
						strcpy((sou+i)->three,rmspace(temp));



					}
					else//일반적인 음네모닉일때
					{
						fscanf(p,"%s%c",(sou+i)->three,&enter);
					}

					//location 설정start로 설정해준다. 일괄적으로 설정해준다.
					if(((sou+i)->two)[0]=='+')//+가 앞에 붙어있을 경우 4형식
					{
						(sou+i)->loc=start;
						start+=4;
					}
					else if(strcmp((sou+i)->two,"BASE")==0)//BASE일 경우
					{
						(sou+i)->loc=-1;
					}
					else if(strcmp((sou+i)->two,"RESW")==0)//RESW,RESB,BYTE일 경우 예외 처리
					{
						(sou+i)->loc=start;
						int t;
						sscanf((sou+i)->three,"%d",&t);
						start+=3*t;
					}
					else if(strcmp((sou+i)->two,"RESB")==0)
					{
						(sou+i)->loc=start;
						int t;
						sscanf((sou+i)->three,"%d",&t);
						start+=t;
					}
					else if(strcmp((sou+i)->two,"BYTE")==0)
					{
						(sou+i)->loc=start;
						if(((sou+i)->three)[0]=='C')//캐릭터형일 경우
						{
							int count=0;

							count=strlen((sou+i)->three)-3;
						
							start+=count;//문자 개수만큼 location 증가
						}
						else if(((sou+i)->three)[0]=='X')//16진수일 경우 1 증가
							start+=1;
					}
					else if(find((sou+i)->two)==0)//Hash table안에 존재하지 않을때
					{
						printf("Line num %d : No mnemonic\n",i+1);
						free(sou);
						erflag=1;
						continue;
					}

					else//그 외 일반적인 경우
					{
						(sou+i)->loc=start;
						start+=findnum((sou+i)->two);
					}

				}
				else//Hash table에있을 경우 , mnemonic 일 경우
				{
					strcpy((sou+i)->two,temp2);
					if((strcmp((sou+i)->two,"COMPR")==0||strcmp((sou+i)->two,"STCH")==0)||strcmp((sou+i)->two,"LDCH")==0)//콤마가 필요할 경우
					{
						fscanf(p,"%[^,] %c %s%c",temp,&(sou+i)->comma,(sou+i)->four,&enter);
						strcpy((sou+i)->three,rmspace(temp));
					}
					else if(strcmp((sou+i)->two,"RSUB")==0)
					{
						(sou+i)->line=5*i+5;
					}
					else//일반적인 음네모닉
					{
						fscanf(p,"%s%c",(sou+i)->three,&enter);
					}
					//location 설정
					 if(((sou+i)->two)[0]=='+')//+가 앞에 붙어있을 경우 4형식
					 {
						 (sou+i)->loc=start;
						 start+=4;
					 }
					 else if(strcmp((sou+i)->two,"BASE")==0)//위의 경우와 같다.
					 {
						 (sou+i)->loc=-1;
					 }
					 else if(strcmp((sou+i)->two,"RESW")==0)
					 {
						 (sou+i)->loc=start;
						 int t;
						 sscanf((sou+i)->three,"%d",&t);
						 start+=3*t;
					 }
					 else if(strcmp((sou+i)->two,"RESB")==0)
					 {
						 (sou+i)->loc=start;
						 int t;
						 sscanf((sou+i)->three,"%d",&t);
						 start+=t;
					 }
					 else if(strcmp((sou+i)->two,"BYTE")==0)
					 {
						 (sou+i)->loc=start;
						 start+=1;
					 }
					 else//그 외 일반적인 경우
					 {
						 (sou+i)->loc=start;
						 start+=findnum((sou+i)->two);
					 }


				}
				(sou+i)->line=5*i+5;
				i++;
			}
			//여기서부턴 SYMBOL table에 없는 타겟이 어셈 파일에 있을경우 오류를 발생하는 역할을 한다.
			//SYMBOL TABLE을 비워야한다.
			for(i=0;i<=endd;i++)
			{
				char* temp3;
				temp3=(char*)malloc(sizeof(char)*16);//Target 앞에 #이나 @가 붙을 수 있으므로 temp를 이용해 제대로된 스트링을 구한다.
				if(strcmp((sou+i)->two,"BYTE")==0||strcmp((sou+i)->two,"RESW")==0)//예외 처리이다.
					continue;
				if(strcmp((sou+i)->two,"CLEAR")==0||strcmp((sou+i)->two,"STCH")==0)
					continue;
				if(strcmp((sou+i)->two,"COMPR")==0||strcmp((sou+i)->two,"TIXR")==0)
					continue;
				if(strcmp((sou+i)->two,"END")==0)
					continue;

				if((sou+i)->three[0]=='@'||(sou+i)->three[0]=='#')
					temp3=(sou+i)->three+1;
				else
					strcpy(temp3,(sou+i)->three);
				if(temp3[0]<='Z'&&temp3[0]>='A')
				{
					int k;
					int flag=0;//오류 체크 플래그
					for(k=0;k<=endd;k++)
					{
						
						if((sou+k)->one[0]>='A'&&(sou+k)->one[0]<='Z')
						{
							if(strcmp((sou+k)->one,temp3)==0)//있으면 1
							{
								flag=1;break;
							}
		
						}
					}
					if(flag==0)//오류 발생시
					{

						printf("Line num %d has invalid target name\n",i+1);
						return 0;
					}

				}
			}
			if(erflag==1)
			{
				sou=NULL;
				continue;
			}
			FILE* q=fopen(name,"w");
			FILE* r=fopen(name2,"w");

			if(strcmp(sou->two,"START")==0)//START일경우
			{
				fprintf(q,"%5d\t%04X  %-10s %-8s %-9s\n",sou->line,sou->loc,sou->one,sou->two,sou->three);
			}
			else//Start로 시작하지 않을 경우 첫줄만 똑같이 규칙으로 출력해준다.
			{
				sou->ob=object(0);
				fprintf(q,"%5d\t",sou->line);
				if(sou->one[0]=='.')
					fprintf(q,"      .     %s\n",sou->junk);
				else{
					if(strcmp(sou->two,"BASE")!=0)
						fprintf(q,"%04X  ",sou->loc);
					else
						fprintf(q,"      ");
					if(sou->one[0]!='\0')
						fprintf(q,"%-10s",sou->one);
					else
						fprintf(q,"         ");
					if(sou->two[0]=='+')
						fprintf(q,"%-9s",sou->two);
					else
						fprintf(q," %-8s",sou->two);
					if(sou->comma==',')
					{
						char dum[20];
						strcpy(dum,sou->three);
						strcat(dum,",");
						strcat(dum,sou->four);
						fprintf(q," %-9s",dum);
					}
					else
					{
						if(sou->three[0]=='#'||sou->three[0]=='@')
							fprintf(q,"%-10s",sou->three);
						else if(sou->three[0]=='\0')
							fprintf(q,"          ");
						else
							fprintf(q," %-9s",sou->three);
					}
					if(sou->ob==NULL)
						fprintf(q,"\n");
					else
						fprintf(q,"    %s\n",sou->ob);
				}
			}
			for(i=1;i<=endd;i++)//여기서 lst파일에 써주는 역할을 한다.
			{
				fprintf(q,"%5d\t",(sou+i)->line);//라인 출력
				if(((sou+i)->one)[0]=='.')//주석일 경우
				{
					fprintf(q,"      .     %s\n",(sou+i)->junk);
				}
				else if(strcmp((sou+i)->two,"END")==0)//END 어셈 파일의 끝일 경우
				{
					fprintf(q,"\t         %-8s %-9s",(sou+i)->two,(sou+i)->three);
					endd = i;
					break;
				}
				else
				{
					if(strcmp((sou+i)->two,"BASE")!=0)//location을 출력하지 않는다
					{
						fprintf(q,"%04X  ",(sou+i)->loc);
					}
					else
					{
						fprintf(q,"      ");
					}
					if(((sou+i)->one)[0]!='\0')//멀쩡할 경우
					{
						fprintf(q,"%-10s",(sou+i)->one);
					}
					else
						fprintf(q,"          ");

					if(((sou+i)->two)[0]=='+')//+가 붙어져있을 경우
						fprintf(q,"%-9s",(sou+i)->two);

					else
						fprintf(q," %-8s",(sou+i)->two);

					if((sou+i)->comma==',')//콤마가 있을경우 
					{
						char dum[20];
						strcpy(dum,(sou+i)->three);
						strcat(dum,",");
						strcat(dum,(sou+i)->four);
						fprintf(q," %-9s",dum);
					}
					else//일반적인 경우
					{
						if(((sou+i)->three)[0]=='#'||((sou+i)->three)[0]=='@')
							fprintf(q,"%-10s",(sou+i)->three);
						else if(((sou+i)->three)[0]=='\0')
							fprintf(q,"          ");
						else
							fprintf(q," %-9s",(sou+i)->three);
					}
					
					    
					(sou+i)->ob=object(i);//오브젝 코드 생성

					if((sou+i)->ob==NULL)//오브젝 코드가 존재하지않을때
						fprintf(q,"\n");
					else
						fprintf(q,"    %s\n",(sou+i)->ob);


				}
			
			}


			/////////////////////////////////////여기부터 obj 파일 쓰기
			if(strcmp(sou->two,"START")==0)//Start가 있을 때 없을 때 구별
			{
				i=1;
				fprintf(r,"H%-6s%06X%06X\n",sou->one,sou->loc,(((sou+endd)->loc)-(sou->loc)));
			}
			else
			{
				fprintf(r,"H SICXE%06X%06X\n",sou->loc,(((sou+endd)->loc)-(sou->loc)));
				i=0;
			}
			int k;
			while(1)//Text Record
			{
				fprintf(r,"T%06X",(sou+i)->loc);
				int endindex;//한줄 끝 코드의 인덱스
				int lengthend;//한줄 길이
				int length=0;
				for(k=i;;k++)
				{
					if(strcmp((sou+k)->two,"BASE")==0||(sou+k)->one[0]=='.')//예외
						continue;
					else if((k==endd||length>=58)||(strcmp((sou+k)->two,"RESW")==0||strcmp((sou+k)->two,"RESB")==0))//이런 경우들에 obj코드 한줄의 끝을 설정한다.
					{
						endindex=k-1;//그전까지 인덱스를 한줄 끝으로 설정
						lengthend=length;
						break;
					}
					else 
						length+=strlen((sou+k)->ob);//그전까지 길이를 더한다.
				}
				fprintf(r,"%02X",lengthend/2);//코드 길이 
				for(k=i;k<=endindex;k++)
				{
					if(strcmp((sou+k)->two,"BASE")==0||(sou+k)->one[0]=='.')
						continue;
					fprintf(r,"%s",(sou+k)->ob);
				}
				i=k;
				if(i>=endd)//브레이크
					break;
				fprintf(r,"\n");
				while(1)//오브젝 코드가 있는 라인까지 인덱스 증가
				{
					if((sou+i)->ob!=NULL)
						break;
					if((sou+i)->ob==NULL)
						i++;
				}
			}
			fprintf(r,"\n");
			for(i=1;i<=endd;i++)//Modify Record
			{
				if((sou+i)->two[0]=='+'&&((sou+i)->three[0]!='#'))
				{
					fprintf(r,"M0000%02X05\n",(sou+i)->loc+1);
				}
			}
			fprintf(r,"E%06X",sou->loc);
			for(i=0;i<=endd;i++)//symboltable에 저장
			{
				if(strcmp((sou+i)->two,"START")==0)
					continue;
				else if(((sou+i)->one[0]<'A'||(sou+i)->one[0]>'Z'))
					continue;
				else
					addsymbol(i);
			}
			free(sou);
			fclose(p);
			fclose(q);
			fclose(r);
			addh(input2);
			
		}
		else if(strcmp(input,"progaddr")==0)//progaddr를 입력받을 때
		{
			char junk[10];//error check 용도
			junk[0]='\0';
			char addtemp[10];//임시로 받을 문자열
			sscanf(input2,"%s %s %s",input,addtemp,junk);
			if(junk[0]!='\0')
			{
				printf("Error\n");
				continue;
			}
			progAddr=to10(addtemp);//program address에 입력 저장

		}
		else if(strcmp(input,"loader")==0)//loader 명령어
		{
			erflag=0;//초기화
			char name[3][15];
			char junk[10];
			junk[0]='\0';
			name[0][0]='\0';
			name[1][0]='\0';
			name[2][0]='\0';
			filenum=0;//입력되는 파일 개수
			sscanf(input2,"%s %s %s %s %s",input,name[0],name[1],name[2],junk);
			if(name[0][0]=='\0')
			{
				printf("Error\n");
				continue;
			}
			if(name[1][0]=='\0')
				filenum=1;
			else if(name[2][0]=='\0')
				filenum=2;
			else
				filenum=3;
			if(junk[0]!='\0')
			{
				printf("Error\n");
				continue;
			}
			es=(ESTAB*)malloc(sizeof(ESTAB)*filenum);
			int totallength=0;//total length이다.
			for(i=0;i<filenum;i++)//파일 개수만큼 읽어들인다.
			{
				FILE* p=fopen(name[i],"r");
				if(p==NULL)
				{
					printf("No %s FILE!!\n",name[i]);
					erflag=1;
					continue;
				}
				char H;
				fscanf(p,"%c",&H);
				if(H!='H')
				{
					printf("No Head Error\n");
					continue;//다음파일로 스킴
				}
				char* progname;//program name
				progname=(char*)malloc(sizeof(char)*10);
				fscanf(p,"%s",progname);
				progname=rmspace(progname);//빈공간이 있을 수 있으니 빈칸 제거
				for(int k=0;k<i;k++)
				{
					if(strcmp(es[k].progname,progname)==0)
					{
						erflag=1;
						break;
					}
				}
				if(erflag==1)
				{
					printf("The program name is already existed.\n");
					break;
				}
				strcpy(es[i].progname,progname);
				char temp[7];
				fscanf(p,"%6s",temp);//6자리만큼 받는다
				int startaddress=to10(temp);//주소 출발값
				fscanf(p,"%6s",temp);
				int programlength;
				programlength=to10(temp);//obj파일 길이
				char dump;
				fscanf(p,"%c",&dump);
				char dumpstr[100];
				es[i].address=startaddress+progAddr;//SET CSADDR
				es[i].length=programlength;//SET LENGTH
				es[i].head=NULL;
				es[i].r_head=NULL;
				while(1)
				{
					fscanf(p,"%c",&H);
					if(H=='E')//END일경우
						break;
					else if(H=='D')//D record 일 경우
					{
						while(1){
							char* resw;
							resw=(char*)malloc(sizeof(char)*7);
							int resw_add;
							resw[0]='*';
							fscanf(p,"%6s%6s",resw,temp);
							
							resw=rmspace(resw);
							resw_add=to10(temp);//그 변수의 주소 입력
							resw_add+=es[i].address;//초기 주소 더해준다.
							fscanf(p,"%c",&dump);//끝일 때 브레이크
							addes(resw,resw_add,i);//ES TABLE에 추가
							if(dump=='\n')
								break;
							else
							{
								fseek(p,-1,1);
							}
						}

					}
					else if(H=='T')//T record 일 경우
					{
						fscanf(p,"%[^\n]",dumpstr);
						fscanf(p,"%c",&dump);
					}
					else if(H=='M')//Modification record 일 경우
					{
						fscanf(p,"%[^\n]",dumpstr);
						fscanf(p,"%c",&dump);
					}
					else if(H=='R')
					{
						while(1){
							char* rtemp;
							char* resw;
							resw=(char*)malloc(sizeof(char)*7);
							rtemp=(char*)malloc(sizeof(char)*3);
							fscanf(p,"%2s",rtemp);
							fscanf(p,"%6s",resw);
							resw=rmspace(resw);
							add_ref(resw,rtemp,i);
							fscanf(p,"%c",&dump);
							if(dump=='\n')
								break;
							else
								fseek(p,-1,1);
						}
					}

					else
					{
						fscanf(p,"%[^\n]",dumpstr);
						fscanf(p,"%c",&dump);
					}
				}
				progAddr=es[i].address+es[i].length;
				totallength+=es[i].length;
				fclose(p);
			}
			if(erflag==1)
				continue;
			printf("Control		Symbol\n");
			printf("section		name		Address		Length\n");
			printf("------------------------------------------------------\n");
			for(i=0;i<filenum;i++)
			{
				printf("%s				%04X		%04X\n",es[i].progname,es[i].address,es[i].length);
				symbolt* temp;
				temp=es[i].head;
				while(temp!=NULL)
				{
					printf("		%s		%04X\n",temp->symbol,temp->loc);
					temp=temp->link;
				}
			}
			printf("------------------------------------------------------\n");
			printf("				total length	%04X\n",totallength);
			
			memoryend=es[0].address+totallength-1;
			//////////////////////////////여기까지 table에 저장 
			//이제부터 Pass2
			for(i=0;i<filenum;i++)
			{
				FILE* p=fopen(name[i],"r");
				char dumpstr[50];
				char dump;
				char H;
				fscanf(p,"%[^\n]",dumpstr);
				fscanf(p,"%c",&dump);
				while(1)
				{
					fscanf(p,"%c",&H);
					if(H=='T')//T recorde일때 메모리에 로딩
					{
						int startadd;
						char temp[7];
						int linelength;
						fscanf(p,"%6s",temp);
						startadd=to10(temp);//시작 주소
						startadd+=es[i].address;
						fscanf(p,"%2s",temp);
						linelength=to10(temp);//줄 길이
						for(int k=0;k<linelength;k++)
						{
							fscanf(p,"%2s",temp);
							m[startadd+k][0]=temp[0];
							m[startadd+k][1]=temp[1];
						}//Loading 작업이다.
						fscanf(p,"%c",&dump);
					}
					else if(H=='E')
						break;
					else if(H=='M')
					{
						int targetadd;//변경할 주소값
						char temp[7];
						char plus_minus;//+ 혹은 -
						fscanf(p,"%6s",temp);
						targetadd=to10(temp);
						targetadd+=es[i].address;

						fscanf(p,"%*c%*c%c",&plus_minus);
						fscanf(p,"%2s",temp);
						if(temp[0]<='9')//숫자로 들어왔을 경우
						{
							add_num_memory(temp,targetadd,i,plus_minus);//메모리 수정
						}
						else//symbol 그 자체가 들어왔을 경우
						{
							//add_sym_memory(temp,targetadd,i);//메모리 수정
						}
						fscanf(p,"%c",&dump);
						
					}
					else
					{
						fscanf(p,"%[^\n]",dumpstr);
						fscanf(p,"%c",&dump);
					}
				}
			}
			//L=memoryend;
			addh(input2);		
		}
		else if(strcmp(input,"run")==0)//run 명령어
		{
			if(realstart==1)//처음 시작할경우
				L=memoryend;
			if(strcmp(inputn,"run")!=0)//run말고 또다른 뒤에 명령어가 잇을경우
			{
				printf("Error\n");
				continue;
			}
			if(es==NULL)//loader를 하지않았을때
			{
				printf("Error. No loaded Memory.\n");
				continue;
			}
			run();
			addh(input2);
		}
		else if(strcmp(input,"bp")==0)//breakpoint 설정 명령어
		{
			char bp[6];
			sscanf(input2,"%s %s",input,bp);
			if(strcmp(inputn,"bp")==0)//bp만 입력됐을 경우
			{
				printbp();
				addh(input2);
				continue;
			}
			else if(strcmp(bp,"clear")==0)//bp clear
			{
				bpclear();
				addh(input2);
				continue;
			}
			addbp(bp);
			A=0;
			X=0;
			L=0;
			PC=0;
			S=0;
			T=0;
			bptemp=bphead;
			realstart=1;
			realend=0;
			addh(input2);
		}
		else//올바르지않은 입력일 경우 에러
		{
			printf("Error\n");
		}
	}
	deletem();//메모리 해제
	return 0;
}
void addh(char* word)//linked list에 추가하는 함수
{
	node* new;
	new=(node*)malloc(sizeof(node));
	new->link=NULL;
	new->word=word;
	if(head==NULL)
	{
		head=new;
		return;
	}
	else
	{
		node* temp;
		temp=head;
		while(temp->link!=NULL)
			temp=temp->link;
		temp->link=new;
	}
}
void printh()//linked list에 저장된 데이터들을 출력해주는 함수.
{
	node* temp;
	temp=head;
	int num=1;
	while(temp!=NULL)
	{
		printf("\t%-5d%s\n",num,temp->word);
		temp=temp->link;
		num++;
	}
}
void deletem()// linked list에 할당된 메모리를 해제하는 함수이다.
{
	node* temp;
	node* temp2;
	//할당이 안되있을 경우 함수 종료.
	if(head!=NULL)
	{
		temp=head;
		while(temp!=NULL)
		{
			temp2=temp;
			free(temp2->word);
			free(temp2);
			temp=temp->link;
		}
	}
	int i;
	hnode* temp3;
	hnode* temp4;
	for(i=0;i<20;i++)//Hash table에 있는 메모리를 해제시켜준다.
	{
		if(strcmp(table[i]->op,"--")!=0)//링크드 리스트가 없을 경우이다.
		{
			temp3=table[i];
			while(temp3!=NULL)
			{
				temp4=temp3;
				free(temp4);
				temp3=temp3->link;
			}
		}
		else
		{
			temp3=table[i];
			free(temp3);
		}
	}
}
int checkin(char* input)//올바른 16진수가 들어왔는지 확인해주는 함수이다.
{
	int i;
	for(i=0;;i++)
	{
		if(input[i]=='\0')
			break;
		if((input[i]>='0'&&input[i]<='9')||(input[i]>='A'&&input[i]<='F')||(input[i]>='a'&&input[i]<='f'))//올바른 범위 안에 있을때
			continue;
		else
			return 1;
	}
	return 0;
}
int checkin2(char* input)//입력받은 start, end가 중간에 공백이 있거나 길이가 5자리를 넘어가는지 확인해준다.
{
	int i;
	int length=0;
	for(i=0;;i++)
	{
		if(input[i]=='\0')
			return 0;
		if(length>=6)
			return 1;
		if(input[i]==' '||input[i]=='\t')
			return 1;
		length++;
	}

}
char* rmspace(char* input)//빈칸을 지워서 앞으로 땡겨주는 함수이다.
{
	int i;
	int j=0;
	char* result;
	result=(char*)malloc(sizeof(char)*strlen(input));
	for(i=0;;i++)
	{
		if(input[i]=='\0')
			break;
		if(input[i]==' '||input[i]=='\t')
			continue;
		result[j]=input[i];
		j++;
	}
	result[j]='\0';
	return result;
}
char* changestart(char* input)//start 변수를 바꿔주는 함수이다.
{
	char* result;
	int end=strlen(input)-1;
	result=(char*)malloc(sizeof(char)*(end+1));
	int i;
	int nend;
	for(i=end;;i--)//start의 뒤에 공백들을 없애주는 역할을 한다.
	{
		if(i==0)
		{	
			nend=i;
			break;
		}
		
		if(input[i]==' '||input[i]=='\t')
			continue;
		else{
			nend=i;
			break;
		}
	}
	for(i=0;i<=nend;i++)
		result[i]=input[i];
	i++;
	result[i]='\0';
	return result;
}
int to10(char* input)//10진수로 바꿔주는 함수이다.
{
	int length=strlen(input);
	int i;
	int result=0;
	for(i=length-1;i>=0;i--)
	{
		if(input[i]>='A'&&input[i]<='F')
			result+=(input[i]-55)*powe(16,length-i-1);
		else if(input[i]>='a'&&input[i]<='f')
			result+=(input[i]-87)*powe(16,length-i-1);
		else
			result+=(input[i]-48)*powe(16,length-i-1);
	}
	return result;
}
char* to16(int input)//16진수 문자열로 바꿔주는 함수이다.
{
	int* num;
	num=(int*)malloc(sizeof(int)*7);
	char* result;
	result=(char*)malloc(sizeof(char)*7);
	int i;
	int temp;
	if(input>=0)
		temp=input;
	else
		temp=16777215+input+1;
	for(i=0;i<6;i++)
	{
		if(temp<16)
		{
			num[i]=temp;
			break;
		}
		num[i]=temp%16;
		temp=temp/16;
	}
	int check=i;
	num[i+1]=-1;
	int j=0;
	for(i=check;i>=0;i--)
	{
		if(num[i]>=0&&num[i]<=9)
			result[j]=num[i]+'0';
		else
			result[j]=num[i]-10+'A';

		j++;
	}
	result[j]='\0';
	return result;

}
int powe(int one,int two)//one의 two승을 구해준다.
{
	int result=one;
	int i;
	if(two==0)
		return 1;
	else if(two==1)
		return one;
	for(i=0;i<two-1;i++)
		result*=one;
	return result;
}
void addtable(hnode* new)//Hash table에 새로운 노드를 추가해준다.
{
	int i;
	for(i=0;i<20;i++)
	{
		if((table[i]->ins)[0]==(new->ins)[0])//같은 Key일경우이다.
		{
			hnode* temp;
			temp=table[i];
			while(temp->link!=NULL)
				temp=temp->link;
			temp->link=new;
			break;
		}
		else//키가 다르고 
		{
			if(strcmp(table[i]->op,"--")==0)//채워져있지않은 table이면
			{
				table[i]=new;
				break;
			}
			else//이미 채워져있으면
				continue;
		}
	}
}
int findandprint(char* input)//table 내에 input이 있는지 찾아주고 있으면 출력해주고 1을 리턴, 없으면 0을 리턴
{
	int i;
	for(i=0;i<20;i++)
	{
		if(input[0]==(table[i]->ins)[0])//Key 값이 같을 경웅이다.
		{
			hnode* temp;
			temp=table[i];
			while(temp!=NULL&&(strcmp(temp->ins,input)!=0))
				temp=temp->link;
			if(temp==NULL)
			{
				printf("Invalid mnemonic\n");
				return 0;
			}
			printf("opcode is %s\n",temp->op);
			return 1;
		}
	}
	printf("Invalid mnemonic\n");
	return 0;
}
int find(char* input)//Hash table에서 input을 찾아주는 함수
{
	int i;
	if(input[0]=='+')
		input=input+1;
	for(i=0;i<20;i++)
	{
		if(input[0]==(table[i]->ins)[0])
		{
			hnode* temp;
			temp=table[i];
			while(temp!=NULL&&(strcmp(temp->ins,input)!=0))
				temp=temp->link;
			if(temp==NULL)
			{
				return 0;
			}
			return 1;
		}
	}
	return 0;
}
char* findopcode(char* input)//opcode를 찾아 리턴해준다.
{
	int i;
	for(i=0;i<20;i++)
	{
		if(input[0]==(table[i]->ins)[0])
		{
			hnode* temp;
			temp=table[i];
			while(temp!=NULL&&(strcmp(temp->ins,input)!=0))
				temp=temp->link;
			if(temp==NULL)
			{
				printf("No data\n");
				return NULL;
			}
			return temp->op;
		}
	}
	return NULL;
}
int findnum(char* input)//Hash table에서 input의 형식 넘버를 리턴해준다.
{
	int i;
	for(i=0;i<20;i++)
	{
		if(input[0]==(table[i]->ins)[0])
		{
			hnode* temp;
			temp=table[i];
			while(temp!=NULL&&(strcmp(temp->ins,input)!=0))
				temp=temp->link;
			if(temp==NULL)
				return 0;
			return temp->num;
		}
	}
	return 0;
}
void printtable()//Hash table을 다 출력해준다.
{
	int i=0;
	hnode* temp;
	temp=table[0];
	while(i<20)
	{
		printf("%d : ",i);
		if(strcmp(table[i]->op,"--")==0)
		{
			printf("empty\n");
			i++;
			continue;
		}
		temp=table[i];
		
		while(temp!=NULL)
		{
			printf("[%s,%s] ",temp->op,temp->ins);
			temp=temp->link;
			if(temp==NULL)
				break;
			else
			{
				printf("-> ");
			}
		}
		printf("\n");
		i++;
	}
	return;
}
char* object(int i)//Object Code를 리턴해준다.
{
	char* ob=NULL;
	char* op;
	int num;
	if(strcmp((sou+i)->two,"BASE")==0)//예외이다.
		return NULL;
	if(strcmp((sou+i)->two,"BYTE")==0)
	{
		if((sou+i)->three[0]=='C')//예외 처리 캐릭터일경우
		{
			ob=(char*)malloc(sizeof(char)*2);
			for(int k=2;k<=strlen((sou+i)->three)-2;k++)
			{
				if((sou+i)->three[k]==39)
					break;
				else{
					ob=(char*)realloc(ob,sizeof(char)*(2*(k+1)));
					ob[2*(k-2)]=to16((int)((sou+i)->three[k]))[0];
					ob[2*(k-2)+1]=to16((int)((sou+i)->three[k]))[1];
				}	
			}
		}
		else if((sou+i)->three[0]=='X')//16진수 일경우
		{
			ob=(char*)malloc(sizeof(char)*3);
			for(int k=2;k<=strlen((sou+i)->three)-2;k++)
			{
				if((sou+i)->three[k]==39)
					break;
				else
				{
					ob=(char*)realloc(ob,sizeof(char)*((k)));
					ob[(k-2)]=(sou+i)->three[k];
				}
			}

		}
		return ob;
	}
	else if(strcmp((sou+i)->two,"RESW")==0||strcmp((sou+i)->two,"RESB")==0)//예외 처리
		return NULL;
		



	op=(char*)malloc(sizeof(char)*3);
	if((sou+i)->two[0]=='+'){//+가 붙어있을 경우이다.
		num=findnum(((sou+i)->two)+1);
		strcpy(op,findopcode(((sou+i)->two)+1));
	}
	else{
		num=findnum((sou+i)->two);//형식
		strcpy(op,findopcode((sou+i)->two));
	}
        int N=1;//비트들 초기화
	int I=1;
	int x=0;
	int b=0;
	int p=0;
	int e=0;

	if((sou+i)->three[0]=='#')//immediate addressing
	{
		N=0;
		I=1;
	}
	else if((sou+i)->three[0]=='@')//indirect addressing
	{
		N=1;
		I=0;
	}

	if((sou+i)->two[0]=='+'){//4형식임을 알려준다.
		num=4;
		e=1;
	}
	if((sou+i)->comma==','&&(strcmp((sou+i)->two,"STCH")==0||strcmp((sou+i)->two,"LDCH")==0))
	{
		x=1;
		b=1;
	}
	ob=(char*)malloc(sizeof(char)*9);
	
	int targetloc=findtargetloc((sou+i)->three);//target address이다.
	int displace;//타켓과 현재 위치의 주소차이이다.
	if((sou+i+1)->loc==-1)
		displace=targetloc-(sou+i+2)->loc;
	else
		displace=targetloc-(sou+i+1)->loc;
	int temp=x*8+b*4+p*2+e*1;
	char* disp;
	disp=(char*)malloc(sizeof(char)*3);
	//음수면 2의 보수로 변환
	if(strcmp((sou+i)->two,"RSUB")==0)//예외
	{
		ob[0]=op[0];
		ob[1]=op[1]+2*N+I;
		ob[2]='0';
		ob[3]='0';
		ob[4]='0';
		ob[5]='0';
		ob[6]='\0';
		return ob;
	}
	if(strcmp((sou+i)->two,"TIXR")==0)//예외
	{
		ob[0]=op[0];
		ob[1]=op[1];
		ob[2]='5';
		ob[3]='0';
		ob[4]='\0';
		return ob;
	}
        if(num==3)//3형식일때
	{
		ob[0]=op[0];
		ob[1]=op[1]+2*N+I;
		if(op[1]<='9'&&ob[1]>'9'){
			ob[1]+=7;
		}
		else if(ob[1]>'F')//opcode에 ni값을 더했을 경우 자릿수가 넘어갈때이다.
		{
			ob[1]=ob[1]-'F'-1+'0';
			ob[0]++;
			if(ob[0]==58)
				ob[0]='A';
		}
		if(strcmp((sou+i)->two,"STCH")==0||strcmp((sou+i)->two,"LDCH")==0)//이경우엔
		{
			int k;
			for(k=1;k<endd;k++)
			{
				if(strcmp((sou+k)->two,"BASE")==0)
					break;
			}
			displace=targetloc-findtargetloc((sou+k)->three);
			ob[2]=temp+'0';
			if(ob[2]>'9')
				ob[2]+=7;
			ob[3]='0';ob[4]='0';ob[5]='0';
			for(k=strlen(to16(displace))-1;k>=0;k--)
			{
				ob[k-strlen(to16(displace))+6]=to16(displace)[k];//뒤에서부터 채워준다. 나머지는 0으로 채워준다.
			}
			ob[6]='\0';
			return ob;
		}

		if((sou+i)->three[0]=='#')//immediate addressing 일 때
		{
			char dump[10];
			dump[0]='\0';
			char ctarget;
			int target;
			sscanf((sou+i)->three,"%*c%c%s",&ctarget,dump);
			if(ctarget>='0'&&ctarget<='9'){
				sscanf((sou+i)->three,"%*c%d",&target);
			
			//숫자만 있을경우
			
				ob[2]='0';
				ob[3]='0';ob[4]='0';ob[5]='0';
				for(int k=strlen(to16(target))-1;k>=0;k--)
				{
					ob[k-strlen(to16(target))+6]=to16(target)[k];//위와 마찬가징다.
				}
				ob[6]='\0';
				return ob;

			}
		}

		if(displace>=-2048&&displace<=2047)//PC relative일때이다.
			p=1;
		else//Base relative일 때이다.
			b=1;
		if(displace<0&&b!=1){
			temp=x*8+b*4+p*2+e*1;
			ob[2]=temp+'0';//
			ob[3]=complement(displace)[1];
			ob[4]=complement(displace)[2];
			ob[5]=complement(displace)[3];
			ob[6]='\0';
			return ob;
		}
		if(b==1)//Base relative일때 
		{
			temp=x*8+b*4+p*2+e*1;
			int k;
			for(k=1;k<endd;k++)
			{
				if(strcmp((sou+k)->two,"BASE")==0)
					break;
			}
			displace=targetloc-findtargetloc((sou+k)->three);
			ob[2]=temp+'0';
			if(ob[2]>'9')
				ob[2]+=7;
			ob[3]='0';ob[4]='0';ob[5]='0';
			for(k=strlen(to16(displace))-1;k>=0;k--)
			{
				ob[k-strlen(to16(displace))+6]=to16(displace)[k];
			}
			ob[6]='\0';
			return ob;
		}
		if(strlen(to16(displace))==1)//disp가 한자리 일때이다.
		{
			disp[0]='0';
			disp[1]=to16(displace)[0];
		}
		else
			disp=to16(displace);
		temp=x*8+b*4+p*2+e*1;
		ob[2]=temp+'0';
		ob[3]='0';
		ob[4]=disp[0];
		ob[5]=disp[1];
		ob[6]='\0';
	}
	else if(num==2)//2 포멧일 때
	{
		ob[0]=op[0];
		ob[1]=op[1];
		if(strcmp((sou+i)->two,"COMPR")==0)
		{
			if(strcmp((sou+i)->three,"A")==0)
				ob[2]='0';
			else if(strcmp((sou+i)->three,"S")==0)
				ob[2]='4';
			else if(strcmp((sou+i)->three,"X")==0)
				ob[2]='1';
			else if(strcmp((sou+i)->three,"L")==0)
				ob[2]='2';
			else
				ob[2]='8';

			if(strcmp((sou+i)->four,"A")==0)
				ob[3]='0';
			else if(strcmp((sou+i)->four,"S")==0)
				ob[3]='4';
			else if(strcmp((sou+i)->four,"X")==0)
				ob[3]='1';
			else if(strcmp((sou+i)->four,"L")==0)
				ob[3]='2';
			else
				ob[3]='8';
			ob[4]='\0';
			return ob;
		}
		if(strcmp((sou+i)->three,"X")==0)
		{
			ob[2]='1';
			ob[3]='0';
		}
		else if(strcmp((sou+i)->three,"A")==0)
		{
			ob[2]='0';
			ob[3]='0';
		}
		else if(strcmp((sou+i)->three,"S")==0)
		{
			ob[2]='4';
			ob[3]='0';
		}
		ob[4]='\0';
		return ob;
	}
	else if(num==4)//4형식일때이다.
	{
		temp=x*8+b*4+p*2+e*1;
		if(strcmp((sou+i)->two+1,"JSUB")==0||strcmp((sou+i)->two,"+JSUB")==0)
		{
			ob[0]=op[0];
			ob[1]=op[1];
			ob[2]=temp+'0';
			ob[3]='0';
			ob[4]='\0';
			
			strcat(ob,to16(targetloc));
			return ob;
		}
		if((sou+i)->three[0]=='#')//네모닉 앞에 +가 붙고 target 앞에 #이 붙을 때
		{
			ob[0]=op[0]+N*2;
			ob[1]=op[1]+I;
			ob[2]=temp+'0';
			ob[3]='0';
			int tar;
			sscanf((sou+i)->three,"%*c%d",&tar);
			ob[4]='0';
			ob[5]='0';
			ob[6]='0';
			ob[7]='0';
			for(int k=strlen(to16(tar))-1;k>=0;k--)
			{
				ob[8+k-strlen(to16(tar))]=to16(tar)[k];
			}
			ob[8]='\0';
			return ob;
		}
	}
	return ob;


}
int findtargetloc(char* input)//input에 해당하는 니모닉의 location을 리턴해준다.
{
	int i=0;
	char* input2;
	if(input[0]=='#'||input[0]=='@')
		input2=input+1;
	else 
		input2=input;
	for(i=1;i<=endd;i++)
	{
		if(strcmp((sou+i)->one,input2)==0)
		{
			return (sou+i)->loc;
		}
	}
	return -1;
}
char* complement(int num)//음수를 2의 보술 바꿔주는 함수
{
	char* result;
	result=(char*)malloc(sizeof(char)*5);
	result=to16(65535+num+1);
	return result;

}	
void addsymbol(int i)//i번째 심볼을 테이블에 저장
{
	symbolt* new;
	new=(symbolt*)malloc(sizeof(symbolt));
	strcpy(new->symbol,(sou+i)->one);
	new->loc=(sou+i)->loc;
	new->link=NULL;
	if (stable==NULL)
	{
		stable=new;
		return;
	}
	else
	{
		symbolt* temp;
		symbolt* temp2;
		temp=stable;
		temp2=NULL;
		while(strcmp(temp->symbol,new->symbol)>=0&&temp!=NULL)//알파벳 순으로 저장되는 알고리즘
		{
			temp2=temp;
			temp=temp->link;
			if(temp==NULL)
				break;
		}
		if(temp2==NULL)
		{
			new->link=temp;
			stable=new;
		}
		else{
			temp2->link=new;
			new->link=temp;
		}
	}
}
void printsymbol(void)//symbol 테이블을 출력해준다.
{
	symbolt* temp;
	temp=stable;
	while(temp!=NULL)//NULL일 경우 break한다
	{
		if(temp->link==NULL)//마지막줄을 \n 생략
			printf("\t%s\t%04X",temp->symbol,temp->loc);
		else
			printf("\t%s\t%04X\n",temp->symbol,temp->loc);
		temp=temp->link;
	}
}
void addes(char* symbol,int address,int i)//external symbol table에 추가해주는 함수이다.
{
	symbolt* new;
	new=(symbolt*)malloc(sizeof(symbolt));
	strcpy(new->symbol,symbol);
	new->loc=address;
	new->link=NULL;
	if(es[i].head==NULL)//비어있을 경우
	{
		es[i].head=new;
	}
	else//안비어있을 때
	{
		symbolt* temp;
		temp=es[i].head;
		while(temp->link!=NULL)
			temp=temp->link;
		temp->link=new;
	}
	return;
}
void add_ref(char* resw,char* num,int i)//EST 구조체에 외부 참조 변수들을 저장해준다.
{
	ref* rnew;
	rnew=(ref*)malloc(sizeof(ref));
	strcpy(rnew->name,resw);
	rnew->ref_num=to10(num);
	rnew->link=NULL;
	if(es[i].r_head==NULL)
		es[i].r_head=rnew;
	else
	{
		ref* temp;
		temp=es[i].r_head;
		while(temp->link!=NULL)
			temp=temp->link;
		temp->link=rnew;
	}
	return;
}
void add_num_memory(char* temp,int targetadd,int i,char plus_minus)//Memory에 modifciation 내용을 수정해주는 함수
{
	char original[7];
	strcpy(original,m[targetadd]);
	strcat(original,m[targetadd+1]);
	strcat(original,m[targetadd+2]);
	ref* rtemp;
	rtemp=es[i].r_head;
	int add_resw_loc;
	int k;
	if(to10(temp)==1)
	{
		add_resw_loc=es[i].address;
	}
	else{
		char find[7];//외부 참조 심볼
		while(rtemp!=NULL)
		{
			if(rtemp->ref_num==to10(temp))//number가 같으면
			{
				strcpy(find,rtemp->name);
				break;
			}
			rtemp=rtemp->link;
		}//find 찾음
		if(find[0]=='\0')
			printf("Null 값입니다.\n");

		//int add_prog_loc;//프로그램의 더할 주소값
		for(k=0;k<filenum;k++)
		{
			symbolt* stemp;
			stemp=es[k].head;
			while(stemp!=NULL)
			{
				if(strcmp(stemp->symbol,find)==0)
				{
					add_resw_loc=stemp->loc;
					//add_prog_loc=es[k].address;
					break;
				}
				stemp=stemp->link;
			}
		}
	}
	char add_address[7];
	for(k=0;k<6;k++)
		add_address[k]='0';
	add_address[6]='\0';
	int ntemp;
	if(plus_minus=='+')//+일때
		ntemp=to10(original)+add_resw_loc;//+add_prog_loc;//더해줃나
	else//-일때
		ntemp=to10(original)-add_resw_loc;
	int templen=strlen(to16(ntemp));
	for(k=0;k<templen;k++)
	{
		add_address[6-templen+k]=to16(ntemp)[k];//더할 주소 배열 완성
	}
	//이제 다시 메모리에 로딩
	m[targetadd][0]=add_address[0];
	m[targetadd][1]=add_address[1];
	m[targetadd+1][0]=add_address[2];
	m[targetadd+1][1]=add_address[3];
	m[targetadd+2][0]=add_address[4];
	m[targetadd+2][1]=add_address[5];//loading 완료

}
/*void add_sym_memory(char* temp,int targetadd,int i)
{

}*/
void addbp(char bp[7])//breakpoint 추가해주는 함수
{
	/*if(to10(bp)>memoryend)
	{
		printf("Not allowed ranged breakpoint.\n");
		return;
	}*/
	bptb* new;
	new=(bptb*)malloc(sizeof(bptb));
	strcpy(new->breakpoint,bp);
	new->link=NULL;
	if(bphead==NULL)//head가 NULL일경우
	{
		bphead=new;
	}
	else 
	{
		bptb* temp;
		bptb* pre;
		pre=NULL;
		temp=bphead;
		while(temp!=NULL&&to10(new->breakpoint)>to10(temp->breakpoint))
		{
			pre=temp;
			temp=temp->link;
		}
		if(pre==NULL)
		{
			new->link=temp;
			bphead=new;
		}
		else{
			pre->link=new;
			new->link=temp;
		}
	}
	printf("\t[ok] create breakpoint %s\n",bp);
}
void printbp(void)//저장된 breakpoint 출력
{
	if(bphead==NULL)
	{
		printf("There is no breakpoint.\n");
		return;
	}
	else
	{
		printf("\tbreakpoint\n");
		printf("\t----------\n");	
		bptb* temp;
		temp=bphead;
		while(temp!=NULL)
		{
			printf("\t%s\n",temp->breakpoint);
			temp=temp->link;
		}
	}
	return;
}
void bpclear(void)
{
	if(bphead==NULL)
	{
		printf("No breakpoint.\n");
	}
	else
	{
		bptb* temp;
		//bptb* temp2;
		temp=bphead;
		while(temp!=NULL)
		{
			bptb* temp2;
			temp2=temp;
			temp=temp->link;
			free(temp2);
		}
		bphead=NULL;
		bptemp=bphead;
		printf("\t[ok] clear all breakpoints\n");
		return;
	}
}

void run(void)//run해주는 함수
{
	//bptb* temp;
	//temp=bphead;
	//int tempend;//breakpoint
	if(realstart==1)//처음으로 run이 실행될경우
	{
		if(bptemp!=NULL)//breakpoint가 있을경우
		{
			PC=es[0].address;
			tempend=to10(bptemp->breakpoint);
			bptemp=bptemp->link;
		}//처음 시작인데 breakpoint가 없는 설정일경우
		else
		{
			PC=es[0].address;
			tempend=memoryend+2;
		}
	}
	else//처음이 아닐 때
	{
		if(bptemp==NULL)//breakpoint 더이상 존재하지않을때
		{
			tempend=memoryend+3;
		}
		else//breakpoint존재할때
		{
			tempend=to10(bptemp->breakpoint);
			bptemp=bptemp->link;
		}
	}
	realstart=0;
	int plus=0;//PC값을 더하기 위한 변수 // 지역함수에서 PC값이 안변하면 변하게해준다.
	//L=memoryend-1;
	if(PC<=tempend){
	while(1)
	{
		beforePC=PC;
		plus=0;
		//printf("%s%s%s\n\n",m[PC],m[PC+1],m[PC+2]);
		if(PC>tempend)
			break;	

		if(PC>memoryend)
		{
			realend=1;
			break;
		}
		//if(PC>=tempend)//breakpoint를 만날 경우
		//	break;
		char now_m_value[3];
		strcpy(now_m_value,m[PC]);//불러온 메모리 값
		/*if(to10(now_m_value)==0)//빈 메모리
		{
			now_m++;
			continue;//다음 메모리로 넘어간다.
		}*/
		//처음으로 나오는 0이 아닌 메모리값은 mnemonic이다.
		
		if((to10(now_m_value)/4)*4==180)//Clear
		{
			//printf("CLear\n");
			CLEAR();
			PC++;
		}
		else if((to10(now_m_value)>0&&(to10(now_m_value)/4)*4==0)&&(to10(m[PC+1])/16<16&&to10(m[PC+2])!=0))//수정 필요하다
		{
		
			LDA();
			//printf("LDA\n");
		}
		else if((to10(now_m_value)/4)*4==20)//STL
		{
			STL();
			//printf("STL\n");
		}
		else if((to10(now_m_value)/4)*4==60)//J
		{
			J();
			plus++;
		}
		else if((to10(now_m_value)/4)*4==48)//JEQ
		{
			JEQ();
			plus++;
			//printf("JEQ\n");
		}
		else if((to10(now_m_value)/4)*4==40)//COMP
		{
			flag=COMP();
			//printf("COMP\n");
		}
		else if((to10(now_m_value)/4)*4==72)//JSUB
		{
			JSUB();
			plus++;
			//printf("JSUB\n");
		}
		else if((to10(now_m_value)/4)*4==80)//LDCH
		{
			LDCH();
			//printf("LDCH\n");
		}
		else if((to10(now_m_value)/4)*4==76)//RSUB
		{
			//RSUB();
			PC=L;
			plus++;
			//printf("RSUB\n");
		}
		else if((to10(now_m_value)/4)*4==56)//JLT
		{
			JLT();
			plus++;
			//printf("JLT\n");
		}
		else if((to10(now_m_value)/4)*4==12)//STA
		{
			STA();
			//printf("STA\n");
		}
		else if((to10(now_m_value)/4)*4==84)//STCH
		{
			STCH();
			//printf("STCH\n");
		}
		else if((to10(now_m_value)/4)*4==16)//STX
		{
			STX();
			//printf("STX\n");
		}
		else if((to10(now_m_value)/4)*4==104)//LDB
		{
			LDB();
			//printf("LDB\n");
		}
		else if((to10(now_m_value)/4)*4==116)//LDT
		{
			LDT();
			//printf("LDT\n");
		}
		else if((to10(now_m_value)/4)*4==160)//COMPR
		{
			flag=COMPR();
			PC+=1;
			//printf("COMPR\n");
		}
		else if((to10(now_m_value)/4)*4==184)//TIXR
		{
			flag=TIXR();
			//printf("RESULT is %d\n",flag);
			PC+=1;
			//printf("TIXR\n");
		}
		else if((to10(now_m_value)/4)*4==224)//TD
		{
			//TD();
			flag=-1;
			if(to10(m[PC+1])/16==1)//format 4
				PC+=3;
			else//format3
				PC+=2;
			//printf("TD\n");
		}
		else if((to10(now_m_value)/4)*4==220)//WD
		{
			//WD();
			if(to10(m[PC+1])/16==1)
				PC+=3;
			else
				PC+=2;
		}
		else if((to10(now_m_value)/4)*4==216)//RD
		{
			//RD();
			if(to10(m[PC+1])/16==1)
				PC+=3;
			else
				PC+=2;
		}
		else
		{
			PC++;
			plus=1;
		}
		if(plus==0)
			PC++;

		if(PC>=tempend)//breakpoint 만날경우
		{
			
			break;
		}

	}
	}
	if(realend==1)
	{
		printf("\t\tA : %06X	X : %06X\n",A,X);
		printf("\t\tL : %06X	PC: %06X\n",L,PC);
		printf("\t\tB : %06X	S : %06X\n",B,S);
		printf("\t\tT : %06X\n",T);
		//프로그램 끝일 경우

		printf("\tEnd Program\n");
	}
	else//breakpoint가 남아있을경우
	{
		printf("\t\tA : %06X	X : %06X\n",A,X);
		printf("\t\tL : %06X	PC: %06X\n",L,beforePC);
		printf("\t\tB : %06X	S : %06X\n",B,S);
		printf("\t\tT : %06X\n",T);

		printf("\tStop at checkpoint[%X]\n",tempend);
	}


}
int findxbpe(int* x,int* b,int* p,int* e)
{
	int result;
	result=to10(m[PC+1])/16;
	if(result==1)
		*e=1;
	else if(result==2)
		*p=1;
	else if(result==4)
		*b=1;
	else if(result==8)
		*x=1;
	else if(result==9)
	{
		*x=1;
		*e=1;
	}
	else if(result==10)
	{
		*p=1;
		*x=1;
	}
	else if(result==12)
	{
		*b=1;
		*x=1;
	}
	return result;
}
void CLEAR(void)
{
	if(m[PC+1][0]=='0')
		A=0;
	else if(m[PC+1][0]=='1')
		X=0;
	else if(m[PC+1][0]=='2')
		L=0;
	else if(m[PC+1][0]=='3')
		B=0;
	else if(m[PC+1][0]=='4')
		S=0;
	else if(m[PC+1][0]=='5')
		T=0;
	else if(m[PC+1][0]=='8')
		PC=0;
	return;
}
void LDA(void)
{
	int ni=to10(m[PC])-(to10(m[PC])/4)*4;//n,i의 값이다.ex) n=1,i=1면 3
	int format=3;
	int x,b,p,e;
	x=0;
	b=0;
	p=0;
	e=0;
	int ta;//target address이다.
	int disp;
	char temp3[7];
	char temp4[7];
	temp4[0]=m[PC+1][1];
	temp4[1]='\0';
	strcat(temp4,m[PC+2]);
	strcat(temp4,m[PC+3]);//4형식일때 disp

	temp3[0]=m[PC+1][1];
	temp3[1]='\0';
	strcat(temp3,m[PC+2]);//3형식일때 disp
	int k;
	k=findxbpe(&x,&b,&p,&e);
	if(e==1)//FORMAT4
	{
		ta=to10(temp4);
		format=4;
	}
	else if(ni==0)//SIC mnemonic
	{
		ta=to10(temp3);
		if(x==1)
			ta+=X;
	}
	else if(k==0)//FORMAT3 and not pc,b
	{
		disp=to10(temp3);
		ta=disp;
	}
	else if(k==2)//PC relative
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+PC+3;
	}
	else if(k==4)//B relative
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+B;
	}
	else if(k==8)//X indexed
	{
		disp=to10(temp3);
		ta=disp+X;
	}
	else if(k==10)//p, x indexed
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+PC+3+X;
	}
	else if(k==12)//b,x indexed
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+B+X;
	}
	char temp_t[7];
	strcpy(temp_t,m[ta]);
	strcat(temp_t,m[ta+1]);
	strcat(temp_t,m[ta+2]);
	if(ni==0||ni==3)//SIC or simple addressing
	{
		A=to10(temp_t);
	}
	else if(ni==1)//immediate addressing
	{
		A=ta;
	}
	else if(ni==2)//indirect addressing
	{
		ta=to10(temp_t);
		char temp_2[7];
		strcpy(temp_2,m[ta]);
		strcat(temp_2,m[ta+1]);
		strcat(temp_2,m[ta+2]);
		A=to10(temp_2);
	}
	if(format==4)	
		PC+=3;
	else
		PC+=2;
}
void JSUB(void)
{
	int ni=to10(m[PC])-(to10(m[PC])/4)*4;//n,i의 값이다.ex) n=1,i=1면 3
	//int format=3;
	int x,b,p,e;
	x=0;
	b=0;
	p=0;
	e=0;
	int ta;//target address이다.
	int disp;
	char temp3[7];
	char temp4[7];
	temp4[0]=m[PC+1][1];
	temp4[1]='\0';
	strcat(temp4,m[PC+2]);
	strcat(temp4,m[PC+3]);//4형식일때 disp

	temp3[0]=m[PC+1][1];
	temp3[1]='\0';
	strcat(temp3,m[PC+2]);//3형식일때 disp
	int k;
	k=findxbpe(&x,&b,&p,&e);
	if(e==1)//FORMAT4
	{
		ta=to10(temp4);
		L=PC+4;
		//format=4;
	}
	else if(ni==0)//SIC mnemonic
	{
		ta=to10(temp3);
		if(x==1)
			ta+=X;
		L=PC+3;
	}
	else if(k==0)//FORMAT3 and not pc,b
	{
		disp=to10(temp3);
		ta=disp;
		L=PC+3;
	}
	else if(k==2)//PC relative
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+PC+3;
		L=PC+3;
	}
	else if(k==4)//B relative
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+B;
		L=PC+3;
	}
	else if(k==8)//X indexed
	{
		disp=to10(temp3);
		ta=disp+X;
		L=PC+3;
	}
	else if(k==10)//p, x indexed
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+PC+3+X;
		L=PC+3;
	}
	else if(k==12)//b,x indexed
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+B+X;
		L=PC+3;
	}
	char temp_t[7];
	strcpy(temp_t,m[ta]);
	strcat(temp_t,m[ta+1]);
	strcat(temp_t,m[ta+2]);

	if(ni==0||ni==3)//SIC or simple addressing
	{
		PC=ta;
	}
	else if(ni==1)//immediate addressing
	{
		PC=ta;
	}
	else if(ni==2)//indirect addressing
	{
		PC=to10(temp_t);
	}
}
void J(void)
{
	int ni=to10(m[PC])-(to10(m[PC])/4)*4;//n,i의 값이다.ex) n=1,i=1면 3
	//int format=3;
	int x,b,p,e;
	x=0;
	b=0;
	p=0;
	e=0;
	int ta;//target address이다.
	int disp;
	char temp3[7];
	char temp4[7];
	temp4[0]=m[PC+1][1];
	temp4[1]='\0';
	strcat(temp4,m[PC+2]);
	strcat(temp4,m[PC+3]);//4형식일때 disp

	temp3[0]=m[PC+1][1];
	temp3[1]='\0';
	strcat(temp3,m[PC+2]);//3형식일때 disp
	int k;
	k=findxbpe(&x,&b,&p,&e);
	if(e==1)//FORMAT4
	{
		ta=to10(temp4);
		//format=4;
	}
	else if(ni==0)//SIC mnemonic
	{
		ta=to10(temp3);
		if(x==1)
			ta+=X;
	}
	else if(k==0)//FORMAT3 and not pc,b
	{
		disp=to10(temp3);
		ta=disp;
	}
	else if(k==2)//PC relative
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+PC+3;
	}
	else if(k==4)//B relative
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+B;
	}
	else if(k==8)//X indexed
	{
		disp=to10(temp3);
		ta=disp+X;
	}
	else if(k==10)//p, x indexed
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+PC+3+X;
	}
	else if(k==12)//b,x indexed
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+B+X;
	}
	char temp_t[7];
	strcpy(temp_t,m[ta]);
	strcat(temp_t,m[ta+1]);
	strcat(temp_t,m[ta+2]);
	if(ni==0||ni==3)//SIC or simple addressing
	{
		PC=to10(temp_t);
	}
	else if(ni==1)//immediate addressing
	{
		PC=ta;
	}
	else if(ni==2)//indirect addressing
	{
		ta=to10(temp_t);
		/*char temp_2[7];
		printf("ta is %d\n",ta);
		strcpy(temp_2,m[ta]);
		strcat(temp_2,m[ta+1]);
		strcat(temp_2,m[ta+2]);
		PC=to10(temp_2);*/
		PC=ta;
	}
}
void JLT(void)
{
	int ni=to10(m[PC])-(to10(m[PC])/4)*4;//n,i의 값이다.ex) n=1,i=1면 3
	int format=3;
	int x,b,p,e;
	x=0;
	b=0;
	p=0;
	e=0;
	int ta;//target address이다.
	int disp;
	char temp3[7];
	char temp4[7];
	temp4[0]=m[PC+1][1];
	temp4[1]='\0';
	strcat(temp4,m[PC+2]);
	strcat(temp4,m[PC+3]);//4형식일때 disp

	temp3[0]=m[PC+1][1];
	temp3[1]='\0';
	strcat(temp3,m[PC+2]);//3형식일때 disp
	int k;
	k=findxbpe(&x,&b,&p,&e);
	if(e==1)//FORMAT4
	{
		ta=to10(temp4);
		format=4;
	}
	else if(ni==0)//SIC mnemonic
	{
		ta=to10(temp3);
		if(x==1)
			ta+=X;
	}
	else if(k==0)//FORMAT3 and not pc,b
	{
		disp=to10(temp3);
		ta=disp;
	}
	else if(k==2)//PC relative
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+PC+3;
	}
	else if(k==4)//B relative
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+B;
	}
	else if(k==8)//X indexed
	{
		disp=to10(temp3);
		ta=disp+X;
	}
	else if(k==10)//p, x indexed
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+PC+3+X;
	}
	else if(k==12)//b,x indexed
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+B+X;
	}
	char temp_t[7];
	strcpy(temp_t,m[ta]);
	strcat(temp_t,m[ta+1]);
	strcat(temp_t,m[ta+2]);
	if(flag==-1)
	{
		if(ni==0||ni==3)//SIC or simple addressing
		{
			PC=ta;
		}
		else if(ni==1)//immediate addressing
		{
			PC=ta;
		}
		else if(ni==2)//indirect addressing
		{
			PC=to10(temp_t);
		}
	}
	else
	{
		if(format==4)	
			PC+=4;
		else
			PC+=3;
	}
}
void JEQ(void)
{
	int ni=to10(m[PC])-(to10(m[PC])/4)*4;//n,i의 값이다.ex) n=1,i=1면 3
	int format=3;
	int x,b,p,e;
	x=0;
	b=0;
	p=0;
	e=0;
	int ta;//target address이다.
	int disp;
	char temp3[7];
	char temp4[7];
	temp4[0]=m[PC+1][1];
	temp4[1]='\0';
	strcat(temp4,m[PC+2]);
	strcat(temp4,m[PC+3]);//4형식일때 disp

	temp3[0]=m[PC+1][1];
	temp3[1]='\0';
	strcat(temp3,m[PC+2]);//3형식일때 disp
	int k;
	k=findxbpe(&x,&b,&p,&e);
	if(e==1)//FORMAT4
	{
		ta=to10(temp4);
		format=4;
	}
	else if(ni==0)//SIC mnemonic
	{
		ta=to10(temp3);
		if(x==1)
			ta+=X;
	}
	else if(k==0)//FORMAT3 and not pc,b
	{
		disp=to10(temp3);
		ta=disp;
	}
	else if(k==2)//PC relative
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+PC+3;
	}
	else if(k==4)//B relative
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+B;
	}
	else if(k==8)//X indexed
	{
		disp=to10(temp3);
		ta=disp+X;
	}
	else if(k==10)//p, x indexed
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+PC+3+X;
	}
	else if(k==12)//b,x indexed
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+B+X;
	}
	char temp_t[7];
	strcpy(temp_t,m[ta]);
	strcat(temp_t,m[ta+1]);
	strcat(temp_t,m[ta+2]);
	if(flag==0)
	{
		if(ni==0||ni==3)//SIC or simple addressing
		{
			PC=ta;
		}
		else if(ni==1)//immediate addressing
		{
			PC=ta;
		}
		else if(ni==2)//indirect addressing
		{
			ta=to10(temp_t);
			PC=ta;
		}
	}
	else
	{
		if(format==4)	
			PC+=4;
		else
			PC+=3;
	}

}
int COMP(void)
{
	int ni=to10(m[PC])-(to10(m[PC])/4)*4;//n,i의 값이다.ex) n=1,i=1면 3
	int format=3;
	int x,b,p,e;
	x=0;
	b=0;
	p=0;
	e=0;
	int ta;//target address이다.
	int disp;
	char temp3[7];
	char temp4[7];
	temp4[0]=m[PC+1][1];
	temp4[1]='\0';
	strcat(temp4,m[PC+2]);
	strcat(temp4,m[PC+3]);//4형식일때 disp

	temp3[0]=m[PC+1][1];
	temp3[1]='\0';
	strcat(temp3,m[PC+2]);//3형식일때 disp
	int k;
	k=findxbpe(&x,&b,&p,&e);
	if(e==1)//FORMAT4
	{
		ta=to10(temp4);
		format=4;
	}
	else if(ni==0)//SIC mnemonic
	{
		ta=to10(temp3);
		if(x==1)
			ta+=X;
	}
	else if(k==0)//FORMAT3 and not pc,b
	{
		disp=to10(temp3);
		ta=disp;
	}
	else if(k==2)//PC relative
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+PC+3;
	}
	else if(k==4)//B relative
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+B;
	}
	else if(k==8)//X indexed
	{
		disp=to10(temp3);
		ta=disp+X;
	}
	else if(k==10)//p, x indexed
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+PC+3+X;
	}
	else if(k==12)//b,x indexed
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+B+X;
	}
	char temp_t[7];
	strcpy(temp_t,m[ta]);
	strcat(temp_t,m[ta+1]);
	strcat(temp_t,m[ta+2]);
	int data;
	if(ni==0||ni==3)//SIC or simple addressing
	{
		data=to10(temp_t);
		
	}
	else if(ni==1)//immediate addressing
	{
		data=ta;
	}
	else if(ni==2)//indirect addressing
	{
		ta=to10(temp_t);
		char temp_2[7];
		strcpy(temp_2,m[ta]);
		strcat(temp_2,m[ta+1]);
		strcat(temp_2,m[ta+2]);
		data=to10(temp_2);
	}
	if(format==4)	
		PC+=3;
	else
		PC+=2;
	if(A==data)
		return 0;
	else if(A<data)
		return -1;
	else
		return 1;
}
int data_reg(int num)
{
	if(num==0)
		return A;
	else if(num==1)
		return X;
	else if(num==2)
		return L;
	else if(num==8)
		return PC;
	else if(num==3)
		return B;
	else if(num==4)
		return S;
	else
		return T;
}
int COMPR(void)
{
	int reg_f1;
	int reg_f2;
	reg_f1=(to10(m[PC+1]))/16;
	reg_f2=(to10(m[PC+1]))%16;
	if(data_reg(reg_f1)==data_reg(reg_f2))
		return 0;
	else if(data_reg(reg_f1)>data_reg(reg_f2))
		return 1;
	else
		return -1;
}
int TIXR(void)
{
	X++;
	int reg_f1;
	//int reg_f2;
	reg_f1=(to10(m[PC+1]))/16;
	//reg_f2=(to10(m[PC+1]))%16;
	if(reg_f1==0)//compare with A
	{
		if(X==A)
			return 0;
		else if(X<A)
			return -1;
		else
			return 1;
	}
	else if(reg_f1==1)//compare with X
	{
		if(X==X)
			return 0;
		else if(X<X)
			return -1;
		else
			return 1;
	}
	else if(reg_f1==2)//compare with L
	{
		if(X==L)
			return 0;
		else if(X<L)
			return -1;
		else
			return 1;
	}
	else if(reg_f1==8)//compare with PC
	{
		if(X==PC)
			return 0;
		else if(X<PC)
			return -1;
		else
			return 1;
	}
	else if(reg_f1==3)//compare with B
	{
		if(X==B)
			return 0;
		else if(X<B)
			return -1;
		else
			return 1;
	}
	else if(reg_f1==4)//compare with S
	{
		if(X==S)
			return 0;
		else if(X<S)
			return -1;
		else 
			return 1;
	}
	else if(reg_f1==5)//Compare with T
	{
		if(X==T)
			return 0;
		else if(X<T)
			return -1;
		else 
			return 1;
	}
	return 10;
}
void STCH(void)
{
	int ni=to10(m[PC])-(to10(m[PC])/4)*4;//n,i의 값이다.ex) n=1,i=1면 3
	int format=3;
	int x,b,p,e;
	x=0;
	b=0;
	p=0;
	e=0;
	int ta;//target address이다.
	int disp;
	char temp3[7];
	char temp4[7];
	temp4[0]=m[PC+1][1];
	temp4[1]='\0';
	strcat(temp4,m[PC+2]);
	strcat(temp4,m[PC+3]);//4형식일때 disp

	temp3[0]=m[PC+1][1];
	temp3[1]='\0';
	strcat(temp3,m[PC+2]);//3형식일때 disp
	int k;
	k=findxbpe(&x,&b,&p,&e);
	if(e==1)//FORMAT4
	{
		ta=to10(temp4);
		format=4;
	}
	else if(ni==0)//SIC mnemonic
	{
		ta=to10(temp3);
		if(x==1)
			ta+=X;
	}
	else if(k==0)//FORMAT3 and not pc,b
	{
		disp=to10(temp3);
		ta=disp;
	}
	else if(k==2)//PC relative
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+PC+3;
	}
	else if(k==4)//B relative
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+B;
	}
	else if(k==8)//X indexed
	{
		disp=to10(temp3);
		ta=disp+X;
	}
	else if(k==10)//p, x indexed
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+PC+3+X;
	}
	else if(k==12)//b,x indexed
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+B+X;
	}
	char temp_t[7];
	strcpy(temp_t,m[ta]);
	strcat(temp_t,m[ta+1]);
	strcat(temp_t,m[ta+2]);

	if(ni==0||ni==3)//SIC or simple addressing
	{
		char temp[3];
		int t=A%(16*16);
		if(strlen(to16(t))==1)
		{
			temp[0]='0';
			temp[1]=to16(t)[0];
			temp[2]='\0';
			strcpy(m[ta],temp);
		}
		else
		{
			temp[0]=to16(t)[0];
			temp[1]=to16(t)[1];
			temp[2]='\0';
			strcpy(m[ta],temp);
		}
	}
	else if(ni==1)//immediate addressing
	{
		//A=ta;
	}
	else if(ni==2)//indirect addressing
	{
		ta=to10(temp_t);
		char temp[3];
		int t=A%(16*16);
		if(strlen(to16(t))==1)
		{
			temp[0]='0';
			temp[1]=to16(t)[0];
			temp[2]='\0';
			strcpy(m[ta],temp);
		}
		else
		{
			temp[0]=to16(t)[0];
			temp[1]=to16(t)[1];
			temp[2]='\0';
			strcpy(m[ta],temp);
		}
	}
	if(format==4)
		PC+=3;
	else
		PC+=2;
}
void LDCH(void)
{
	int ni=to10(m[PC])-(to10(m[PC])/4)*4;//n,i의 값이다.ex) n=1,i=1면 3
	int format=3;
	int x,b,p,e;
	x=0;
	b=0;
	p=0;
	e=0;
	int ta;//target address이다.
	int disp;
	char temp3[7];
	char temp4[7];
	temp4[0]=m[PC+1][1];
	temp4[1]='\0';
	strcat(temp4,m[PC+2]);
	strcat(temp4,m[PC+3]);//4형식일때 disp

	temp3[0]=m[PC+1][1];
	temp3[1]='\0';
	strcat(temp3,m[PC+2]);//3형식일때 disp
	int k;
	k=findxbpe(&x,&b,&p,&e);
	if(e==1)//FORMAT4
	{
		ta=to10(temp4);
		format=4;
	}
	else if(ni==0)//SIC mnemonic
	{
		ta=to10(temp3);
		if(x==1)
			ta+=X;
	}
	else if(k==0)//FORMAT3 and not pc,b
	{
		disp=to10(temp3);
		ta=disp;
	}
	else if(k==2)//PC relative
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+PC+3;
	}
	else if(k==4)//B relative
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+B;
	}
	else if(k==8)//X indexed
	{
		disp=to10(temp3);
		ta=disp+X;
	}
	else if(k==10)//p, x indexed
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+PC+3+X;
	}
	else if(k==12)//b,x indexed
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+B+X;
	}
	char temp_t[7];
	strcpy(temp_t,m[ta]);
	strcat(temp_t,m[ta+1]);
	strcat(temp_t,m[ta+2]);

	if(ni==0||ni==3)//SIC or simple addressing
	{
		A=(A/(16*16))*16*16+to10(m[ta]);
	}
	else if(ni==1)//immediate addressing
	{
		A=(A/(16*16))*16*16+ta/(16*16*16*16);
	}
	else if(ni==2)//indirect addressing
	{
		ta=to10(temp_t);
		A=(A/(16*16))*16*16+to10(m[ta]);
	}
	if(format==4)	
		PC+=3;
	else
		PC+=2;	
}
void LDT(void)
{
	int ni=to10(m[PC])-(to10(m[PC])/4)*4;//n,i의 값이다.ex) n=1,i=1면 3
	int format=3;
	int x,b,p,e;
	x=0;
	b=0;
	p=0;
	e=0;
	int ta;//target address이다.
	int disp;
	char temp3[7];
	char temp4[7];
	temp4[0]=m[PC+1][1];
	temp4[1]='\0';
	strcat(temp4,m[PC+2]);
	strcat(temp4,m[PC+3]);//4형식일때 disp

	temp3[0]=m[PC+1][1];
	temp3[1]='\0';
	strcat(temp3,m[PC+2]);//3형식일때 disp
	int k;
	k=findxbpe(&x,&b,&p,&e);
	if(e==1)//FORMAT4
	{
		ta=to10(temp4);
		format=4;
	}
	else if(ni==0)//SIC mnemonic
	{
		ta=to10(temp3);
		if(x==1)
			ta+=X;
	}
	else if(k==0)//FORMAT3 and not pc,b
	{
		disp=to10(temp3);
		ta=disp;
	}
	else if(k==2)//PC relative
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+PC+3;
	}
	else if(k==4)//B relative
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+B;
	}
	else if(k==8)//X indexed
	{
		disp=to10(temp3);
		ta=disp+X;
	}
	else if(k==10)//p, x indexed
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+PC+3+X;
	}
	else if(k==12)//b,x indexed
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+B+X;
	}
	char temp_t[7];
	strcpy(temp_t,m[ta]);
	strcat(temp_t,m[ta+1]);
	strcat(temp_t,m[ta+2]);

	if(ni==3)//simple addressing
	{
		T=to10(temp_t);
	}
	else if(ni==1)//immediate addressing
	{
		T=ta;
	}
	else if(ni==2)//indirect addressing
	{
		ta=to10(temp_t);
		char temp_2[7];
		strcpy(temp_2,m[ta]);
		strcat(temp_2,m[ta+1]);
		strcat(temp_2,m[ta+2]);
		T=to10(temp_2);
	}
	if(format==4)	
		PC+=3;
	else
		PC+=2;	
}
void LDB(void)
{
	int ni=to10(m[PC])-(to10(m[PC])/4)*4;//n,i의 값이다.ex) n=1,i=1면 3
	int format=3;
	int x,b,p,e;
	x=0;
	b=0;
	p=0;
	e=0;
	int ta;//target address이다.
	int disp;
	char temp3[7];
	char temp4[7];
	temp4[0]=m[PC+1][1];
	temp4[1]='\0';
	strcat(temp4,m[PC+2]);
	strcat(temp4,m[PC+3]);//4형식일때 disp

	temp3[0]=m[PC+1][1];
	temp3[1]='\0';
	strcat(temp3,m[PC+2]);//3형식일때 disp
	int k;
	k=findxbpe(&x,&b,&p,&e);
	if(e==1)//FORMAT4
	{
		ta=to10(temp4);
		format=4;
	}
	else if(k==0)//FORMAT3 and not pc,b
	{
		disp=to10(temp3);
		ta=disp;
	}
	else if(k==2)//PC relative
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+PC+3;
	}
	else if(k==4)//B relative
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+B;
	}
	else if(k==8)//X indexed
	{
		disp=to10(temp3);
		ta=disp+X;
	}
	else if(k==10)//p, x indexed
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+PC+3+X;
	}
	else if(k==12)//b,x indexed
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+B+X;
	}
	char temp_t[7];
	strcpy(temp_t,m[ta]);
	strcat(temp_t,m[ta+1]);
	strcat(temp_t,m[ta+2]);

	if(ni==3)//simple addressing
	{
		B=to10(temp_t);
	}
	else if(ni==1)//immediate addressing
	{
		B=ta;
	}
	else if(ni==2)//indirect addressing
	{
		ta=to10(temp_t);
		char temp_2[7];
		strcpy(temp_2,m[ta]);
		strcat(temp_2,m[ta+1]);
		strcat(temp_2,m[ta+2]);
		B=to10(temp_2);
	}
	if(format==4)	
		PC+=3;
	else
		PC+=2;
}
void STX(void)
{
	int ni=to10(m[PC])-(to10(m[PC])/4)*4;//n,i의 값이다.ex) n=1,i=1면 3
	int format=3;
	int x,b,p,e;
	x=0;
	b=0;
	p=0;
	e=0;
	int ta;//target address이다.
	int disp;
	char temp3[7];
	char temp4[7];
	temp4[0]=m[PC+1][1];
	temp4[1]='\0';
	strcat(temp4,m[PC+2]);
	strcat(temp4,m[PC+3]);//4형식일때 disp

	temp3[0]=m[PC+1][1];
	temp3[1]='\0';
	strcat(temp3,m[PC+2]);//3형식일때 disp
	int k;
	k=findxbpe(&x,&b,&p,&e);
	if(e==1)//FORMAT4
	{
		ta=to10(temp4);
		format=4;
	}
	else if(ni==0)//SIC mnemonic
	{
		ta=to10(temp3);
		if(x==1)
			ta+=X;
	}
	else if(k==0)//FORMAT3 and not pc,b
	{
		disp=to10(temp3);
		ta=disp;
	}
	else if(k==2)//PC relative
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+PC+3;
	}
	else if(k==4)//B relative
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+B;
	}
	else if(k==8)//X indexed
	{
		disp=to10(temp3);
		ta=disp+X;
	}
	else if(k==10)//p, x indexed
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+PC+3+X;
	}
	else if(k==12)//b,x indexed
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+B+X;
	}
	char temp_t[7];
	strcpy(temp_t,m[ta]);
	strcat(temp_t,m[ta+1]);
	strcat(temp_t,m[ta+2]);

	if(ni==0||ni==3)//SIC and simple addressing
	{
		char temp[3];
		int t=X/(16*16*16*16);
		if(strlen(to16(t))==1)
		{
			temp[0]='0';
			temp[1]=to16(t)[0];
			temp[2]='\0';
			strcpy(m[ta],temp);
		}
		else
		{
			temp[0]=to16(t)[0];
			temp[1]=to16(t)[1];
			temp[2]='\0';
			strcpy(m[ta],temp);
		}
		t=(X%(16*16*16*16))/(16*16);
		if(strlen(to16(t))==1)
		{
			temp[0]='0';
			temp[1]=to16(t)[0];
			temp[2]='\0';
			strcpy(m[ta+1],temp);
		}
		else
		{
			temp[0]=to16(t)[0];
			temp[1]=to16(t)[1];
			temp[2]='\0';
			strcpy(m[ta+1],temp);
		}
		t=X%(16*16);
		if(strlen(to16(t))==1)
		{
			temp[0]='0';
			temp[1]=to16(t)[0];
			temp[2]='\0';
			strcpy(m[ta+2],temp);
		}
		else
		{
			temp[0]=to16(t)[0];
			temp[1]=to16(t)[1];
			temp[2]='\0';
			strcpy(m[ta+2],temp);
		}
	}
	else if(ni==2)//indirect addressing
	{
		ta=to10(temp_t);
		char temp[3];
		int t=X/(16*16*16*16);
		if(strlen(to16(t))==1)
		{
			temp[0]='0';
			temp[1]=to16(t)[0];
			temp[2]='\0';
			strcpy(m[ta],temp);
		}
		else
		{
			temp[0]=to16(t)[0];
			temp[1]=to16(t)[1];
			temp[2]='\0';
			strcpy(m[ta],temp);
		}
		t=(X%(16*16*16*16))/(16*16);
		if(strlen(to16(t))==1)
		{
			temp[0]='0';
			temp[1]=to16(t)[0];
			temp[2]='\0';
			strcpy(m[ta+1],temp);
		}
		else
		{
			temp[0]=to16(t)[0];
			temp[1]=to16(t)[1];
			temp[2]='\0';
			strcpy(m[ta+1],temp);
		}
		t=X%(16*16);
		if(strlen(to16(t))==1)
		{
			temp[0]='0';
			temp[1]=to16(t)[0];
			temp[2]='\0';
			strcpy(m[ta+2],temp);
		}
		else
		{
			temp[0]=to16(t)[0];
			temp[1]=to16(t)[1];
			temp[2]='\0';
			strcpy(m[ta+2],temp);
		}


	}
	if(format==4)	
		PC+=3;
	else
		PC+=2;	
}
void STA(void)
{
	int ni=to10(m[PC])-(to10(m[PC])/4)*4;//n,i의 값이다.ex) n=1,i=1면 3
	int format=3;
	int x,b,p,e;
	x=0;
	b=0;
	p=0;
	e=0;
	int ta;//target address이다.
	int disp;
	char temp3[7];
	char temp4[7];
	temp4[0]=m[PC+1][1];
	temp4[1]='\0';
	strcat(temp4,m[PC+2]);
	strcat(temp4,m[PC+3]);//4형식일때 disp

	temp3[0]=m[PC+1][1];
	temp3[1]='\0';
	strcat(temp3,m[PC+2]);//3형식일때 disp
	int k;
	k=findxbpe(&x,&b,&p,&e);
	if(e==1)//FORMAT4
	{
		ta=to10(temp4);
		format=4;
	}
	else if(ni==0)//SIC mnemonic
	{
		ta=to10(temp3);
		if(x==1)
			ta+=X;
	}
	else if(k==0)//FORMAT3 and not pc,b
	{
		disp=to10(temp3);
		ta=disp;
	}
	else if(k==2)//PC relative
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+PC+3;
	}
	else if(k==4)//B relative
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+B;
	}
	else if(k==8)//X indexed
	{
		disp=to10(temp3);
		ta=disp+X;
	}
	else if(k==10)//p, x indexed
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+PC+3+X;
	}
	else if(k==12)//b,x indexed
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+B+X;
	}
	char temp_t[7];
	strcpy(temp_t,m[ta]);
	strcat(temp_t,m[ta+1]);
	strcat(temp_t,m[ta+2]);

	if(ni==0||ni==3)//SIC and simple addressing
	{
		char temp[3];
		int t=A/(16*16*16*16);
		if(strlen(to16(t))==1)
		{
			temp[0]='0';
			temp[1]=to16(t)[0];
			temp[2]='\0';
			strcpy(m[ta],temp);
		}
		else
		{
			temp[0]=to16(t)[0];
			temp[1]=to16(t)[1];
			temp[2]='\0';
			strcpy(m[ta],temp);
		}
		t=(A%(16*16*16*16))/(16*16);
		if(strlen(to16(t))==1)
		{
			temp[0]='0';
			temp[1]=to16(t)[0];
			temp[2]='\0';
			strcpy(m[ta+1],temp);
		}
		else
		{
			temp[0]=to16(t)[0];
			temp[1]=to16(t)[1];
			temp[2]='\0';
			strcpy(m[ta+1],temp);
		}
		t=A%(16*16);
		if(strlen(to16(t))==1)
		{
			temp[0]='0';
			temp[1]=to16(t)[0];
			temp[2]='\0';
			strcpy(m[ta+2],temp);
		}
		else
		{
			temp[0]=to16(t)[0];
			temp[1]=to16(t)[1];
			temp[2]='\0';
			strcpy(m[ta+2],temp);
		}
	}
	else if(ni==2)//indirect addressing
	{
		ta=to10(temp_t);
		char temp[3];
		int t=A/(16*16*16*16);
		if(strlen(to16(t))==1)
		{
			temp[0]='0';
			temp[1]=to16(t)[0];
			temp[2]='\0';
			strcpy(m[ta],temp);
		}
		else
		{
			temp[0]=to16(t)[0];
			temp[1]=to16(t)[1];
			temp[2]='\0';
			strcpy(m[ta],temp);
		}
		t=(A%(16*16*16*16))/(16*16);
		if(strlen(to16(t))==1)
		{
			temp[0]='0';
			temp[1]=to16(t)[0];
			temp[2]='\0';
			strcpy(m[ta+1],temp);
		}
		else
		{
			temp[0]=to16(t)[0];
			temp[1]=to16(t)[1];
			temp[2]='\0';
			strcpy(m[ta+1],temp);
		}
		t=A%(16*16);
		if(strlen(to16(t))==1)
		{
			temp[0]='0';
			temp[1]=to16(t)[0];
			temp[2]='\0';
			strcpy(m[ta+2],temp);
		}
		else
		{
			temp[0]=to16(t)[0];
			temp[1]=to16(t)[1];
			temp[2]='\0';
			strcpy(m[ta+2],temp);
		}
	}
	if(format==4)	
		PC+=3;
	else
		PC+=2;	
}
void STL(void)
{
	int ni=to10(m[PC])-(to10(m[PC])/4)*4;//n,i의 값이다.ex) n=1,i=1면 3
	int format=3;
	int x,b,p,e;
	x=0;
	b=0;
	p=0;
	e=0;
	int ta;//target address이다.
	int disp;
	char temp3[7];
	char temp4[7];
	temp4[0]=m[PC+1][1];
	temp4[1]='\0';
	strcat(temp4,m[PC+2]);
	strcat(temp4,m[PC+3]);//4형식일때 disp

	temp3[0]=m[PC+1][1];
	temp3[1]='\0';
	strcat(temp3,m[PC+2]);//3형식일때 disp
	int k;
	k=findxbpe(&x,&b,&p,&e);
	if(e==1)//FORMAT4
	{
		ta=to10(temp4);
		format=4;
	}
	else if(ni==0)//SIC mnemonic
	{
		ta=to10(temp3);
		if(x==1)
			ta+=X;
	}
	else if(k==0)//FORMAT3 and not pc,b
	{
		disp=to10(temp3);
		ta=disp;
	}
	else if(k==2)//PC relative
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+PC+3;
	}
	else if(k==4)//B relative
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+B;
	}
	else if(k==8)//X indexed
	{
		disp=to10(temp3);
		ta=disp+X;
	}
	else if(k==10)//p, x indexed
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+PC+3+X;
	}
	else if(k==12)//b,x indexed
	{
		disp=to10(temp3);
		if(disp>=0x800)
			disp=disp-0xfff-0x1;
		ta=disp+B+X;
	}
	char temp_t[7];
	strcpy(temp_t,m[ta]);
	strcat(temp_t,m[ta+1]);
	strcat(temp_t,m[ta+2]);

	if(ni==0||ni==3)//SIC and simple addressing
	{
		char temp[3];
		int t=L/(16*16*16*16);
		if(strlen(to16(t))==1)
		{
			temp[0]='0';
			temp[1]=to16(t)[0];
			temp[2]='\0';
			strcpy(m[ta],temp);
		}
		else
		{
			temp[0]=to16(t)[0];
			temp[1]=to16(t)[1];
			temp[2]='\0';
			strcpy(m[ta],temp);
		}
		t=(L%(16*16*16*16))/(16*16);
		if(strlen(to16(t))==1)
		{
			temp[0]='0';
			temp[1]=to16(t)[0];
			temp[2]='\0';
			strcpy(m[ta+1],temp);
		}
		else
		{
			temp[0]=to16(t)[0];
			temp[1]=to16(t)[1];
			temp[2]='\0';
			strcpy(m[ta+1],temp);
		}
		t=L%(16*16);
		if(strlen(to16(t))==1)
		{
			temp[0]='0';
			temp[1]=to16(t)[0];
			temp[2]='\0';
			strcpy(m[ta+2],temp);
		}
		else
		{
			temp[0]=to16(t)[0];
			temp[1]=to16(t)[1];
			temp[2]='\0';
			strcpy(m[ta+2],temp);
		}
	}
	else if(ni==2)//indirect addressing
	{
		ta=to10(temp_t);
		char temp[3];
		int t=L/(16*16*16*16);
		if(strlen(to16(t))==1)
		{
			temp[0]='0';
			temp[1]=to16(t)[0];
			temp[2]='\0';
			strcpy(m[ta],temp);
		}
		else
		{
			temp[0]=to16(t)[0];
			temp[1]=to16(t)[1];
			temp[2]='\0';
			strcpy(m[ta],temp);
		}
		t=(L%(16*16*16*16))/(16*16);
		if(strlen(to16(t))==1)
		{
			temp[0]='0';
			temp[1]=to16(t)[0];
			temp[2]='\0';
			strcpy(m[ta+1],temp);
		}
		else
		{
			temp[0]=to16(t)[0];
			temp[1]=to16(t)[1];
			temp[2]='\0';
			strcpy(m[ta+1],temp);
		}
		t=L%(16*16);
		if(strlen(to16(t))==1)
		{
			temp[0]='0';
			temp[1]=to16(t)[0];
			temp[2]='\0';
			strcpy(m[ta+2],temp);
		}
		else
		{
			temp[0]=to16(t)[0];
			temp[1]=to16(t)[1];
			temp[2]='\0';
			strcpy(m[ta+2],temp);
		}


	}
	if(format==4)	
		PC+=3;
	else
		PC+=2;	
}














