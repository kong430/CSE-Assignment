public class Engineer extends Employee {
	double rate;
	public Engineer() {}
	public Engineer(String name, int employeeNum) {
		this.name = name;
		this.employeeNum = employeeNum;
		this.rate = 4;
		this.department = "Engineering";
	}
	public boolean equals(Object obj) {
		if (getClass()!=obj.getClass()) return false;
		else {
			Engineer eng = (Engineer)obj;
			return (name.equals(eng.name)&&employeeNum==eng.employeeNum);
		}
	}
	
	public String toString() {
		return "Name : "+ name+"\nEmp# : "+ employeeNum+"\nDept : "+department+"\n";
	}
	
	public double getPaid() {
		double pay = workHrs*rate;
		return pay;
	}
}
