#include "management.h"

int main()
{
  int exit=0;
  int exit2=0;
  int anykey;
  int login_flag=0;
  initscr();
  clear();
  Create_Struct();
  if(TOP->ST_YEAR==NULL){//파일이 존재하지 않을때
	  endwin();
	  return 0;
  }
  while(!exit)
  { 
	//initscr();
	clear();
	echo();
	exit2=0;
	//noecho();
	switch(Account_Manage()){
		case MENU_LOGIN:
			clear();
			printw("Student Number:");//학번 ID 입력
			scanw("%s",Curr_Num);//비밀번호 입력
			noecho();
			printw("Password:");
			scanw("%s",Curr_Pass);
			login_flag=login();
			if(login_flag==1)//로그인 완료!!
			{
				while(!exit2){
				clear();
				switch(menu()){
					case MENU_ASSIGN:
						Search_Assign();

						break;
					case MENU_CGPA:
						Search_CGPA();
						break;
					case MENU_CHANGE:
						Change_Password();
						break;
					case MENU_LOGOUT:
						exit2=1;
						break;
				}
				}
			}
			else//로그인이 안되었을 때
			{
				printw("Invalid ID or Invalid Password!\n");
				printw("You will be returned to first menu\n");
				printw("Please input any key\n");
				getch();
				refresh();

			}
			break;
		case MENU_NEW:
			New_Account();
			break;
		case MENU_DEL:
			Delete_Account();
			break;
		case MENU_TEMP:
			Temp_Password();
			break;
		case MENU_QUIT: exit=1;break;
		
		//default: printw("---Invalid Input!---\n");
	}

	
  }
  endwin();
  Save_Data();
  free(TOP);
  system("clear");
  return 0;
}
void Save_Data()
{
  int i,j,k;
  int current_year;
  int current_num;
  int current_assign;
  int current_cgpa;
  FILE* fpoint;
  fpoint=fopen("data.txt","wt");
  current_year=TOP->Year_Size;
  fprintf(fpoint,"%d\n",current_year);
  for(i=0;i<current_year;i++)
  {
	  fprintf(fpoint,"%s %d\n",TOP->ST_YEAR[i].year,TOP->ST_YEAR[i].Num_Size);
	  current_num=TOP->ST_YEAR[i].Num_Size;
	  for(j=0;j<current_num;j++)
	  {
		  fprintf(fpoint,"%s %s %d %d ",TOP->ST_YEAR[i].ST_NUM[j].number,TOP->ST_YEAR[i].ST_NUM[j].password,TOP->ST_YEAR[i].ST_NUM[j].Assign_Size,TOP->ST_YEAR[i].ST_NUM[j].CGPA_Size);
		  current_assign=TOP->ST_YEAR[i].ST_NUM[j].Assign_Size;
		  current_cgpa=TOP->ST_YEAR[i].ST_NUM[j].CGPA_Size;
		  for(k=0;k<current_assign;k++)
		  {
			  fprintf(fpoint,"%s %s/ %s %d %d ",TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].name,TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].describe,TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].professor,TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].date[0],TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].date[1]);
		  }
		  for(k=0;k<current_cgpa;k++)
		  {
			  fprintf(fpoint,"%d %.2f ",TOP->ST_YEAR[i].ST_NUM[j].Child_C[k].semester,TOP->ST_YEAR[i].ST_NUM[j].Child_C[k].score);
		  }
		  fprintf(fpoint,"\n");
	  }
  }
  fclose(fpoint);
}
void Create_Struct()
{
  int i,j,k;
  int current_year;
  int current_num;
  int current_assign;
  int current_cgpa;
  char* token;
  char temp[350];
  FILE* fpoint;
  fpoint=fopen("data.txt","rt");
  TOP=(TREE_HEAD*)malloc(sizeof(TREE_HEAD));
  if(fpoint==NULL)
  {
	       printw("There is no file. The program will be ended.\n");
		   getch();
		     return;
  }
  fscanf(fpoint,"%d\n",&(TOP->Year_Size));
  current_year=TOP->Year_Size;
  TOP->ST_YEAR=(YEAR*)malloc(sizeof(YEAR)*current_year);
  
  char junk;
  for(i=0;i<current_year;i++)
  {
		fscanf(fpoint,"%s %d\n",TOP->ST_YEAR[i].year,&TOP->ST_YEAR[i].Num_Size);
		current_num=TOP->ST_YEAR[i].Num_Size;
		TOP->ST_YEAR[i].ST_NUM=(STUDENT*)malloc(sizeof(STUDENT)*current_num);
		for(j=0;j<current_num;j++)
		{
			fscanf(fpoint,"%s %s %d %d",TOP->ST_YEAR[i].ST_NUM[j].number,TOP->ST_YEAR[i].ST_NUM[j].password,&(TOP->ST_YEAR[i].ST_NUM[j].Assign_Size),&(TOP->ST_YEAR[i].ST_NUM[j].CGPA_Size));
			current_assign=TOP->ST_YEAR[i].ST_NUM[j].Assign_Size;
			current_cgpa=TOP->ST_YEAR[i].ST_NUM[j].CGPA_Size;
			TOP->ST_YEAR[i].ST_NUM[j].Child_A=(ASSIGN*)malloc(sizeof(ASSIGN)*current_assign);
			TOP->ST_YEAR[i].ST_NUM[j].Child_C=(CGPA*)malloc(sizeof(CGPA)*current_cgpa);
			for(k=0;k<current_assign;k++)
			{
				fscanf(fpoint,"%s %[^/]%*c %s %d %d ",TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].name,TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].describe,TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].professor,&(TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].date[0]),&(TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].date[1]));
			}
			for(k=0;k<current_cgpa;k++)
			{
				fscanf(fpoint,"%d %f\n",&(TOP->ST_YEAR[i].ST_NUM[j].Child_C[k].semester),&(TOP->ST_YEAR[i].ST_NUM[j].Child_C[k].score));
			}

		}
  }
  fclose(fpoint); 

}
char Account_Manage()
{
  printw("1. Login\n");
  printw("2. Create new Account\n");
  printw("3. Delete Account\n");
  printw("4. Get Temporary Password\n");
  printw("5. Exit\n");
  return wgetch(stdscr);
}
char menu()
{
  printw("1. Assignment Management\n");
  printw("2. CGPA Management\n");
  printw("3. Change Password\n");
  printw("4. Logout\n");
  return wgetch(stdscr);
}
void Search_Assign()
{
  int Asize;
  char input;
  clear();
  printw("<Assignment Management for %s>\n",Curr_Num);
  Asize = TOP->ST_YEAR[Login_Year].ST_NUM[Login_Num].Assign_Size;
  Sort_Assign();
  Print_Assign(Asize);
  printw("1. New Assignment\n2. Delete Assignment\n3. Return to main menu\n");
  noecho();
  input=wgetch(stdscr);
  echo();
  switch(input)
  {
    case '1': Add_Assign(); break;
    case '2': Delete_Assign(); break;
    case '3': return; break;
  }
  clear();
}

