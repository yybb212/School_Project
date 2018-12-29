package hw4;
import java.awt.*;
import java.util.*;
import java.awt.event.*;

public class s20141556hw4 extends Frame implements ActionListener {
	private Canvas canvas;
	public static LinkedList <Ball> ball_list;
	public static int num=0;
	public s20141556hw4(String title) {
		super(title);
		canvas = new Canvas();
		add("Center", canvas);
		Panel p = new Panel();
		Button s = new Button("Start");
		Button c = new Button("Close");
		p.add(s);
		p.add(c);
		s.addActionListener(this);
		c.addActionListener(this);
		add("South", p);
	}

	public void actionPerformed(ActionEvent evt) {
		if (evt.getActionCommand() == "Start") {
			ball_list=new LinkedList <Ball>();
			int i;
			Ball newbb[]=new Ball[5];
			for(i=0;i<5;i++)
			{
				newbb[i]=new Ball(canvas);
				ball_list.add(newbb[i]);
			}
			
			ball_list.get(1).dy=1;
			ball_list.get(1).x=500;
			ball_list.get(1).y=200;
			ball_list.get(2).dx=-1;
			ball_list.get(2).x=200;
			ball_list.get(2).y=100;
			ball_list.get(3).dy=-1;
			ball_list.get(3).dx=-1;
			ball_list.get(3).x=300;
			ball_list.get(3).y=200;
			ball_list.get(4).dx=-1;
			for(i=0;i<5;i++)
			{
				ball_list.get(i).start();
				num++;
				try {
					Thread.sleep(600);
				}catch(InterruptedException e) {
				}
			}
			
		} else if (evt.getActionCommand() == "Close")
			System.exit(0);
	}

	public static void main(String[] args) {
		Frame f = new s20141556hw4("Bounce Thread");
		f.setSize(800, 600);
		WindowDestroyer listener = new WindowDestroyer();
		f.addWindowListener(listener);
		f.setVisible(true);
	}

	class Ball extends Thread {
		private Canvas box;
		private int XSIZE = 32;
		private int YSIZE = 32;
		private int x = 400;
		private int y = 300;
		private int dx = 1;
		private int dy = 1;
		boolean run=false;
		boolean same=false;
		
		public Ball(Canvas c) {
			box = c;
		}

		public void draw() {
			Graphics g = box.getGraphics();
			run=true;
			g.fillOval(x, y, XSIZE, YSIZE);
			g.dispose();
		}
		public void white_draw() {
			Graphics g=box.getGraphics();
			g.setXORMode(box.getBackground());
			//g.setColor(Color.white);
			//g.fillOval(this.x, this.y, 100, 100);
			box.setBackground(Color.white);
			g.clearRect(this.x, this.y, getWidth(), getHeight());
			//g.dispose();
			
		}
		public void move() {
			Graphics g = box.getGraphics();
			g.setXORMode(box.getBackground());
			g.setColor(Color.black);
			g.fillOval(x, y, XSIZE, YSIZE);
			x += dx;
			y += dy;
			Dimension d = box.getSize();
			if (x < 0) {
				x = 0;
				dx = -dx;
			}
			if (x + XSIZE >= d.width) {
				x = d.width - XSIZE;
				dx = -dx;
			}
			if (y < 0) {
				y = 0;
				dy = -dy;
			}
			if (y + YSIZE >= d.height) {
				y = d.height - YSIZE;
				dy = -dy;
			}
			g.fillOval(x, y, XSIZE, YSIZE);
			g.dispose();
		}	
		
