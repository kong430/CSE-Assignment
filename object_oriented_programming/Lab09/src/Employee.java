
public class Employee {
	public String name;
	public int workDay;
	public int workHrs;
	
	public Employee(String name) {
		this.name = name;
		workDay = 1;
		workHrs = 0;
	}
	
	public String getname() {
		return name;
	}
	
	public int getworkDay() {
		return workDay;
	}
	
	public int getworkHrs() {
		return workHrs;
	}
	
	public void addWorkDay() {
		workDay++;
	}
	
	public void addWorkHrs(int Hrs) {
		workHrs+=Hrs;
	}
}

