package hw3;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.math.BigDecimal;
import java.math.MathContext;
public class s20141556hw3 extends Frame {
	
	private TextArea area;
	private Frame Cal;
	int paren_flag;
	boolean dot_flag;
	boolean equal_flag;
	public s20141556hw3(String str){
		
		paren_flag=0;
		dot_flag=false;
		equal_flag=false;
		
		Cal=new Frame(str);
		Cal.setLayout(new BorderLayout());
		
		Cal.setSize(400,600);
	    Cal.setBackground(Color.CYAN);
		
	    /***************TEXT AREA*****************/
	    
	    Panel p=new Panel();
	    area=new TextArea("",5,30,TextArea.SCROLLBARS_NONE);	    
	    //area.setHorizontalAlignment(JTextField.RIGHT);
	    //area.setComponentOrientation(ComponentOrientation.RIGHT_TO_LEFT);
	    area.setBounds(5,5,30,30);
	    p.add(area);
	    Cal.add(p,BorderLayout.CENTER);
	    /*****************************************/    
	    
	    
	    /***************BUTTON********************/
		///7///
	    Panel p2=new Panel();
	    p2.setLayout(new GridLayout(4,5));
	  
		Button seven=new Button("7");
		
		///8///
		Button eight=new Button("8");
		
		///9///
		Button nine=new Button("9");
		///"/"///
		Button divide=new Button("/");
		///C///
		Button C = new Button("C");
		/// 4///
		Button four = new Button("4");
		/// 5///
		Button five = new Button("5");
		/// 6///
		Button six = new Button("6");
		/// *///
		Button multiply = new Button("*");
		/// <-///
		Button back = new Button("<-");
		/// 1///
		Button one = new Button("1");
		/// 2///
		Button two = new Button("2");
		/// 3///
		Button three = new Button("3");
		/// minus///
		Button minus = new Button("-");
		/// (///
		Button left = new Button("(");
		/// 0///
		Button zero = new Button("0");
		/// .///
		Button dot = new Button(".");
		/// =///
		Button equal = new Button("=");
		/// +///
		Button plus = new Button("+");
		/// )///
		Button right = new Button(")");
		

		// seven.addActionListener(new ButtonHandler());
		p2.add(seven);
		seven.addActionListener(new ButtonHandler());
		p2.add(eight);
		eight.addActionListener(new ButtonHandler());
		p2.add(nine);
		nine.addActionListener(new ButtonHandler());
		p2.add(divide);
		divide.addActionListener(new ButtonHandler());
		p2.add(C);
		C.addActionListener(new ButtonHandler());
		p2.add(four);
		four.addActionListener(new ButtonHandler());
		p2.add(five);
		five.addActionListener(new ButtonHandler());
		p2.add(six);
		six.addActionListener(new ButtonHandler());
		p2.add(multiply);
		multiply.addActionListener(new ButtonHandler());
		p2.add(back);
		back.addActionListener(new ButtonHandler());
		p2.add(one);
		one.addActionListener(new ButtonHandler());
		p2.add(two);
		two.addActionListener(new ButtonHandler());
		p2.add(three);
		three.addActionListener(new ButtonHandler());
		p2.add(minus);
		minus.addActionListener(new ButtonHandler());
		p2.add(left);
		left.addActionListener(new ButtonHandler());
		p2.add(zero);
		zero.addActionListener(new ButtonHandler());
		p2.add(dot);
		dot.addActionListener(new ButtonHandler());
		p2.add(equal);
		equal.addActionListener(new ButtonHandler());
		p2.add(plus);
		plus.addActionListener(new ButtonHandler());
		p2.add(right);
		right.addActionListener(new ButtonHandler());
		
		
		Cal.add(p2, BorderLayout.SOUTH);
		
		/*****************************************/
		
		Cal.pack();
		WindowDestroyer x=new WindowDestroyer();
		Cal.addWindowListener(x);
		Cal.setVisible(true);
	}
	public class KeyHandler implements KeyListener{

		@Override
		public void keyPressed(KeyEvent e) {
			// TODO Auto-generated method stub
			char c=e.getKeyChar();
			String o=area.getText();
			int len=o.length();
			char last;
			if(len!=0)
				last=o.charAt(len-1);
			else
				last='\0';
			
			if(c=='0'||c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9')
			{
				if(!grammer(c))
					e.consume();
			}
			else if(c=='+'||c=='-'||c=='/'||c=='*')
			{
				if(!grammer(c))
					e.consume();
				else
					dot_flag=false;
			}
			else if(c=='(')
			{
				if(!grammer(c))
					e.consume();
				else
					paren_flag++;
			}
			else if(c==')')
			{
				if(!grammer(c))
					e.consume();
				else {
					paren_flag--;
					dot_flag=false;
				}
			}
			else if((int)c==8)//Back Space 일 때
			{
				if(last==')')
					paren_flag++;
				if(last=='.')
					dot_flag=false;
			}
			else if(c=='=')
			{
				if(!grammer(c))
					e.consume();
				else {
					dot_flag=false;
					String s=area.getText();
					s=s+'='+"\r\n"+"1000";
					area.setText(s);
				
				}
			}
			else if(c=='.')
			{
				if(!grammer(c))
					e.consume();
				else
					dot_flag=true;
			}
			else
				e.consume();
			
		}

		@Override
		public void keyReleased(KeyEvent e) {
			// TODO Auto-generated method stub
			
		}

		@Override
		public void keyTyped(KeyEvent e) {
			// TODO Auto-generated method stub
			
		}
	
	}
	 
