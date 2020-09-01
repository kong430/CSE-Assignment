public class Manager extends Employee {
	int officeNum;
	String team;

	public Manager(String name, int employeeNum, int officeNum, String team) {
		this.name = name;
		this.employeeNum = employeeNum;
		this.officeNum = officeNum;
		this.team = team;
		this.department = "Management";		
	}
	
	public String toString() {
		return "Name : " + name + "\nEmp# : " + employeeNum
				+ "\nlocation : "+department+", office : "+officeNum;
	}
	public boolean equals(Object obj) {
		if (obj == null) return false;
		else if(getClass()!=obj.getClass()) return false;
		else {
			Manager emp = (Manager)obj;
			return (super.equals(obj)&&
					officeNum ==emp.officeNum && team ==emp.team);
		}
	}
	
	

}
