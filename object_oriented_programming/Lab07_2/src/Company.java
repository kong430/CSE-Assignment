public class Company {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Employee emp1 = new Manager("John Smith", 1234, 25, "door and panels");
		Employee emp2 = new Engineer("Peter Anderson", 1432, "fabrication #7", "door and panels");
		Manager emp5 = new Manager("John Smith", 1234, 25, "team 7");
		
		Employee emp3 = new Employee("Jane Roberts", 2345);
		Employee emp4 = new Employee("John Smith", 1234);
		
		System.out.println(emp1.toString()+"\n");
		System.out.println(emp2.toString()+"\n");
		System.out.println(emp3.toString()+"\n");
		System.out.println(emp4.toString()+"\n");
		
		System.out.println(emp1.equals(emp2));
		System.out.println(emp1.equals(emp5));
		System.out.println(emp1.equals(emp4));
		
	}

}
