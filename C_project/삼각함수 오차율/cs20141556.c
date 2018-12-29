#include <stdio.h>
#include <math.h>
void taylor_sin(double, int, double*);//Taylor series를 이용해 sin()함수 구현
void taylor_cos(double, int, double*);//Taylor series를 이용해 cos()함수 구현
void taylor_tan(double, int, double*);//Taylor series를 이용해 tan()함수 구현
int factorial(int);//Factorial computation 구현
double angle_to_radian(double);//60분법 형태의 각도를 라디안으로 변환하는 함수
void compute_error_rate(double,double*, double*, double*);//오차율을 구하는 함수

int main()
{
  double ang;//60분법 형태의 각도
  double ang2;//라디안 형태의 각도
  int num;//항의 개수
  double ms,mc,mt;//Math Library를 이용해서 구한 값들
  double sinh;
  double cosh;
  double tanh;//Taylor series를 이용해서 구한 값들
  
  printf("Input angle : ");
  
  scanf("%lf",&ang);
  ang2=angle_to_radian(ang);//ang을 라디안 형태로 바꿈
  ms=sin(ang2);//실제 sin값
  mc=cos(ang2);//실제 cos값
  mt=tan(ang2);//실제 tan값
  printf("Input the number of terms (3~5) : ");//항의 개수를 입력받는다.
  scanf("%d",&num);
  if(num>2 && num<6)
  {



  printf("<Sin, Cos, Tan function using math library>\n");
  printf("Sin(%.2lf)  :%25.15lf\n",ang,ms);//실제 sin값
  printf("Cos(%.2lf)  :%25.15lf\n",ang,mc);//실제 cos값
  if(((int)ang/90)%2==1||-((int)ang/90)%2==1)//ang이 90도의 홀수배일 때
  {
    printf("Tan(%.2lf)  :        Infinite\n",ang);
  }
  else
  {
   printf("Tan(%.2lf)  :%25.15lf\n",ang,mt);//실제 tan값
  }
  printf("\n");
  printf("<Sin, Cos, Tan function using taylor series>\n");
  
  taylor_sin(ang2,num,&sinh);//테일러 함수에 라디안 값을 대입한다
  taylor_cos(ang2,num,&cosh);
  taylor_tan(ang2,num,&tanh);
  printf("Sin(%.2lf)  :%25.15lf\n",ang,sinh);//테일러함수의 sin값
  printf("Cos(%.2lf)  :%25.15lf\n",ang,cosh);//테일러함수의 cos값
  printf("Tan(%.2lf)  :%25.15lf\n",ang,tanh);//테일러함수의 tan값
  printf("\n");

  
  compute_error_rate(ang2,&sinh,&cosh,&tanh);
  if((int)ang==ang)//ang이 정수일 때
  {
   if(((int)ang/90)%2==1||-((int)ang/90)%2==1)//ang이90도의 홀수배일 때
   {
    printf("The error rate of Sin :%25.13lf\n",sinh);//sin의 오차율
    printf("The error rate of Cos :          Infinite\n");//cos의 오차율
    printf("The error rate of Tan :          Infinite\n");//tan의 오차율
   }
   else if(((int)ang)%180==0)//ang이 180도의 배수일 때
   {
    printf("The error rate of Sin :          Infinite\n");//sin의 오차율
    printf("The error rate of Cos :%25.13lf\n",cosh);//cos의 오차율
    printf("The error rate of Tan :%25.13lf\n",tanh);//tan의 오차율
   }

   else
   {
    printf("The error rate of Sin :%25.13lf\n",sinh);//sin의 오차율
    printf("The error rate of Cos :%25.13lf\n",cosh);//cos의 오차율
    printf("The error rate of Tan :%25.13lf\n",tanh);//tan의 오차율
   }
  }
  else
  {
  printf("The error rate of Sin :%25.13lf\n",sinh);//sin의 오차율
  printf("The error rate of Cos :%25.13lf\n",cosh);//cos의 오차율
  printf("The error rate of Tan :%25.13lf\n",tanh);//tan의 오차율
  }
  }
  else
  {
    printf("Error!\n");//n이 3부터 5사이의 정수가 아닐 때 오류 출력
  }
  return 0;

}
void taylor_sin(double ang2, int num, double* sinh)//테일러sin함수의 정의
{
  if(num==5)
  {
        *sinh=ang2+((double)((-1)/(double)factorial(3))* pow(ang2,3))+((double)(1/(double)factorial(5))* pow(ang2,5))+((double)((-1)/(double)factorial(7))* pow(ang2,7))+((double)(1/(double)factorial(9))* pow(ang2,9));
  }
  if(num==4)
  {
        *sinh=ang2+((-1)/(double)factorial(3)*pow(ang2,3))+(1/(double)factorial(5)*pow(ang2,5))+((-1)/(double)factorial(7)*pow(ang2,7));
  }
  if(num==3)
  {
        *sinh=ang2+((double)((-1)/(double)factorial(3)) * pow(ang2,3))+((double)(1/(double)factorial(5)) * pow(ang2,5));
                                        
  }
}
void taylor_cos(double ang2, int num, double* cosh)//테일러cos함수의 정의
{
  if(num==5)
   {
         *cosh=1+((-1)/(double)factorial(2)*pow(ang2,2))+(1/(double)factorial(4)*pow(ang2,4))+((-1)/(double)factorial(6)*pow(ang2,6))+(1/(double)factorial(8)*pow(ang2,8));
   }
  if(num==4)
   {
         *cosh=1+((-1)/(double)factorial(2)*pow(ang2,2))+(1/(double)factorial(4)*pow(ang2,4))+((-1)/(double)factorial(6)*pow(ang2,6));
   }
  if(num==3)
   {
         *cosh=1+((-1)/(double)factorial(2)*pow(ang2,2))+(1/(double)factorial(4)*pow(ang2,4));
   }
}
void taylor_tan(double ang2, int num, double* tanh)//테일러tan함수의 정의
{
  double a,b;
  taylor_sin(ang2,num,&a);
  taylor_cos(ang2,num,&b);
  *tanh=a/b;//tan=sin/cos
}

