package oop_2;
import java.util.Scanner;

public class EmployeeManager {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner keyboard = new Scanner(System.in);
		Employee e1 = new Employee("James Wright", 42, "Manager", 20000);
		System.out.printf(e1.toString()+"\n");
		Employee e2 = new Employee("Amy Smith", 27, "Design Coordinator", 8000, 15);
		System.out.printf(e2.toString()+"\n");
		Employee e3 = new Employee("Peter Coolidge", 32, "Assistant Manager", 12000, 7);
		System.out.printf(e3.toString()+"\n");
		Employee e4 = new Employee("John Doe", 22, "Engineer", 10000, 10);
		System.out.printf(e4.toString()+"\n");
		
		//货肺款 employee 积己
		Employee own = new Employee("Min Gyeong", 21, "Student", 15000, 5);
		
		System.out.println(own.equals(e2));
		
		e1.vacation(10);
		e3.vacation(10);
		
		System.out.println(e1.toString()+"\n"+e2.toString());
		System.out.println(e3.toString()+"\n"+e4.toString());
	}

}
