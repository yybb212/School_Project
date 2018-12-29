package hw2;
class Employee {
	private long id;
	private String name;
	private int age;
	Employee(){
		id=0;
		name="NULL";
		age=0;
	}
	Employee(long id,String name,int age){
		this.id=id;
		this.name=name;
		this.age=age;
	}
	public void print() {
		int num;
		if(id/100>=1)
			num=0;
		else if(id/10>=1)
			num=1;
		else if(id/1>=1)
			num=2;
		else
			num=3;
		System.out.print("[e");
		int i;
		for(i=0;i<num;i++)
			System.out.print("0");
		System.out.println(id+", "+name+", "+age+"]");
	}
	long retid() {
		return id;
	}
	String retname() {
		return name;
	}
	int retage() {
		return age;
	}
}
class Manager extends Employee{
	private String department;
	Manager(){
		super();
	}
	Manager(int id,String name,int age,String department){
		super(id,name,age);
		this.department=department;
	}
	public void print() {
		long id=super.retid();
		String name=super.retname();
		int age=super.retage();
		int num;
		if(id/100>=1)
			num=0;
		else if(id/10>=1)
			num=1;
		else if(id/1>=1)
			num=2;
		else
			num=3;
		System.out.print("[m");
		int i;
		for(i=0;i<num;i++)
			System.out.print("0");
		System.out.println(id+", "+name+", "+age+", "+department+"]");
		
		
	}
}
public class s20141556hw2 {

	public static void main(String[] args) {
		//System.out.println("<<output>>");
		System.out.println("===Employee===");
		Employee em[]=new Employee[5];
		em[0]=new Employee(1,"John",27);
		em[1]=new Employee(2,"Eujin",25);
		em[2]=new Employee(3,"Alex",26);
		em[3]=new Employee(4,"Jenny",23);
		em[4]=new Employee(5,"Tom",25);
		Manager ma[]=new Manager[2];
		ma[0]=new Manager(1,"Andy",33,"Marketing");
		ma[1]=new Manager(2,"Kate",30,"Sales");
		
		for(int i=0;i<5;i++)
			em[i].print();
		System.out.println("===Manager===");
		for(int i=0;i<2;i++)
			ma[i].print();
	
	}

}