int factorial(int x)//팩토리얼 함수
{
  int result;
  if(x==1)
  {
    result=1;
    return result;
  }
  if(x==2)
  {
    result=2;
    return result;
  }
  if(x==3)
  {
    result=6;
    return result;
  }
  if(x==4)
  {
    result=24;
    return result;
  }
  if(x==5)
  {
    result=120;
    return result;
  }
  if(x==6)
  {
    result=720;
    return result;
  }
  if(x==7)
  {
    result=5040;
    return result;
  }
  if(x==8)
  {
    result=40320;
    return result;
  }
  if(x==9)
  {
    result=362880;
    return result;
  }
  if(x==10)
  {
    result=3628800;
    return result;
  }
  if(x==11)
  {
    result=3628800*11;
    return result;
  }
}
double angle_to_radian(double ang)//60분법을 호도법으로 변환시켜주는 함수
{
  double result;
  if(ang>=360)
    {
      double a;
      a=ang-(int)ang;//ang의 소수자리
      ang=(int)ang%360+a;//ang에서 360으로 나눈 나머지를 ang에 넣는다.
      result=ang/180*M_PI;//180으로 나누고 파이를 곱함으로서 호도법으로 변환한다.
      return result;
    }
  if(ang<=-360)
  {
    double a;
    double b;
    a=fabs(a);//a는 ang의 절대값
    b=a-(int)a;//b는 a의 소수자리
    a=((int)a)%360+b;//a에서 360으로 나눈 나머지를 a에 넣는다.
    result=-a/180*M_PI;//호도법으로 변환한다.
    return result;
  }
    
  else
  {
    result=ang/180*M_PI;//호도법으로 변환한다.
    return result;
  }
}
void compute_error_rate(double ang2,double *sinh,double *cosh,double *tanh)//sin,cos,tan의 각각의 오차율을 계산해주는 함수
{
  double ms,mc,mt;
  double a,b,c;
   ms=sin(ang2);//사인값(math library)
   mc=cos(ang2);//코사인값
   mt=tan(ang2);//탄젠트값
   a=*sinh;//테일러 함수에 의한 값
   b=*cosh;//"
   c=*tanh;//"
  *sinh=fabs(ms-a)/fabs(ms)*100;//각각의 오차율을 포인트 변수에 저장한다
  *cosh=fabs(mc-b)/fabs(mc)*100;
  *tanh=fabs(mt-c)/fabs(mt)*100;
}