void Print_Assign(int Asize)
{
  int k,D_day,thistime,thattime;
  time_t t;
  struct tm *today;
  struct tm *due;
  int i;
  int j;
  int m,d;
  i=Login_Year;
  j=Login_Num;
  t = time(NULL);
  today = localtime(&t);
  thistime = mktime(today);
  for(k=0;k<Asize;k++)
  {
	  printw("<%d> Name         : %s\n",k+1,TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].name);
	  printw("    Describe     : %s\n",TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].describe);
	  printw("    professor    : %s\n",TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].professor);
	  m=TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].date[0];
	  d=TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].date[1];
	  printw("    Due : %d/%d\n",m,d);
	  due=(struct tm*)malloc(sizeof(struct tm));
	  due->tm_year=117;
	  due->tm_mon=m-1;
	  due->tm_mday=d;
	  due->tm_hour=23;
	  due->tm_min=59;
	  due->tm_sec=59;
	  thattime=mktime(due);
	  D_day=(((thattime-thistime)/60)/60)/24;
	  
	  if(thattime-thistime<0)
		  printw("    D-day over!!\n\n");
	  else if(D_day==0)
		  printw("    D-day        : TODAY!\n\n");
	  else{
	  printw("    D-day        : -%d\n\n",D_day);
	  }
	  free(due);
  }
  
}

