#include<stdio.h>
#include<stdlib.h>
char** resize(int arg1,int* height,int* width,char**img)//이미지를 2배 확대, 2배 축소
{
	int nheight,nwidth,i,j;
	char**a;char tmp;//return 할 이중배열 선언과 임시 저장할 변수 선언
	if(arg1!=0&&arg1!=1)//옳지 않은 입력일 경우이다.
	{
		printf("Invalid arg!\n");
		return img;
	}
	else if(arg1==0)//2배 확대
	{
		nheight=2*(*height);//새로운 가로 세로 길이
		nwidth=2*(*width);
		if(nheight>4096||nwidth>4096)//지정된 가로세로 길이를 넘을 때 이다.
		{
			printf("Error! The size is too big\n");
			return img;
		}
		a=(char**)malloc(sizeof(char*)*nheight);//동적 할당 해준다.
		for(i=0;i<nheight;i++)
			*(a+i)=(char*)malloc(sizeof(char)*nwidth);
		
		for(i=0;i<*height;i++)//여기서 두배로 확대 시켜주는 역할을 한다.
		{
			for(j=0;j<*width;j++)
			{
				tmp=*(*(img+i)+j);
				*(*(a+2*i)+2*j)=tmp;
				*(*(a+2*i+1)+2*j)=tmp;
				*(*(a+2*i)+2*j+1)=tmp;
				*(*(a+2*i+1)+2*j+1)=tmp;
			}
		}
		*height=nheight;//변화된 가로 세로 길이를 저장해준다.
		*width=nwidth;
		return a;
	}
	else if(arg1==1)//1일때 축소이다.
	{	
		nheight=(*height)/2;
		nwidth=(*width)/2;
		a=(char**)malloc(sizeof(char*)*nheight);//동적 배열해준다.
		for(i=0;i<nheight;i++)
			*(a+i)=(char*)malloc(sizeof(char)*nwidth);
		if(nheight<1||nwidth<1)//사이즈가 너무 작을 때 에러를 출력해준다.
		{
			printf("Error! The size is too small!\n");
			return img;
		}
		for(i=0;i<nheight;i++)//여기서 축소 기능을 해준다.
			for(j=0;j<nwidth;j++)
			{
				tmp=(*(*(img+2*i)+2*j)+*(*(img+2*i)+2*j+1)+*(*(img+2*i+1)+2*j)+*(*(img+2*i+1)+2*j+1))/4;
				*(*(a+i)+j)=tmp;
			}
		*height=nheight;//변화된 가로 세로 길이를 다시 저장해준다.
		*width=nwidth;
		return a;
	}

}
char** rotate(int height,int width,int angle,char** img)//이미지 회전, 0,1,2(90,180,270도) 이미지 회전
{	
	char** a;
	int i,j;
	if(angle!=0&&angle!=1&&angle!=2)//옳지 않은 입력일 경우 에러를 출력해준다.
	{
		printf("Error! Invalid angle!\n");
		return img;
	}
	else if(angle==0)//90도 회전
	{
		a=(char**)malloc(sizeof(char*)*width);//동적 할당해준다.
		for(i=0;i<width;i++)
			*(a+i)=(char*)malloc(sizeof(char)*height);
		for(i=0;i<width;i++)//새로 선언한 배열에 90도 회전된 img배열을 저장해준다.
			for(j=0;j<height;j++)
				*(*(a+i)+j)=*(*(img+height-1-j)+i);
		img=(char**)realloc(img,sizeof(char*)*width);//img배열을 재할당시켜준다. 변화된 사이즈만큼 해준다.
		for(i=0;i<width;i++)
			*(img+i)=(char*)realloc(*(img+i),sizeof(char)*height);
		img=a;//재할당된 img배열에 아까 저장놨던 변화된 배열을 다시 가리켜준다.
		return img;
	}
	else if(angle==1)//180도 회전
	{
		a=(char**)malloc(sizeof(char*)*height);
		for(i=0;i<height;i++)
			*(a+i)=(char*)malloc(sizeof(char)*width);
		for(i=0;i<height;i++)//90도와 마찬가지로 새로 선언된 배열에 회전된 배열을 저장해준다.
			for(j=0;j<width;j++)
				*(*(a+i)+j)=*(*(img+height-1-i)+width-1-j);
		img=(char**)realloc(img,sizeof(char*)*height);//재할당해준다.
		for(i=0;i<height;i++)
			*(img+i)=(char*)realloc(*(img+i),sizeof(char)*width);
		img=a;//다시 넣어준다.
		return img;
	}
	else if(angle==2)//270도 회전
	{
		a=(char**)malloc(sizeof(char*)*width);
		for(i=0;i<width;i++)
			*(a+i)=(char*)malloc(sizeof(char)*height);
		for(i=0;i<width;i++)//90도회전과 정반대 기능을 해준다.
			for(j=0;j<height;j++)
				*(*(a+i)+j)=*(*(img+j)+width-1-i);
		img=(char**)realloc(img,sizeof(char*)*width);//나머지 할당과 저장은 위와 같다.
		for(i=0;i<width;i++)
			*(img+i)=(char*)realloc(*(img+i),sizeof(char)*height);
		img=a;
		return img;
	}
}
void flip(int height,int width, int flag, char** img)//이미지 반전0,1 (수평, 수직) 이미지 반전
{
	int i,j;
	char junk;
	if(flag!=0&&flag!=1)//옳지 않은 입력일 경우 에러 메세지를 출력한후 함수를 종료한다.
	{
		printf("Invalid flag!\n");
		return;
	}
	else if(flag==0)//수평(위아래) 반전
	{
		for(i=0;i<height/2;i++)//junk를 이용해 이미지 배열을 위아래로 반전시켜준다.
			for(j=0;j<width;j++)
			{
				junk=*(*(img+height-1-i)+j);
				*(*(img+height-1-i)+j)=*(*(img+i)+j);
				*(*(img+i)+j)=junk;
			}
	}
	else if(flag==1)//수직(옆으로) 반전
	{	
		for(i=0;i<height;i++)//마찬가지로 이번엔 양옆으로 반전시켜준다.
			for(j=0;j<width/2;j++)
			{
				junk=*(*(img+i)+width-1-j);
				*(*(img+i)+width-1-j)=*(*(img+i)+j);
				*(*(img+i)+j)=junk;
			}
	}
}
char* copy(int x1,int y1,int c_h,int c_w,int height,int width,char** img)//이미지 배열에서 원하는 사이즈 크기만큼 복사해 그 복사한 배열을 리턴해준다. 1차배열이다.
{	
	char* c;
	c=(char*)malloc(sizeof(char)*(c_h*c_w+c_h+1));//리턴할 배열 동적 할당
	int i,j,k=0;
	for(i=y1;i<y1+c_h;i++)
		for(j=x1;j<x1+c_w;j++)
		{
			
			*(c+k)=*(*(img+i)+j);
			k++;
			if(j==x1+c_w-1)
			{
				*(c+k)='\t';//여기서 \t을 넣어주는 이유는 1차 배열에 그림을 저장하기 위해서는 행이 바뀔 때마다 그 가로 세로 길이를 저장해주기 위해서이다. 즉 t를 이용해 행이 바뀜을 알려줄수 있다.
				k++;
			}
		}
	*(c+k)='\0';//마지막엔 널값을 넣어준다. 문자열의 끝을 알려주기 위함이다.
	return c;
}	

