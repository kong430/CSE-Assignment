public class Manager extends Employee {
	double overtimeRate;
	double rate;
	int regularHrs;
	
	public Manager(String name, int employeeNum) {
		this.name = name;
		this.employeeNum = employeeNum;
		rate = 5.0;
		overtimeRate = 8.0;
		regularHrs = 40;
		department = "Management";
	}
	public boolean equals(Object obj) {
		if (getClass()!=obj.getClass()) return false;
		else {
			Manager man = (Manager)obj;
			return (name.equals(man.name)&&employeeNum==man.employeeNum);
		}
	}
	public String toString() {
		return "Name : "+name+"\nEmp# : "+employeeNum+"\nDept : "+department+"\n";
	}
	public double getPaid() {
		double pay;
		int overtimeHrs = workHrs-regularHrs;
		if (workHrs<40) pay = workHrs*rate;
		else pay = regularHrs*rate + overtimeHrs*overtimeRate;
		return pay;
	}
}