char cgpa_menu()
{
  printw("1. Add new GPA or Change existing GPA\n");
  printw("2. View all\n");
  printw("3. Exit\n");
  return wgetch(stdscr);
}
void Search_CGPA() 
{
  int exit;
  Curr_year_index=Login_Year;
  Curr_num_index=Login_Num;
  while(!exit)
  {
    clear();
    switch(cgpa_menu())
    {
      case CGPA_ADD: Add_GPA(); break;
      case CGPA_VIEW: Print_CGPA(); break;
      case CGPA_QUIT: exit = 1; break;
	  default: break;
    }
  }
  exit = 0;
}
void Add_GPA()
{
  char semester;
  float gpa;
  int gpa_size;
  clear();
  echo();
  printw("Input the semester of GPA : ");
  scanw("%c", &semester);

  gpa_size = TOP -> ST_YEAR[Curr_year_index].ST_NUM[Curr_num_index].CGPA_Size;  

  if(semester - '0' > (gpa_size + 1) || semester - '0' < 1) {
    printw("You entered wrong number!\n");
    getch();
    return ;
  } 
  printw("Input the GPA : ");
  scanw("%f", &gpa);

  if(gpa < 0 || gpa > 4.31) {
    printw("You entered wrong number!\n");
    getch();
    return ;
  }

  if(semester - '0' <= gpa_size) {
    Cor_GPA(semester, gpa);
    return ;
  }

  TOP -> ST_YEAR[Curr_year_index].ST_NUM[Curr_num_index].CGPA_Size++;
  gpa_size++;

  TOP -> ST_YEAR[Curr_year_index].ST_NUM[Curr_num_index].Child_C = (CGPA*)realloc(TOP -> ST_YEAR[Curr_year_index].ST_NUM[Curr_num_index].Child_C,gpa_size * sizeof(CGPA));

  TOP -> ST_YEAR[Curr_year_index].ST_NUM[Curr_num_index].Child_C[gpa_size - 1].semester = semester - '0';
  TOP -> ST_YEAR[Curr_year_index].ST_NUM[Curr_num_index].Child_C[gpa_size - 1].score = gpa; 
	Save_Data();
  return ;

}
void Cor_GPA(char semester, float gpa) 
{
  int i;
  TOP -> ST_YEAR[Curr_year_index].ST_NUM[Curr_num_index].Child_C[semester - '0' - 1].score = gpa;
  printw("GPA is changed successfully!\n");
  getch();
  return ;

}
void Print_CGPA() //Additional
{
  int i;
  int tmpSemester;
  float tmpGPA;
  float sum = 0;
  clear();
  printw("<CGPA Management for %s>\n", Curr_Num);
  printw("------------------------------\n");
  printw("  Semester  |  GPA  |  CGPA  |  \n");
  for(i = 0 ; i < TOP -> ST_YEAR[Curr_year_index].ST_NUM[Curr_num_index].CGPA_Size ; i++) 
  {
	tmpSemester=TOP->ST_YEAR[Curr_year_index].ST_NUM[Curr_num_index].Child_C[i].semester;
	tmpGPA=TOP->ST_YEAR[Curr_year_index].ST_NUM[Curr_num_index].Child_C[i].score;
	sum+=tmpGPA;
    printw("------------------------------\n");
    printw("     %d      |  %.2f |  %.2f  |\n", tmpSemester, tmpGPA, sum/(i + 1));
  }
  printw("------------------------------\n\n");
  printw("<CGPA Management by Graph for %s>\n", Curr_Num);
  printw("(x-axis : semester,  y-axis : score)\n");
  Print_CGPA_Graph();
  getch();
}
void Print_CGPA_Graph() 
{
 	char map[25][55];//그래포 배열이다.
	int i,j;
	for(i=0;i<25;i++)
		for(j=0;j<55;j++)
			map[i][j]=' ';//공백으로 초기화
	for(i=0;i<25;i++)
		map[i][54]='\n';//마지막 문자에는 \n
	for(i=0;i<9;i++)
		map[0][6*i+5]='|';// x축 | 문자 입력
	for(i=1;i<=8;i++)
		map[0][6*(i-1)+2+6]='0'+('1'-'0')*i;//x축 값 입력
	for(i=0;i<54;i++)
		map[1][i]='-';
	for(i=2;i<25;i++)//y축 형태 입력
		map[i][5]='|';
	for(i=0;i<5;i++)
		map[5*i+2][1]='0'+('1'-'0')*i;
	for(i=0;i<5;i++)
		map[5*i+2][2]='.';
	for(i=0;i<5;i++)
		map[5*i+2][3]='0';
	//여기까지 그래프 기본틀 완성
	int csize=TOP->ST_YEAR[Login_Year].ST_NUM[Login_Num].CGPA_Size;
	for(i=0;i<csize;i++)
	{
		int sem;float score;
		int check;
		sem=TOP->ST_YEAR[Login_Year].ST_NUM[Login_Num].Child_C[i].semester;
		score=TOP->ST_YEAR[Login_Year].ST_NUM[Login_Num].Child_C[i].score;
		for(j=0;j<55;j++)
		{
			if(map[0][j]=='0'+('1'-'0')*sem)
			{
				char one,two,three,four;
				one=((int)(score))*('1'-'0')+'0';//점수를 표시할 문자들이다.
				two='.';
				three=(int)((int)(score*10)%10)*('1'-'0')+'0';
				four=(int)((int)(score*100)%10)*('1'-'0')+'0';
				check=(int)(score*100)/20+1;//check변수는 x축으로부터 몇칸 위로 올라가야하는지 알려준다.
				
				map[1+check][j]='*';
				if(check==1){//만약 점수를 표시하는 문자가 x축을 침범했을 경우에는 문자 위에 점수를 표기하게 한다.
					map[2+check][j-1]=one;
					map[2+check][j]=two;
					map[2+check][j+1]=three;
					map[2+check][j+2]=four;
				}
				else{//그렇지 않을 경우엔 원상태로 표기.
				map[1+check-1][j-1]=one;
				map[1+check-1][j]=two;
				map[1+check-1][j+1]=three;
				map[1+check-1][j+2]=four;
				}
			}
		}
	}
	
	for(i=24;i>=0;i--)
		for(j=0;j<55;j++)
			printw("%c",map[i][j]);
}
void Sort_Assign()
{
  int i,j,tmpm,tmpd;//tmpm : 달, tmpd : 일
  ASSIGN* temp;
  temp=(ASSIGN*)malloc(sizeof(ASSIGN));
  Assign_Count=TOP->ST_YEAR[Login_Year].ST_NUM[Login_Num].Assign_Size;
  for(i=1;i<Assign_Count;i++)
  {
		tmpm=TOP->ST_YEAR[Login_Year].ST_NUM[Login_Num].Child_A[i].date[0];
		tmpd=TOP->ST_YEAR[Login_Year].ST_NUM[Login_Num].Child_A[i].date[1];
		j=i;
		temp[0]=TOP->ST_YEAR[Login_Year].ST_NUM[Login_Num].Child_A[i];
		while((TOP->ST_YEAR[Login_Year].ST_NUM[Login_Num].Child_A[j-1].date[0]>tmpm || (TOP->ST_YEAR[Login_Year].ST_NUM[Login_Num].Child_A[j-1].date[0]==tmpm && TOP->ST_YEAR[Login_Year].ST_NUM[Login_Num].Child_A[j-1].date[1]>tmpd))&&(j>0)){
			TOP->ST_YEAR[Login_Year].ST_NUM[Login_Num].Child_A[j]=TOP->ST_YEAR[Login_Year].ST_NUM[Login_Num].Child_A[j-1];
			j--;
		}
		TOP->ST_YEAR[Login_Year].ST_NUM[Login_Num].Child_A[j]=temp[0];

  }
}
void Add_Assign()
{
  //Login_Num,Login_Year
	ASSIGN* new;
	new=(ASSIGN*)malloc(sizeof(ASSIGN));
	clear();
	printw("Enter the name of new assignment:\n");
	scanw("%s",new->name);
	printw("Enter the description of new assignment:\n");
	scanw("%[^\n]",new->describe);
	printw("Enter the professor of new assignment:\n");
	scanw("%[^\n]",new->professor);
	while(1){printw("Enter the due month of new assignment: ");
	scanw("%d",&new->date[0]);
	if(new->date[0]>0&&new->date[0]<13)
		break;
	else{
		printw("Month is 1~12\n");
		continue;
	}}
	while(1){
	printw("Enter the due day of new assignment: ");
	scanw("%d",&new->date[1]);
	if(new->date[1]>0&&new->date[1]<32)
		break;
	else{
		printw("Day is 1~31\n");
		continue;
	}
	}
	int j=Login_Num;
	int i=Login_Year;
	TOP->ST_YEAR[i].ST_NUM[j].Assign_Size++;
	int asize=TOP->ST_YEAR[i].ST_NUM[j].Assign_Size;
	TOP->ST_YEAR[i].ST_NUM[j].Child_A=(ASSIGN*)realloc(TOP->ST_YEAR[i].ST_NUM[j].Child_A,sizeof(ASSIGN)*(TOP->ST_YEAR[i].ST_NUM[j].Assign_Size));
	TOP->ST_YEAR[i].ST_NUM[j].Child_A[asize-1]=new[0];
	printw("New assignment is successfully added!!\n");
	getch();
	Save_Data();
}
void Delete_Assign()
{
	char delname[100];
	int i=Login_Year;
	int j=Login_Num;
	int k,asize,index;
	while(1){
	clear();
	printw("Type the assign name to delete : ");//삭제할 숙제의 이름을 입력받는다.
	scanw("%s",delname);
	asize=TOP->ST_YEAR[i].ST_NUM[j].Assign_Size;
	int check=0;
	for(k=0;k<asize;k++)
	{
		if(strcmp(TOP->ST_YEAR[i].ST_NUM[j].Child_A[k].name,delname)==0){
			check=1;
			getch();
			index=k;
			break;
		}
	}
	if(check==0){//그 숙제가 존재하지 않을때 오류메세지 출력후 다시 입력받게 한다.
		printw("Invalid assignment name!\nPlease retype the name.\n");
		getch();
		continue;
	}
	else if(check==1)
		break;
	}
	for(k=index;k<asize-1;k++)//삭제하기위해 인덱스를 하나씩 앞으로 당긴다.
		TOP->ST_YEAR[i].ST_NUM[j].Child_A[k]=TOP->ST_YEAR[i].ST_NUM[j].Child_A[k+1];
	asize=TOP->ST_YEAR[i].ST_NUM[j].Assign_Size--;
	TOP->ST_YEAR[i].ST_NUM[j].Child_A=(ASSIGN*)realloc(TOP->ST_YEAR[i].ST_NUM[j].Child_A,sizeof(ASSIGN)*asize);//숙제 사이즈가 줄었기 때문에 메모리를 재할당시켜준다.

	printw("The assignment is completely deleted!!\n");
	getch();
	Save_Data();//데이터 저장. 메뉴에서 다시 데이터 접근이 가능하므로 미리 저장해준다.
  
}
void Add_CGPA()//사용하지않은 함수
{
  //Login_Num,Login_Year
  
  /*
  	To do...
  */  
  
}
void New_Account()
{
	int i;
	char nyear[5];
	char nnum[5];
	char pass[16];
	clear();
	while(1){
	echo();
	printw("Input new year:(2000~2017)");
	scanw("%s",nyear);
	if((nyear[0]=='2'&&nyear[1]=='0')&&(('0'<=nyear[2]&&nyear[2]<='1')&&('0'<=nyear[3]&&nyear[3]<='7'))&&(nyear[4]=='\0'))
			break;
	printw("Not Invalid year\n");//원하는 범위 안에 입력이 아닐경우 오류 메세지 출력한다.
	noecho();
	getch();
	}
	while(1){
	echo();
	printw("Input new num:(0000~1999)");
	scanw("%s",nnum);
	if(('0'<=nnum[0]&&nnum[0]<='1')&&(nnum[4]=='\0')&&('0'<=nnum[1]&&nnum[1]<='9')&&('0'<=nnum[2]&&nnum[2]<='9')&&('0'<=nnum[3]&&nnum[3]<='9'))
		break;
	printw("Not Invalid num\n");
	noecho();
	getch();
	}//설정돼있는 범위내에서만 학번을 입력받는다.
	printw("Success_year and num_\n");
	printw("Please Enter\n");
	getch();
	printw("Input your password(max15):");//비밀번호 또한 입력받는다.
	scanw("%s",pass);
	int yearnum=TOP->Year_Size;
	int stunum;
	int check=0;
	int one,two;
	for(i=0;i<yearnum;i++)//이미 같은 year가 존재할때찾아준다
	{
		if(strcmp(TOP->ST_YEAR[i].year,nyear)==0)
		{
			check=1;
			one=i;
			break;
		}
	}
	if(check==1)//그 year가 이미 데이터에 존재할때이다.
	{
		TOP->ST_YEAR[one].Num_Size++;
		int nsize=TOP->ST_YEAR[one].Num_Size;
		TOP->ST_YEAR[one].ST_NUM=(STUDENT*)realloc(TOP->ST_YEAR[one].ST_NUM,sizeof(STUDENT)*TOP->ST_YEAR[one].Num_Size);
		strcpy(TOP->ST_YEAR[one].ST_NUM[nsize-1].number,nnum);
		TOP->ST_YEAR[one].ST_NUM[nsize-1].Assign_Size=0;
		TOP->ST_YEAR[one].ST_NUM[nsize-1].CGPA_Size=0;
		strcpy(TOP->ST_YEAR[one].ST_NUM[nsize-1].password,pass);
	}
	else//year가 데이터에 없을 경우이다.
	{
		TOP->Year_Size++;
		yearnum=TOP->Year_Size;
		TOP->ST_YEAR=(YEAR*)realloc(TOP->ST_YEAR,sizeof(YEAR)*yearnum);
		TOP->ST_YEAR[yearnum-1].Num_Size=1;
		strcpy(TOP->ST_YEAR[yearnum-1].year,nyear);
		TOP->ST_YEAR[yearnum-1].ST_NUM=(STUDENT*)malloc(sizeof(STUDENT));
		strcpy(TOP->ST_YEAR[yearnum-1].ST_NUM[0].number,nnum);
		strcpy(TOP->ST_YEAR[yearnum-1].ST_NUM[0].password,pass);
		TOP->ST_YEAR[yearnum-1].ST_NUM[0].Assign_Size=0;
		TOP->ST_YEAR[yearnum-1].ST_NUM[0].CGPA_Size=0;
	}
	printw("The Account is completely added.\n");
	getch();
	Save_Data();
}
void Delete_Account()
{
	clear();
	int i;
	while(1){
	printw("Input ID to delete : ");
	scanw("%s",Curr_Num);
	printw("Input Password : ");
	scanw("%s",Curr_Pass);
	int stusize=TOP->ST_YEAR[Login_Year].Num_Size;//로그인 함수로 대조한다
	if(login()==1){
		for(i=Login_Num;i<stusize-1;i++)//인덱스를 하나씩 앞으로 당긴다
		{
			TOP->ST_YEAR[Login_Year].ST_NUM[i]=TOP->ST_YEAR[Login_Year].ST_NUM[i+1];
		}
		TOP->ST_YEAR[Login_Year].Num_Size--;//아이디가 하나 삭제됐으므로 사이즈 줄인다.
		free(TOP->ST_YEAR[Login_Year].ST_NUM[stusize-1].Child_A);
		free(TOP->ST_YEAR[Login_Year].ST_NUM[stusize-1].Child_C);

		TOP->ST_YEAR[Login_Year].ST_NUM=(STUDENT*)realloc(TOP->ST_YEAR[Login_Year].ST_NUM,sizeof(STUDENT)*(stusize-1));

		if(TOP->ST_YEAR[Login_Year].Num_Size==0)//만약 그 학번에 아무도 없을때이다.
		{
			for(i=Login_Year;i<TOP->Year_Size-1;i++)
				TOP->ST_YEAR[i]=TOP->ST_YEAR[i+1];
			TOP->Year_Size--;
			free(TOP->ST_YEAR[TOP->Year_Size-1].ST_NUM);
			TOP->ST_YEAR=(YEAR*)realloc(TOP->ST_YEAR,sizeof(YEAR)*(TOP->Year_Size));
		
		}
		break;
	}
	else{
		printw("The ID or password is not correct.\nPlease retype those.\nPlease Enter.\n");
		getch();
		continue;
	}
	}
	Save_Data();
	printw("The account is completely deleted.\n");
	getch();
}
void Change_Password()
{

	char new[16];
	char new2[16];
	int exit=0;
	while(exit!=1){//반복적으로 새로운 비밀번호를 입력받는다. 같을경우 종료하고 아니면 계속 받게된다. 하지만 사용자가 원할때 끝낼수 있다.
	clear();
	noecho();
	printw("Enter new password:");
	scanw("%s",new);
	
	printw("Confirm new password:");
    scanw("%s",new2);
	if(strcmp(new,new2)==0)
	{
		printw("Password of Account <%s> is successfully changed.\n",Curr_Num);
		printw("Please Enter.\n");
		getch();
	    strcpy(TOP->ST_YEAR[Login_Year].ST_NUM[Login_Num].password,new);
		Save_Data();
		echo();
		return;
	}
	else
	{
		printw("The password is not matched.\n");//비밀번호가 서로 맞지 않을때이다. 만약 끝내고 싶으면 1을 입력, 다시 비밀번호를 변경하고싶으면 아무거나 누른다.
		printw("If you want to exit, input 1. or just Enter.\n"); 
		scanw("%d",&exit);
		continue;
	}
	}
	echo();
}