void paste(int x2,int y2,int height,int width,char** img,char* temp)//리턴받은 1차 배열을 이용해 이미지 배열에 붙여주기 기능을 하는 함수이다.
{
	int i,j,k=0;
	int c_h,c_w,barnum=0,total=0;
	for(i=0;;i++){
		if(*(temp+i)=='\t'){//copy 함수에서 넣어줬던 \t를 이용해 1차배열에서 복사된 가로 세로 길이를 구한다.
			barnum++;//\t의 개수이다.
		}
		else if(*(temp+i)=='\0')
		{
			total=i;//1차배열의 길이이다.
			break;
		}
	}
	c_h=barnum;//복사된 그림의 세로 길이이다.
	c_w=(total-barnum)/c_h;//복사된 그림의 가로 길이이다.
	for(i=y2;i<y2+c_h;i++){
		if(i>=height){
			k++;
			continue;
		}
		for(j=x2;j<x2+c_w;j++)
		{
			if(*(temp+k)=='\t')//행이 바뀔경우이다.
				k++;
			if(j>=width)//붙여줄 때 이미지배열 밖으로 범위가 넘어갈경우에는 무시해준다.
			{
				k++;
				continue;
			}
			*(*(img+i)+j)=*(temp+k);//여기서 붙여주기 기능을 해준다.
			k++;
		}
	}

}
void fill(int y,int x,int* num,char** img,char acolor,char bcolor,int height,int width)//같은 문자로 인접해있는 영역을 원하는 문자로 채워주는 함수이다.
{
	if(x==-1||y==-1||y==height||x==width)//재귀함수를 이용했기 때문에 만약 이미지 배열의 범위를 넘을 경우 함수를 종료해준다.
		return;
	if(*(*(img+y)+x)!=acolor)//같은 문자가 아닐경우 종료한다.
		return;
	int i,j,num1=0,num2=0,num3=0,num4=0;//몇개가 바뀌었는지 보여주기위해 개수 변수 4개를 선언하였다.
	*(*(img+y)+x)=bcolor;//일단 파라미터로 받은 위치에 원하는 문자를 넣어준다.
	(*num)++;//넣어줬기 때문에 변한 문자수도 하나 증가한다.
		fill(y-1,x,&num1,img,acolor,bcolor,height,width);//바로 위에 인접해있는 배열값을 다시 재귀함수로 돌린다.
		fill(y+1,x,&num2,img,acolor,bcolor,height,width);//바로 아래에 인접해이는 배열값을 재귀함수로 돌린다.
		fill(y,x-1,&num3,img,acolor,bcolor,height,width);//바로 왼쪽에 인접해있는 배열값을 재귀함수로 돌린다.
		fill(y,x+1,&num4,img,acolor,bcolor,height,width);//바로 오른쪽에 인접해있는 배열값을 재귀함수로 돌린다.
	*num+=num1+num2+num3+num4;//위 4개의 재귀함수에서 넣어준 4개의 변수, 즉 변한 개수를 다 더해준다.
}
int main()//메인 함수이다.
{
	int num,i,j,k;
	char**a;//처음에 입력받을 이미지 배열이다.
	char* junk;
	junk=(char*)malloc(sizeof(char)*4096);
	printf("Input testcase : ");//테스트 케이스를 입력받는다.
	scanf("%d",&num);
	for(k=0;k<num;k++)
	{
		int height,width,query,error=0,qnum;
		printf("Input height , width : ");//가로 세로 길이를 입력받는다.
		scanf("%d %d",&height,&width);
		a=(char**)malloc(sizeof(char*)*height);//동적 할당해준다.
		for(i=0;i<height;i++)
			*(a+i)=(char*)malloc(sizeof(char)*width);
		printf("Input the image :\n");//이미지 입력
		error=0;
		for(i=0;i<height;i++)//height만큼 각 스트링을 입력 받은 후 길이를 잰다
		{
			scanf("%s",junk);
			for(j=0;;j++)
				if(*(junk+j)=='\0')
					break;
			if(j!=width)//width보다 길이가 길경우 error를 표시한다.
			{
				error=1;
				continue;
			}
			else
			{
				for(j=0;j<width;j++)
					*(*(a+i)+j)=*(junk+j);
			}
		

		}
		if(error==1)//입력받은 이미지가 크기를 초과할 경우 에러메세지 출력
		{
			printf("The size is not available!\n");
			continue;
		}
		printf("Input number of query : ");
		scanf("%d",&qnum);
		for(int h=0;h<qnum;h++)
		{
			printf("Input query : ");
			scanf("%d",&query);
			if(query!=1&&query!=2&&query!=3&&query!=4&&query!=5)
			{
				printf("Invalid query num!\n");
				for(i=0;i<height;i++){
					for(j=0;j<width;j++)
						printf("%c",*(*(a+i)+j));
					printf("\n");
				}
				continue;
			}
			if(query==1)//이미지 확대 축소
			{
				int arg;
				printf("\nResize\nInput 0 or 1 : ");//확대,축소 할지 입력
				scanf("%d",&arg);
				a=resize(arg,&height,&width,a);
				printf("Result, resize height : %d, width : %d :\nResult Image\n\n",height,width);	
				for(i=0;i<height;i++)//확대, 축소된 이미지 배열 출력
				{
					for(j=0;j<width;j++)
						printf("%c",*(*(a+i)+j));
					printf("\n");
				}
			}
			else if(query==2)//이미지 회전
			{
				int angle,tmp;
				printf("Input 0 or 1 or 2 : ");//몇도 회전할지 입력
				scanf("%d",&angle);
				a=rotate(height,width,angle,a);
				if(angle==0||angle==2)//90도나 270도 회전일 경우 가로 세로길이는 서로 바꿔주면 된다.
				{
					tmp=height;
					height=width;
					width=tmp;
				}
				printf("Result_rotate height : %d, width : %d\nResult Image\n\n",height,width);//회전된 이미지 배열을 출력해준다.
				for(i=0;i<height;i++){
					for(j=0;j<width;j++)
						printf("%c",*(*(a+i)+j));
					printf("\n");
				}
			}
			else if(query==3)//ㅇ미지 반전
			{
				int flag;
				printf("\nFlip\nInput 0 or 1 : ");//어느쪽으로 반전시킬지 입력받는다.
				scanf("%d",&flag);
				flip(height,width,flag,a);
				printf("Result Image\n\n");//반전된 이미지 출력
				for(i=0;i<height;i++){
					for(j=0;j<width;j++)
						printf("%c",*(*(a+i)+j));
					printf("\n");
				}
			}
			else if(query==4)//이미지 복사, 붙여넣기
			{
				int x1,y1,ch,cw,x2,y2;
				char* temp;
				printf("Copy and Paste\nx1, y1, c_h, c_w, x2, y2 : ");//복사할 위치, 가로세로 길이, 붙여넣기 할 위치를 입력받는다.
				scanf("%d %d %d %d %d %d",&x1,&y1,&ch,&cw,&x2,&y2);
				if((ch<1 || cw<1) || (x1>=width||y1>=height)||(x2>=width||y2>=height)||(x1<0||y1<0)||(x2<0||y2<0))//입력이 올바르지 않을경우 에러를 출력해준다.
				{
			
					printf("Error! Invalid Input\n");
					for(i=0;i<height;i++)//에러를 출력해주고 원래의 이미지를 출력해준다.
					{
						for(j=0;j<width;j++)
							printf("%c",*(*(a+i)+j));
						printf("\n");
					}
					continue;
				}
				if(x1+cw>width)//복사할 그림이 이미지 배열을 넘어갈 경우 넘어가는 영역은 무시하기 위함이다.
					cw=width-x1;
				if(y1+ch>height)
					ch=height-y1;

				temp=copy(x1,y1,ch,cw,height,width,a);//temp배열은 복사된 그림이다.
				paste(x2,y2,height,width,a,temp);//붙여넣기 함수이다.
				printf("Result Image\n\n");//복사, 붙여넣기 된 이미지 배열을 출력해준다.
				for(i=0;i<height;i++)
				{
					for(j=0;j<width;j++)
						printf("%c",*(*(a+i)+j));
					printf("\n");
				}
				free(temp);//복사한 배열을 메모리 해제시켜준다.
			}
			else if(query==5)//fill 이미지 수행
			{
				int x,y,num=0;
				char acolor,bcolor;
				printf("\nFill\nInput y, x, color : ");
				scanf("%d %d %c",&y,&x,&bcolor);
				if((y<0||y>=height)||(x<0||x>=width))//옳지않은 입력일 경우 에러메세지를 출력해준다.
				{
					printf("Invalid input!\n\n");
					for(i=0;i<height;i++)
					{
						for(j=0;j<width;j++)
							printf("%c",*(*(a+i)+j));
						printf("\n");
					}
					continue;
				}
				acolor=*(*(a+y)+x);//acolor는 바꾸고자하는 문자이다.
				if(acolor==bcolor)//원래 같은 문자일 경우 바꾸지 않는다.
				{
					printf("Same Color. Image is not changed\n");
					printf("Number of colored pixels = 0\n\n");
					for(i=0;i<height;i++)
					{
						for(j=0;j<width;j++)
							printf("%c",*(*(a+i)+j));
						printf("\n");
					}
					continue;
				}
				fill(y,x,&num,a,acolor,bcolor,height,width);//함수 실행
				printf("Number of colored pixels = %d\n",num);//몇번 바뀌었는지 개수를 출력해준다.
				for(i=0;i<height;i++)
				{
					for(j=0;j<width;j++)
						printf("%c",*(*(a+i)+j));
					printf("\n");
				}
			}
		

		}
		for(i=0;i<height;i++)//이미지 배열을 메모리 해제시켜준다.
			free(*(a+i));
		free(a);
	}
	free(junk);//메모리 해제.

}
