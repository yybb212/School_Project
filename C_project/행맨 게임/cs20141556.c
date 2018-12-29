#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int play_game(char id[10][9],char pw[10][9],int score[10]);//행맨 게임이 실행되는 함수
void ranking(char id[10][9],int score[10]);//랭킹을 출력해주는 함수
int str_len(char*);//string의 길이를 return해주는 함수
int str_cmp(char *,char *);//두개의 string을 비교해서 같으면 0, 다르면 1을 return 해주는 함수
void str_cpy(char *,char *);//첫번째 parameter의 string을 두번째 parameter의 string으로 복사하는 함수

int main()
{
  FILE* fp=fopen("User.txt","rt");//파일 입출력 스트림, 배열 등 온갖 변수 설정
  int i,j,k;
  int num;
  int least,temp;
  char id[10][9];//텍스트에 저장되잇는 정보
  char pw[10][9];
  int score[10];
  char userid[9];//입력받은 사용자 정보
  char userpw[9];
  int series[10];//랭킹에 사용되는 배열
  char rankid[10][9];
  char aa[9];

  for(i=0;i<10;i++)//텍스트에 저장되어있는 정보를 불러온다.
  {
    fscanf(fp,"%s",id[i]);
    fscanf(fp,"%s",pw[i]);
    fscanf(fp,"%d",&score[i]);
    fgetc(fp);
  }
  for(i=0;i<10;i++)//배열 복사
  {
    series[i]=score[i];
  }
  for(i=0;i<10;i++)//배열 복사
  {
    str_cpy(rankid[i],id[i]);
  }
  for(i=0;i<9;i++)//아이디별 점수를 내림차순으로 바꿔 다시 배열에 저장, 아이디 번호도 같이 바뀐다.   
  {       
    least=i;      
    for(j=i+1;j<10;j++)     
    {         
      if(series[j]>series[least])         
      {            
        least=j;       
      }   
    }     
    temp=series[i];    
    series[i]=series[least];     
    series[least]=temp;    
    str_cpy(aa,rankid[i]);
    str_cpy(rankid[i],rankid[least]);
    str_cpy(rankid[least],aa);
  } 


  
  printf("<Menu>\n");//메인 메뉴
  printf("1. Play game\n");
  printf("2. Ranking\n");
  printf("3. Exit\n");
  printf("Select menu : ");
  scanf("%d",&num);
  switch(num)//메인 메뉴 선택지
  {
    case 1:{

        play_game(id,pw,score);//행맨 게임 실행
    
      break;
    }
    case 2:{
      printf(" Rank     User ID       Score\n");//랭킹 보여주기
      for(i=0;i<10;i++)
      {
        printf("%5d%12s%12d\n",i+1,rankid[i],series[i]);
      }

      
      break;
      
    }
    case 3:{
      printf("Game end\n");
      return -1;
    }
  }


}
int play_game(char id[10][9],char pw[10][9],int score[10])
{
  FILE* fp=fopen("User.txt","rt");//파일 입출력 및 모든 변수 선언 및 초기화
  FILE* fb=fopen("User.txt","wt");
  int i,j,k;
  int num;
  int correct=0,correct2=0;
  int idnum;
  char userid[9];
  char userpw[9];

  FILE* fp2=fopen("Vocab.txt","rt");
  char voc[50][15]={0};
  char inf[50][15]={0};
  char answer[15]={0};
  char input;
  int life=10;
  int jari;
  int nansu;
  int gaesu=0;
  int jumsu=0;
  int hint=1,pass=1;
  int hint2=1,pass2=1;
  int vocabnum,linenum;
  for(i=0;i<10;i++)//다시한번 입력
  {
    fscanf(fp,"%s",id[i]);
    fscanf(fp,"%s",pw[i]);
    fscanf(fp,"%d",&score[i]);
    fgetc(fp);
  }


  for(i=0;i<50;i++)
  {
    fscanf(fp2,"%s",voc[i]);//단어들 배열에 저장
    fscanf(fp2,"%s",inf[i]);//단어정보도 배열에 저장
    fgetc(fp2);
  }
  printf("ID : ");
  scanf("%s",userid);
  printf("PW : ");
  scanf("%s",userpw);

  for(i=0;i<10;i++)//아이디 검색
  {
    if(str_cmp(userid,id[i])==0)
    {
      correct=1;
      idnum=i;
      break;
    }
  }
  if(str_cmp(userpw,pw[idnum])==0)//비밀 번호 일치하는지 확인
  {
    correct2=1;
  }

  if(correct!=1)//아이디가 없으면
  {
    printf("There is no ID<%s>\n",userid);
    for(i=0;i<10;i++)//원래 대로 출력
    {
      fprintf(fb,"%s %s %d\n",id[i],pw[i],score[i]);
    }

    fclose(fb);
    return -1;
  }
  else if(correct2!=1)//비밀번호가 일치하지 않으면
  {
    printf("PW is not correct!\n");
    for(i=0;i<10;i++)//원래대로 출력
    {
      fprintf(fb,"%s %s %d\n",id[i],pw[i],score[i]);
    }

    fclose(fb);
    return -1;
  }
  else
  {
    printf("Login complete\n");
  }


  while(pass==1 || pass==0)//패스 힌트 개수에 따라 다르다
  {
  srand(time(NULL));//난수 생성
  nansu=rand();//난수 생성
  vocabnum=nansu%50;
  linenum=str_len(voc[vocabnum]);//단어 자리수

  for(i=0;i<linenum;i++)
  {
    answer[i]='_';
  }

    

//while
while(1)
{
  for(i=0;i<10;i++)
  {
    fscanf(fp,"%s",id[i]);
    fscanf(fp,"%s",pw[i]);
    fscanf(fp,"%d",&score[i]);
    fgetc(fp);
  }

  if(life==0)//라이프가 0일 경우
  { 
    printf("Your life is 0!! Game Over...\n");
    for(i=0;i<10;i++)
    {
      fprintf(fb,"%s %s %d\n",id[i],pw[i],score[i]);
    }

     fclose(fb);
     return 1;//게임 종료
   }
  else if(str_cmp(answer,voc[vocabnum])==0)//다 맞추면
  {
    printf("Great~!\n");
    if(life==10)//라이프가 10일 때 점수 계산
    {
      jumsu=linenum*2+10;
    }
    else//일반 점수 계산
    {
      jumsu=linenum+life;
    }
    
    printf("Correct! The word is %s\n",voc[vocabnum]);
    printf("The score that you get is %d\n",jumsu);
    printf("Your current score is %d\n",score[idnum]);
    score[idnum]=score[idnum]+jumsu;
    printf("Your total score is %d\n",score[idnum]);
    for(i=0;i<10;i++)//출력
    {
      fprintf(fb,"%s %s %d\n",id[i],pw[i],score[i]);
    }


    return 1;
  }
   else//알파벳 입력
   {
     gaesu=0;
     printf("Life : %d\n",life);
     linenum=str_len(voc[vocabnum]);
     printf("Word : ");
     for(i=0;i<linenum;i++)
     {
       printf("%c ",answer[i]);
     }
     printf("\n");
     printf("Category : %s\n",inf[vocabnum]);
     printf("1. Character hint(count : %d) 2. Word pass(count : %d)\n",hint,pass);//남은 힌트 개수
     printf("Input alphabet or item number: ");//알파벳 입력
     scanf(" %c",&input);
     if(input=='1')//캐릭터 힌트
     {
       if(hint==0)
       {
         printf("Error! You don't have character hint\n");
         continue;
       }
       printf("Select word column to see (1 ~ %d) : ",linenum);
       scanf("%d",&jari);
       printf("Alphabet which you select is %c\n",voc[vocabnum][jari-1]);
       hint--;
       continue;
     }
     else if(input=='2')//워드 패스 힌트
     {
       if(pass==0)
       {
         printf("Error! You don't have word pass\n");
         continue;
       }
       printf("You use work pass!!\n");
       pass--;
      
       break;
     }

     for(i=0;i<linenum;i++)//입력받은 알파벳이 단어에 있으면
     {
       if(voc[vocabnum][i]==input)
       {
         answer[i]=input;
         gaesu++;
       }
     }
     if(gaesu==0)//알파벳이 단어에 없으면
     {
       life--;//라이프 1 감소
     }
     else
     {
       continue;
     }
    
    }
  }
}
if(pass==-1)
{
  printf("Error! You don't have word pass\n");
  fclose(fb);
  return -1;
}

}





int str_cmp(char *s, char *t)

{

  int i;

  for(i=0;s[i]==t[i];i++)//비교한다

    if(s[i]=='\0')

      return 0;

      return s[i]-t[i];

}
int str_len(char *a)
{
  int i=0;//인덱스 변수 선언
  int count=0;//카운트 변수 선언
  while(a[i++]!='\0')
  {
    count++;//count를 증가시켜서 개수구함
  }
  return count;
}
void str_cpy(char *a,char *b)
{
  int i=0,j=0;
  char *copy=a;//포인터에 파라미터 저장
  while(b[i]!='\0')
    copy[j++]=b[i++];//복사한다
    copy[j]='\0';
}