int login()//로그인 함수
{
  int i,j;
  int year_flag=0;
  int num_flag=0;
  int pass_flag=0;
  char year[5]={};
  char num[5]={};
  for(i=0;i<4;i++)
    year[i]=Curr_Num[i];
  for(i=4;i<8;i++)
    num[i-4]=Curr_Num[i];
  for(i=0;i<TOP->Year_Size;i++)
  {
    if(!strcmp(TOP->ST_YEAR[i].year,year))
    {
      year_flag=1;
      break;
    }
  }
  if(year_flag==1)
  {
    for(j=0;j<TOP->ST_YEAR[i].Num_Size;j++)
    {
      if(!strcmp(TOP->ST_YEAR[i].ST_NUM[j].number,num))
      {
        num_flag=1;
        break;
      }
    }
  }
  if(num_flag==1)
  {
    if(!strcmp(TOP->ST_YEAR[i].ST_NUM[j].password,Curr_Pass))
    {
      pass_flag=1;
      Login_Year=i;//stores logged in user's year
      Login_Num=j;//stores logged in user's number
    }
  }
  if(pass_flag==1)
    return 1;
  return 0;
}

void Temp_Password()//임시 비밀번호 발금 함수
{
  int flag1=0;
  int i, j, k;
  char num[5]={};
  char year[5]={};
  char temppassword[8];
  float temp;
  int s;
  clear();
  echo();
  srand(time(NULL));
  printw("Student Number:");//학생 아이디 입력
  scanw("%s",Curr_Num);
  printw("Input latest semester's GPA:");//그 학생의 마지막 점수 확인
  scanw("%f",&temp);
  for(i=0;i<4;i++)
	  year[i]=Curr_Num[i];
  for(i=0;i<4;i++)
	  num[i]=Curr_Num[i+4];
  int one=-1,two=-1,three=-1;
  for(i=0;i<TOP->Year_Size;i++)
  {
	  if(strcmp(year,TOP->ST_YEAR[i].year)==0)
	  {
		  one=i;
		  break;
	  }
  }
  if(one==-1)//ID가 존재하지 않을때
  {
	  printw("Invalid ID\n");//오류 메세지 출력
	  getch();
	  return;
  }
  for(i=0;i<TOP->ST_YEAR[one].Num_Size;i++)
  {
	  if(strcmp(num,TOP->ST_YEAR[one].ST_NUM[i].number)==0)
	  {
		  two=i;
		  break;
	  }
  }
  if(two==-1)//마찬가지로 학번이 존재하지 않을때
  {
	  printw("Invalid ID\n");
	  getch();
	  return;
  }
  s=TOP->ST_YEAR[one].ST_NUM[two].CGPA_Size;//여가서 one two는 그 학생의 year index와 num index이다.
  if(TOP->ST_YEAR[one].ST_NUM[two].Child_C[s-1].score!=temp)//CGP가 맞지 않을때
  {
	  printw("Invalid ID or GPA\n");
	  printw("Please Input Any key\n");
	  int junk;getch();
	  return;
  }
  for(i=0;i<8;i++)
  {
	  int t=0;
	  while(1)
	  {
		  t=rand()%127;//난수 생성
		  if(t>=33&&t<=126)
			  break;
	  }
	  temppassword[i]=t;
  }//임시비밀번호 생성
  printw("Temporary Password is <%s>\n",temppassword);
  int junk;
  getch();
  strcpy(TOP->ST_YEAR[one].ST_NUM[two].password,temppassword);
  Save_Data();
}