	class ButtonHandler implements ActionListener{
		public void actionPerformed(ActionEvent e)
		{
			if(equal_flag)//이미 결과를 낸 상태면 다 지우고 새롭게 시작
			{
				String o2=e.getActionCommand();
				char c2=o2.charAt(0);
				if((c2>='0'&&c2<='9')||c2=='(') {//숫자로 시작할 경우 새롭게 시작
					equal_flag=false;
					String k="";
					area.setText(k);
				}
				else if(c2=='-'||c2=='+'||c2=='*'||c2=='/')//연산자를 입력할 경우 결과값을 그대로 이용
				{
					equal_flag=false;
					String k=area.getText();
					int i=k.indexOf('=');
					area.setText(k.substring(i+2));
				}
				
				
			}
			
			String o=e.getActionCommand();
			char c=o.charAt(0);
			o=area.getText();
			int len=o.length();
			char last;
			if(len!=0)
				last=o.charAt(len-1);
			else
				last='\0';
			
			if(c=='0'||c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9')
			{
				if(!grammer(c))
					return;
			}
			else if(c=='.')
			{
				if(!grammer(c))
					return;
				else {
					dot_flag=true;
				}
			}
			else if(c=='+'||c=='-'||c=='/'||c=='*')
			{
				if(!grammer(c))
					return;
				else {
					dot_flag=false;
				}
			}
			else if(c=='(')
			{
				if(!grammer(c))
					return;
				else
					paren_flag++;
			}
			else if(c==')')
			{
				if(!grammer(c))
					return;
				else {
					paren_flag--;
					dot_flag=false;
				}
			}
			else if(c=='<')
			{
				if(!grammer(c))
					return;
				if(last==')')
					paren_flag++;
				if(last=='.')
					dot_flag=false;
				String s=area.getText();
				s=s.substring(0, s.length()-1);
				area.setText(s);
				
				return;
			}
			else if(c=='C')
			{
				String s="";
				area.setText(s);
				paren_flag=0;
				dot_flag=false;
				
				return;
			}
			else if(c=='=')
			{
				if(!grammer(c))
					return;
				else {
					dot_flag=false;
					String s=area.getText();
					//area.setText(s);
					double answer =calculate(s);
				
					int answer2;
					if(answer%1==0)//정수일 때
					{
						answer2=(int)answer;
						area.setText(s+"="+'\n'+answer2);
					}
					else
						area.setText(s+"="+'\n'+answer);
					equal_flag=true;
					return;
				}
			}
			else
			{}
			String new2=area.getText();
			if(c=='.')
				new2=new2+".";
			else if(c=='/')
				new2=new2+"/";
			else
				new2=new2+c;
			area.setText("");
			area.setText(new2);

		}
	}
	/****************************************/
	public boolean grammer(char input)
	{
		
		//if(!paren_flag)
			//return false;
		String o=area.getText();
		int len=o.length();
		char last;
		if(len!=0)
			last=o.charAt(len-1);
		else
			last='\0';
			
		if(last=='\0')//처음 시작할 때
		{
			if(('0'<=input&&input<='9')||input=='-' ||input=='(')
				return true;
			else if(input==8)
				return false;
			else
				return false;
		}
		else//처음 시작이 아닐 때
		{
			if('0'<=last&&last<='9')
			{
				if(('0'<=input&&input<='9')||input=='/'||input=='*'||(int)input==8||input=='-'||input=='+'||input=='=')
					return true;
				else if(input=='.'&&dot_flag==false)
					return true;
				else if(input==')'&&paren_flag>0)
					return true;
				else
					return false;
			}
			else if(last=='/'||last=='*')
			{
				if(('0'<=input&&input<='9')||(int)input==8||input=='(')
					return true;
				else if(input==')')//&&paren_flag>0)
					return false;
				else
					return false;
			}
			else if(last=='(')
			{      
				if(('0'<=input&&input<='9')||(int)input==8||input=='-'||input=='(')
					return true;
				else
					return false;
			}
			else if(last==')')
			{
				if(input=='+'||input=='-'||(int)input==8||input=='*'||input=='/'||input=='=')
					return true;
				else if(input==')'&&paren_flag>0)
					return true;
				else
					return false;
			}
			else if(last=='+'||last=='-')
			{
				if(('0'<=input&&input<='9')||(int)input==8||input=='(')
					return true;
				else
					return false;
			}
			else if(last=='.')
			{
				if(('0'<=input&&input<='9')||(int)input==8)
					return true;
				else
					return false;
			}
			else
				return false;

		}
		
	}
	public static double calculate(String s)
	{
		String[] num;
		num=new String[50];
		
		String temp="";
		int index=0;
		
		int i;
		for(i=0;i<s.length();i++)
		{

			char c=s.charAt(i);
			if((c>='0'&&c<='9')||c=='.')
			{
				temp=temp+c;
				if(i==s.length()-1)
					num[index++]=temp;
			}
			else if(c=='+'||c=='-'||c=='/'||c=='*'||c==')')
			{
				//if(i!=0)//처음에 -가 나올 때를 제외
					//num[index++]=temp;
				if(i==0||(i>0&&s.charAt(i-1)==')'))
					temp="";
				else
					num[index++]=temp;
				temp="";
				num[index++]=c+"";
			}
			else
				num[index++]=c+"";
		}
		num[index]="\0";
		/*for(i=0;i<index;i++)
			System.out.println(num[i]);*/
		/* 			여기까지 num 배열에 s를 parsing  	*/
		//double result=0;
		BigDecimal result=new BigDecimal("0");
		int op=0;//+:0 -:1 *:2 /:3
		for(i=0;i<index;i++)
		{
			//System.out.println("i is "+i);
			String c=num[i];
			char c_=c.charAt(0);
			if(c_=='-')
				op=1;
			else if(c_=='+')
				op=0;
			else if(c_=='*')
				op=2;
			else if(c_=='/')
				op=3;
			else if(c_>='0'&&c_<='9')//숫자일때
			{
				BigDecimal n=new BigDecimal(""+Double.parseDouble(c));
				//System.out.println("answer is "+result.add(n));
				if(op==0)
					result=result.add(n);
				else if(op==1)
					result=result.subtract(n);
				else if(op==2)
					result=result.multiply(n);
				else 
					result=result.divide(n,16,BigDecimal.ROUND_DOWN);
				//System.out.println("result is "+n.add(result));
			}
			else if(c_=='(')
			{
				int j;
				int end=index-1;
				for(j=i;j<index;j++)
				{
					char c2=num[j].charAt(0);
					if(c2==')')
						end=j;
				}//가장 끝에 있는 )인 인덱스를 구해 end에 넣어준다.
				BigDecimal answer=new BigDecimal(""+cal2(num,i+1,end-1));
			
				if(op==0)
					result=result.add(answer);
				else if(op==1)
					result=result.subtract(answer);
				else if(op==2)
					result=result.multiply(answer);
				else 
					result=result.divide(answer,16,BigDecimal.ROUND_DOWN);
				i=end;//) 의 다음으로 바로 이동
			}
			
		}
				
		return result.doubleValue();
	}
	public static double cal2(String[] num,int start,int end)
	{
		if(start==end)//(숫자) 이런 형태일 경우
		{
		
			return Double.parseDouble(num[start]);
		}
		
		BigDecimal result=new BigDecimal(0);
		int op=0;//+:0 -:1 *:2 /:3
		int i;
		for(i=start;i<=end;i++)
		{
			
			String c=num[i];
			char c_=c.charAt(0);
			if(c_=='-')
				op=1;
			else if(c_=='+')
				op=0;
			else if(c_=='*')
				op=2;
			else if(c_=='/')
				op=3;
			else if(c_>='0'&&c_<='9')//숫자일때
			{
				BigDecimal n=new BigDecimal(""+Double.parseDouble(c));
				if(op==0)
					result=result.add(n);
				else if(op==1)
					result=result.subtract(n);
				else if(op==2)
					result=result.multiply(n);
				else 
					result=result.divide(n,16,BigDecimal.ROUND_DOWN);
			}
			else if(c_=='(')
			{
				int j;
				int end2=end;
				for(j=i;j<=end;j++)
				{
					char c2=num[j].charAt(0);
					if(c2==')')
						end=j;
				}//가장 끝에 있는 )인 인덱스를 구해 end에 넣어준다.
				BigDecimal answer=new BigDecimal(""+cal2(num,i+1,end2-1));
				if(op==0)
					result=result.add(answer);
				else if(op==1)
					result=result.subtract(answer);
				else if(op==2)
					result=result.multiply(answer);
				else 
					result=result.divide(answer,16,BigDecimal.ROUND_DOWN);
				i=end2;//) 의 다음으로 바로 이동
			}
			
		}
		return result.doubleValue();
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		s20141556hw3 Cal2 = new s20141556hw3("Calculator");
	}
	
}