		public void run() {
			draw();		
	
			for (int j = 1; j <= 200000&&this.run==true; j++) {
				move();
				
				for(int i=0;i<ball_list.size();i++)
				{
					if(this.run==false)
						break;
					if(i>=ball_list.size())
						continue;
					//System.out.println(i);
					if(ball_list==null)
						break;
					Ball temp=ball_list.get(i);
					if(temp.run==false)
						continue;
					//System.out.println(temp.getName());
					
					if(i==ball_list.indexOf(this))//자기 본인이면 continue
						continue;
					if(temp.run==true)//상대가 run인 상태이면
					{
						if(check_coll(this,temp))//충돌한다면
						{
							temp.run=false;
							this.run=false;
							
							split(this,temp);
							
							//System.out.println("Split!");
							return;
															
						}
					}
				}
				try {
					Thread.sleep(4);
				} catch (InterruptedException e) {
				}
			}
		}
		public void split(Ball a,Ball b)
		{
			a.run=false;
			b.run=false;
			Ball newb[]=new Ball[4];
			int i;
			for(i=0;i<4;i++)
				newb[i]=new Ball(canvas);
			for(i=0;i<2;i++)
			{
				newb[i].XSIZE=a.XSIZE/2;
				newb[i].YSIZE=a.YSIZE/2;
				newb[i].x=a.x;
				newb[i].y=a.y;
				
			}	
			for(i=2;i<4;i++)
			{
				newb[i].XSIZE=b.XSIZE/2;
				newb[i].YSIZE=b.YSIZE/2;
				newb[i].x=b.x;
				newb[i].y=b.y;
				
			}
			if(newb[0].XSIZE<=1||newb[2].XSIZE<=1)
			{
				
				System.exit(0);
			}
		
			if(a.x<b.x)
			{
				newb[0].dx=-1;
				newb[0].dy=-1;
				newb[1].dx=-1;
				newb[1].dy=1;
				newb[2].dx=1;
				newb[2].dy=-1;
				newb[3].dx=1;
				newb[3].dy=1;
				
				newb[0].y-=newb[0].XSIZE+1;
				newb[1].y+=newb[1].XSIZE;
				//newb[0].x-=2;
				//newb[1].x-=2;
				newb[2].y-=newb[2].XSIZE+1;
				newb[3].y+=newb[3].XSIZE;
			}
			else if(a.x==b.x)
			{
				newb[0].dx=-1;
				newb[0].dy=-1;
				newb[1].dx=-1;
				newb[1].dy=1;
				newb[2].dx=1;
				newb[2].dy=-1;
				newb[3].dx=1;
				newb[3].dy=1;
				
				newb[0].y-=newb[0].XSIZE/2+1;
				newb[1].y+=newb[1].XSIZE/2;
				newb[0].x-=2;
				newb[1].x-=2;
				newb[2].x+=2;
				newb[3].x+=2;
				newb[2].y-=newb[2].XSIZE/2+1;
				newb[3].y+=newb[3].XSIZE/2;
				
			}
			else
			{
				newb[3].dx=-1;
				newb[3].dy=-1;
				newb[2].dx=-1;
				newb[2].dy=1;
				newb[1].dx=1;
				newb[1].dy=-1;
				newb[0].dx=1;
				newb[0].dy=1;
				
				newb[3].y-=newb[3].XSIZE+1;
				newb[2].y+=newb[2].XSIZE;
				//newb[3].x-=2;
				//newb[2].x-=2;
				newb[1].y-=newb[1].XSIZE+1;
				newb[0].y+=newb[0].XSIZE;
			
			}
			
			/*if(newb[0].XSIZE<=1||newb[2].XSIZE<=1)
				System.exit(0);*/
			/*int p1=ball_list.indexOf(a);
			int p2=ball_list.indexOf(b);
			if(p1>=0&&p1<ball_list.size())
				ball_list.remove(p1);
			if(p2<ball_list.size()&&p2>=0)
				ball_list.remove(p2);*/
			for(i=0;i<4;i++)
			{
				ball_list.add(newb[i]);
				newb[i].start();
				try {
					Thread.sleep(10);
				} catch (InterruptedException e) {
				}
			}
			
		}
		public boolean check_coll(Ball a,Ball b)//충돌하는지 확인해주는 함수
		{
			double d=Math.sqrt((double)((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)));//두 ball의 중심 거리
			double r=((double)(a.XSIZE+b.XSIZE))/2;
			//boolean result=false;
			/*if(a.x<b.x)
			{
				if(a.x+100*a.dx>b.x)
					result=true;
			}
			else
			{
				if(b.x+100*b.dx>a.x)
					result=true;
			}*/
			
			if(d<=r)//충돌
				return true;
			else
				return false;
			
			
		}
	}
}