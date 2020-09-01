public abstract class Employee {
	String name;
	int employeeNum;
	String department;
	int workHrs;
	double salary;
	
	public Employee() {}
	
	public Employee(String name, int employeeNum) {
		this.name = name;
		this.employeeNum = employeeNum;
		workHrs = 0;
		salary = 0;
	}
	
	public String getdepartment() {
		return this.department;
	}
	
	public int getworkHrs() {
		return this.workHrs;
	}
	
	public void setdepartment(String department) {
		this.department = department;
	}
	
	public boolean equals(Object obj) {
		if (getClass()!=obj.getClass()) return false;
		else {
			Employee emp = (Employee)obj;
			return (name.equals(emp.name)&&employeeNum==emp.employeeNum);
		}
	}
	
	public String toString() {
		return "Name : "+ name+"\nEmp# : "+ employeeNum+"\n";
	}
	
	public void doWork(int hrs) {
		this.workHrs+=hrs;
		this.salary = getPaid();
	}
	
	public abstract double getPaid();

	public boolean equalPay(Employee emp) {
		if (emp.salary == this.salary) return true;
		else return false;
	}
}







