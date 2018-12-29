#include<stdio.h>
int autosolve(int arr[9][9],int i,int j);
void printsudoku(int arr[9][9]);
int main()
{
    int arr[9][9];
    int i,j;
    //문제입력
    for(i=0;i<9;i++){
	printf("Input %d row integers : ",i+1);
	for(j=0;j<9;j++)
	    scanf("%d",&arr[i][j]);
    }
    printf("\n");
    //자동으로 문제를 풀어준다.
    autosolve(arr,0,0);
    //푼 스도쿠를 출력해준다.
    printsudoku(arr);
    return 0;
}
int autosolve(int arr[9][9],int x,int y)
{
    int i,j;
    int check=0;//반복문을 빠져올 때 쓰는 변수
    while(arr[x][y] > 0)//값이 0인 배열로 차례대로 찾아가게 된다.
	if (++x >= 9)//넘어가면
	{
	    x = 0;
	    if (++y >= 9)//행, 렬 둘다 넘어가면 모든 배열을 검사했다는 뜻이므로
		return 0;
	}

    while(1)//무한 반복으로 시작
    {
	if (++arr[x][y] > 9)//배열값이 0일때 1부터 시작해서 스도쿠 규칙에 따라 넣을 수 있는지 확인하는 과정의 첫단계이다.
	{//만일 값이 9를 넘어갈 경우 다시 0으로 초기화, 이말은 넣을 값이 없으므로 0으로 초기화해주고 리턴값을 -1로 해 역트래킹을 하게 한다.
	    arr[x][y]=0;
	    return -1;
	}

	for (i = 0; i < 9; i++)
	    if (i != x && arr[i][y] == arr[x][y])//세로축에 같은 숫자가 있나 검사한다.
	    {
		check=1;//있으면 check를 1로 하고 continue를 해 다시 검사하게한다.
		break;
	    }
	if(check==1)
	{
	    check=0;
	    continue;
	}

	for (j = 0; j < 9; j++)//마찬가지로 가로축에도 검사를 실시한다.
	    if (j != y && arr[x][j] == arr[x][y])
	    {
		check=1;
		break;
	    }
	if(check==1)
	{
	    check=0;
	    continue;
	}

	for (i = (x / 3) * 3; i < (x / 3) * 3 + 3; i++){//마찬가지로 그 배열이 포함되있는 정사각형 내부에서도 검사를 실시한다.
	    for (j = (y / 3) * 3; j < (y / 3) * 3 + 3; j++)
		if ((i != x || j != y) && arr[i][j] == arr[x][y])
		{
		    check=1;
		    break;
		}
	    if(check==1)
		break;
	}
	if(check==1)
	{
	    check=0;
	    continue;
	}
	if(autosolve(arr,x,y)!=-1)//recursive를 이용해 역추적이 될경우 반복문을 빠져나간다. 그리고 다시 검사하게 한다.
	    break;
    }
    return 0;
}
void printsudoku(int arr[9][9])//스도쿠를 출력해주는 함수이다.
{
    int i,j;
    printf("┏━━┳━━┳━━┳━━┳━━┳━━┳━━┳━━┳━━┓\n");
    for(i=0;i<9;i++)
    {
	printf("┃");
	for(j=0;j<9;j++)
	    printf(" %d┃",arr[i][j]);
	printf("\n");
	if(i==8)
	    break;
	printf("┣━━╋━━╋━━╋━━╋━━╋━━╋━━╋━━╋━━┫\n");
    }
    printf("┗━━┻━━┻━━┻━━┻━━┻━━┻━━┻━━┻━━┛\n");
}
