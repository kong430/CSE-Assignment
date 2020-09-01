public class Engineer extends Employee{
	String workZone;
	String project;
	
	public Engineer(String name, int employeeNum, String workZone, String project) {
		this.name = name;
		this.employeeNum = employeeNum;
		this.workZone = workZone;
		this.project = project;
		this.department = "Engineering";
	}
	
	public boolean equals(Object obj) {
		if (obj == null) return false;
		else if(getClass()!=obj.getClass()) return false;
		else {
			Engineer emp = (Engineer)obj;
			return (super.equals(obj)&&
					workZone ==emp.workZone && project == emp.project);
		}
	}
	
	public String toString() {
		return "Name : " + name + "\nEmp# : "+employeeNum+"\nlocation : "
				+department + ", zone : "+ workZone;
	}
}
