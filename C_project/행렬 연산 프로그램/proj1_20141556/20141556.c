#include<stdio.h>
#include<stdlib.h>
double detA(double** A,int n);
double** addMatrix(double**A,double**B,int n)//두행렬을 더해주는 함수
{
	double** result;
	int i,j;
	result=(double**)calloc(n,sizeof(double*));
	for(i=0;i<n;i++)
	{
		*(result+i)=(double*)calloc(n,sizeof(double));
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			*(*(result+i)+j)=*(*(A+i)+j)+*(*(B+i)+j);
		}
	}
	
	
	return result;
	

}
double** subMatrix(double**A,double**B,int n)//두행렬을 빼주는 함수
{
	double** result;
	int i,j;
	result=(double**)calloc(n,sizeof(double*));
	for(i=0;i<n;i++)
	{
		*(result+i)=(double*)calloc(n,sizeof(double));
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			*(*(result+i)+j)=*(*(A+i)+j)-*(*(B+i)+j);
		}
	}
	
      

	return result;
	

}
double** MulMatrix(double**A,double**B,int n)//두 행렬을 곱해주는 함수
{
	double** result={0};
	int i,j,k;
	result=(double**)calloc(n,sizeof(double*));
	for(i=0;i<n;i++)
	{
		*(result+i)=(double*)calloc(n,sizeof(double));
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			
			for(k=0;k<n;k++)
			{

			*(*(result+i)+j)=*(*(result+i)+j)+*(*(A+i)+k)*(*(*(B+k)+j));
			}
		}
	}

     

	return result;
	
}
int minus(int n)//-1의 n+1승 (별로 쓰이지는 않았다.)
{
	int j;
	int m=-1;
	
		for(j=0;j<n;j++)
		{
			m=m*(-1);
		}
	
	
	return m;
}
double** sub(double **A,int j,int n)//행렬에서 1행과 j열을 제외한 행렬을 리턴해주는 함수, n이 현재 함수 행,열의 크기
{
	double** result;
	int i,k;
	result=(double**)calloc(n-1,sizeof(double*));
	for(i=0;i<n-1;i++)
	{
		*(result+i)=(double*)calloc(n-1,sizeof(double));
	}
	for(i=0;i<n-1;i++)
	{
		for(k=0;k<j-1;k++)//k가 j-1일 때를 제외하고 넣어준다.
		{
			*(*(result+i)+k)=*(*(A+i+1)+k);
		}
		for(k=j;k<n;k++)
		{
			*(*(result+i)+k-1)=*(*(A+i+1)+k);
		}
	}
	
   

	return result;
}
double detA44(double**A)//n=4일 때 determinant 프로젝트에서 하라는 대로.
{
	int det=0;
	int i=0,j;
	for(j=0;j<4;j++)
	{
		if(j%2!=0)
			det += (-1)**(*(A+i)+j)*detA(sub(A,j,4),3);
		else
			det += *(*(A+i)+j)*detA(sub(A,j,4),3);
	}
	return det;
}
double detA(double** A,int n)//행렬의 determinant값을 리턴해주는 함수 n=5일 때는 미처 구하지 못했다.
{
	double result=0;

	
	if(n==2)
	{
		result=*(*(A+0)+0)**(*(A+1)+1)-*(*(A+1)+0)**(*(A+0)+1);
		return result;
	}
	else if(n==3)
	{
		result=minus(1)**(*(A+0)+0)*(*(*(A+1)+1)**(*(A+2)+2)-*(*(A+1)+2)**(*(A+2)+1))+minus(2)**(*(A+0)+1)*(*(*(A+1)+0)**(*(A+2)+2)-*(*(A+2)+0)**(*(A+1)+2))+minus(3)**(*(A+0)+2)*(*(*(A+1)+0)**(*(A+2)+1)-*(*(A+2)+0)**(*(A+1)+1));
		return result;
	}
	else if(n==4)
	{
		return result=detA44(A);
	}
	
}

