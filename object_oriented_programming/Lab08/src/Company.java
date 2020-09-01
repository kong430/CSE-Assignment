public class Company {
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Employee emp1 = new Manager("John Smith", 1234);
		Employee emp2 = new Engineer("Peter Anderson", 1432);
		Manager emp5 = new Manager("Jenny Allen", 1734);
		
		System.out.println(emp1.toString());
		System.out.println(emp2.toString());
		System.out.println(emp5.toString());
		
		emp1.doWork(20);
		emp2.doWork(90);
		
		System.out.println("emp1 Salary: "+emp1.getPaid());
		System.out.println("emp2 Salary: "+emp2.getPaid());
		System.out.println("emp5 Salary: "+emp5.getPaid());
		
		System.out.println("emp1 and emp2 has the same salary? "+ emp1.equalPay(emp2));
		System.out.println("emp1 and emp5 has the same salary? "+ emp1.equalPay(emp5));
		emp5.doWork(20);
		System.out.println("emp1 and emp5 has the same salary? "+ emp1.equalPay(emp5));
		emp1.doWork(40);
		System.out.println("emp1 and emp2 has the same salary? "+ emp1.equalPay(emp2));
	}
}