double** transposeA(double** A, int n)	//행렬의 행과 열을 바꾸어 주는 함수,arr에 행과 열을 바꿔서 입력해준다.
{
	int i,j;
	double** arr;
	arr=(double**)calloc(n,sizeof(double*));
	for(i=0;i<n;i++)
		*(arr+i)=(double*)calloc(n,sizeof(double));
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			*(*(arr+i)+j)=*(*(A+j)+i);
		}
	}
	
      

	return arr;
}

double** inverse55(double **A)//5*5행렬의 역함수를 리턴해주는 함수
{
	int i,j;
	double det=0;
	double** cofactor;
	double** inverse = (double**)calloc(5,sizeof(double*));
	for(i=0;i<5;i++)
		*(inverse+i) =(double*)calloc(5,sizeof(double));
	
	cofactor= (double**)calloc(5,sizeof(double*));
	for(i=0;i<5;i++)
		*(cofactor+i) = (double*)calloc(5,sizeof(double));
	for(i=0;i<5;i++)			// 5x5의 cofactor를 계산한다.
	{
		for(j=0;j<5;j++)
		{
			if((i+j)%2!=0)
				*(*(cofactor+i)+j) = (-1)*detA44(sub(A,j,5));
			else
				*(*(cofactor+i)+j) = detA44(sub(A,j,5));
		}
	}
	cofactor = transposeA(cofactor,5);		//cofactor의 transpose를 다시 cofactor에 넣어준다.
	i=0;
	for(j=0;j<5;j++)
	{
		if(j%2!=0)
			det += (-1)**(*(A+i)+j)*detA44(sub(A,j,5));	// 5x5의 det를 구한다.
		else
			det += *(*(A+i)+j)*detA44(sub(A,j,5));
	}
	if(det==0)					// det = 0 인경우 null을 입력해준다.
		return NULL;
	else
	{
		for(i=0;i<5;i++)
		{
			for(j=0;j<5;j++)
			{
				*(*(inverse+i)+j) = (1/det)**(*(cofactor+i)+j);  // inverse에 cofactor의 transpose와 det의 값으로 나누어 준값이 역행렬이 된다.
			}
		}

	}
	return inverse;

}
double **inverseA(double**A,int n)//n*n행렬의 역함수를 리턴해주는 함수
{
	double det;
	double** result={0};
	double a,b,c,d,e,f,g,h,i;//간단히 계산하기 위해 변수 설정
	int k;
	double** a1;//프로젝트 매뉴엘 대로 순서대로 A,B,C,D 를 설정함
	double** a2;
	double** a3;
	double** a4;
	double** cab;
	double** cab2;
	double** cab3;

	cab=(double**)calloc(2,sizeof(double*));
	for(k=0;k<2;k++)
	{
		*(cab+k)=(double*)calloc(2,sizeof(double));
	}
	cab2=(double**)calloc(2,sizeof(double*));
	for(k=0;k<2;k++)
	{
		*(cab2+k)=(double*)calloc(2,sizeof(double));
	}
	cab3=(double**)calloc(2,sizeof(double*));
	for(k=0;k<2;k++)
	{
		*(cab3+k)=(double*)calloc(2,sizeof(double));
	}
	
	result=(double**)calloc(n,sizeof(double*));
	for(k=0;k<n;k++)
	{
		*(result+k)=(double*)calloc(n,sizeof(double));
	}
	a1=(double**)calloc(2,sizeof(double*));
	for(k=0;k<2;k++)
	{
		*(a1+k)=(double*)calloc(2,sizeof(double));
	}
	a2=(double**)calloc(2,sizeof(double*));
	for(k=0;k<2;k++)
	{
		*(a2+k)=(double*)calloc(2,sizeof(double));
	}
	a3=(double**)calloc(2,sizeof(double*));
	for(k=0;k<2;k++)
	{
		*(a3+k)=(double*)calloc(2,sizeof(double));
	}
	a4=(double**)calloc(2,sizeof(double*));
	for(k=0;k<2;k++)
	{
		*(a4+k)=(double*)calloc(2,sizeof(double));
	}
	
	if(n==2)//n=2일 때 
	{
		*(*(result+0)+0)=*(*(A+1)+1)/detA(A,n);
		*(*(result+1)+1)=*(*(A+0)+0)/detA(A,n);
		*(*(result+0)+1)=-*(*(A+0)+1)/detA(A,n);
		*(*(result+1)+0)=-*(*(A+1)+0)/detA(A,n);
		return result;
	}
	
	else if(n==3)//n=3 일 때
	{
		a=*(*(A+0)+0);
		b=*(*(A+0)+1);
		c=*(*(A+0)+2);
		d=*(*(A+1)+0);
		e=*(*(A+1)+1);
		f=*(*(A+1)+2);
		g=*(*(A+2)+0);
		h=*(*(A+2)+1);
		i=*(*(A+2)+2);
		det=detA(A,n);
		*(*(result+0)+0)=(e*i-f*h)/det;
		*(*(result+0)+1)=-(b*i-c*h)/det;
		*(*(result+0)+2)=(b*f-c*e)/det;
		*(*(result+1)+0)=-(d*i-f*g)/det;
		*(*(result+1)+1)=(a*i-c*g)/det;
		*(*(result+1)+2)=-(a*f-c*d)/det;
		*(*(result+2)+0)=(d*h-e*g)/det;
		*(*(result+2)+1)=-(a*h-b*g)/det;
		*(*(result+2)+2)=(a*e-b*d)/det;
		return result;
	}
	else if(n==4)//n=4 일때
	{
		
		
		*(*(a1+0)+0)=*(*(A+0)+0);
		*(*(a1+0)+1)=*(*(A+0)+1);
		*(*(a2+0)+0)=*(*(A+0)+2);
		*(*(a2+0)+1)=*(*(A+0)+3);
		*(*(a1+1)+0)=*(*(A+1)+0);
		*(*(a1+1)+1)=*(*(A+1)+1);
		*(*(a2+1)+0)=*(*(A+1)+2);
		*(*(a2+1)+1)=*(*(A+1)+3);
		*(*(a3+0)+0)=*(*(A+2)+0);
		*(*(a3+0)+1)=*(*(A+2)+1);
		*(*(a4+0)+0)=*(*(A+2)+2);
		*(*(a4+0)+1)=*(*(A+2)+3);
		*(*(a3+1)+0)=*(*(A+3)+0);
		*(*(a3+1)+1)=*(*(A+3)+1);
		*(*(a4+1)+0)=*(*(A+3)+2);
		*(*(a4+1)+1)=*(*(A+3)+3);
		cab2=inverseA(a1,n/2);
		cab=MulMatrix(a3,cab2,n/2);
		cab=MulMatrix(cab,a2,n/2);
		cab=subMatrix(a4,cab,n/2);
		cab=inverseA(cab,n/2);
		*(*(result+2)+2)=*(*(cab+0)+0);
		*(*(result+2)+3)=*(*(cab+0)+1);
		*(*(result+3)+2)=*(*(cab+1)+0);
		*(*(result+3)+3)=*(*(cab+1)+1);
		cab2=MulMatrix(cab,a3,n/2);
		cab3=inverseA(a1,n/2);
		cab2=MulMatrix(cab2,cab3,n/2);
		*(*(result+2)+0)=-*(*(cab2+0)+0);
		*(*(result+2)+1)=-*(*(cab2+0)+1);
		*(*(result+3)+0)=-*(*(cab2+1)+0);
		*(*(result+3)+1)=-*(*(cab2+1)+1);
		cab=MulMatrix(a2,cab,n/2);
		cab3=inverseA(a1,n/2);
		cab=MulMatrix(cab3,cab,n/2);
		*(*(result+0)+2)=-*(*(cab+0)+0);
		*(*(result+0)+3)=-*(*(cab+0)+1);
		*(*(result+1)+2)=-*(*(cab+1)+0);
		*(*(result+1)+3)=-*(*(cab+1)+1);
		cab=MulMatrix(cab,a3,n/2);
		cab=MulMatrix(cab,cab3,n/2);
		cab=addMatrix(cab3,cab,n/2);
		*(*(result+0)+0)=*(*(cab+0)+0);
		*(*(result+0)+1)=*(*(cab+0)+1);
		*(*(result+1)+0)=*(*(cab+1)+0);
		*(*(result+1)+1)=*(*(cab+1)+1);
		


		return result;
	}
	else if(n==5)//n=5일 때
	{
		return result=inverse55(A);
	}
	
}


double** inverseA_gaussian(double**A,int n)//Gaussian Elimination방법으로 행렬의 역함수를 리턴해주는 함수
{
	int i,j,k,l;
	double** tmp=(double**)calloc(n,sizeof(double*));
	for(i=0;i<n;i++)
		*(tmp+i)=(double*)calloc(2*n,sizeof(double*));
	double** res=(double**)calloc(n,sizeof(double*));
	for(i=0;i<n;i++)
		*(res+i)=(double*)calloc(n,sizeof(double*));
	int lead=0;
	double swap;
	for(i=0;i<n;i++)			//[A|I]를 만든다
	{
		for(j=0;j<n;j++)
		{
			*(*(tmp+i)+j)=*(*(A+i)+j);
			if(j==i)
				*(*(tmp+i)+j+n)=1;
		}
	}
	
	for(i=0;i<n;i++)			//기본행 연산을 한다.
	{
		
		for(j=lead;j<n;j++)
		{
			if(*(*(tmp+i)+j)!=0)
			{
				lead=j;
				for(k=2*n-1;k>=j;k--)
				{
					if(*(*(tmp+i)+k)!=0)
					{
						*(*(tmp+i)+k)=*(*(tmp+i)+k)/(*(*(tmp+i)+j));
					}
				}
				break;
			}
			else{
				for(k=i;k<n;k++)
				{
					if(*(*(tmp+k)+lead)!=0)
					{
						for(l=0;l<2*n;l++)
						{
							swap=*(*(tmp+i)+l);
							*(*(tmp+i)+l)=*(*(tmp+k)+l);
							*(*(tmp+k)+l)=swap;
						}
					}
				}
				break;
			}
		}
		for(j=0;j<n;j++)
		{
			if(i!=j)
			{
				if(*(*(tmp+j)+lead)!=0)
				{
					for(k=2*n-1;k>=0;k--)
					{
						*(*(tmp+j)+k)=*(*(tmp+j)+k)-*(*(tmp+i)+k)**(*(tmp+j)+lead);
					}
				}
				
			}
		
		}
		lead++;
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(i==j)
			{
				if(*(*(tmp+i)+j)!=1)
					return NULL;
			}
			else
			{
				if(*(*(tmp+i)+j)!=0)
					return NULL;
			}
		}
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			*(*(res+i)+j)=*(*(tmp+i)+j+n);
		}
	}
	


	return res;
}
double** matrix_LU(double** A,double** U,double** L,int n)//행렬의 matrix triangularization의 결과를 리턴해주는 함수
{
	int i,j,k,l,lead=0;
	double swap;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			*(*(U+i)+j)=*(*(A+i)+j);
			if(i==j)
				*(*(L+i)+j)=1;
		}
	}
	for(i=0;i<n;i++)
	{

		for(j=lead;j<n;j++)
		{
			if(*(*(U+i)+j)!=0)
			{
				lead=j;
				break;
			}
			else{
				for(k=i;k<n;k++)
				{
					if(*(*(U+k)+lead)!=0)
					{
						for(l=0;l<2*n;l++)
						{
							swap=*(*(U+i)+l);
							*(*(U+i)+l)=*(*(U+k)+l);
							*(*(U+k)+l)=swap;
						}
					}
				}
				break;
			}
		}
		for(j=0;j<n;j++)
		{
			if(i<j)
			{
				if(*(*(U+j)+lead)!=0)
				{
					for(k=n-1;k>=0;k--)
					{
					//		printf("%.2lf - %.2lf*%.2lf/%.2lf = ",*(*(U+j)+k),*(*(U+i)+k),*(*(U+j)+lead),*(*(U+i)+lead));
							if(*(*(U+j)+lead)!=0)	
								*(*(L+j)+lead)=*(*(U+j)+lead)/(*(*(U+i)+lead));
							*(*(U+j)+k)=*(*(U+j)+k)-*(*(U+i)+k)**(*(U+j)+lead)/(*(*(U+i)+lead));
						
					}
				}
				
			}
		}
		lead++;
	}
	return MulMatrix(L,U,n);



}

int main()
{
	double **A;//입력받는 변수
	double** result;//결과를 받는 변수
	double **L;//Low 변수
	double **U;//Upper 변수
	int n;
	int i,j;
	double junk;
	while(1)
	{
	printf("system> input size n : ");
	scanf("%d",&n);

	if(n>5)
	{
		printf("n이 5보다 크면 안됩니다.\n");
		continue;
	}
	else if(n<=1)
	{
		printf("n이 2보다 작으면 안됩니다.\n");
		continue;
	}
	else
	{
		break;
	}
	}
	A=(double**)calloc(n,sizeof(double*));
	for(i=0;i<n;i++)
	{
		*(A+i)=(double*)calloc(n,sizeof(double));
	}  
	L=(double**)calloc(n,sizeof(double*));
	for(i=0;i<n;i++)
	{
		*(L+i)=(double*)calloc(n,sizeof(double));
	}  
	U=(double**)calloc(n,sizeof(double*));
	for(i=0;i<n;i++)
	{
		*(U+i)=(double*)calloc(n,sizeof(double));
	}  
	result=(double**)calloc(n,sizeof(double*));
	for(i=0;i<n;i++)
	{
		*(result+i)=(double*)calloc(n,sizeof(double));
	}  
	printf("system> input %d * %d elements\n",n,n);
	for(i=0;i<n;i++)//행렬을 입력
	{
		for(j=0;j<n;j++)
		{
			scanf("%lf",(*(A+i)+j));
		}
	}
	printf("system> input matrix A\n");//행렬 출력
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%7.2lf ",*(*(A+i)+j));
		}
		printf("\n");
	}
	if(n!=5)
	{
	junk=detA(A,n);
	

	if(junk==0)
	{
		printf("system> A is singular\n");
		return -1;
	}
	else
		printf("system> A is non-singular\n");
	}
	printf("system> inverse of matrix A(Theorem 2)\n");
	result=inverseA(A,n);//일반적인 역행렬 구하기 방식
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%7.2lf",*(*(result+i)+j));
		}
	
		printf("\n");
	}
	printf("system> A*A-1\n");
	result=MulMatrix(A,result,n);
	
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%7.2lf",*(*(result+i)+j));
		}
		printf("\n");
	}
	printf("system> inverse of matrix A(Gaussian Elimination)\n");
	result=inverseA_gaussian(A,n);//가우스 소거법에 의한 역행렬
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%7.2lf",*(*(result+i)+j));
		}
		printf("\n");
	}
	printf("system> A*A-1\n");
	result=MulMatrix(A,result,n);//행렬과 그 행렬의 역행렬의 곱셈
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%7.2lf",*(*(result+i)+j));
		}
		printf("\n");
	}
	printf("system> Low triangular matrix\n");
	result=matrix_LU(A,U,L,n);//행렬의 삼각화
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%7.2lf",*(*(L+i)+j));
		}
		printf("\n");
	}
	printf("system> Upper triangular matrix\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%7.2lf",*(*(U+i)+j));
		}
		printf("\n");
	}
	printf("systme> L*U\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%7.2lf",*(*(result+i)+j));
		}
		printf("\n");
	}

}
