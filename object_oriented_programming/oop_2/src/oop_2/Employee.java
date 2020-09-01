package oop_2;

public class Employee {
		private String name;
		private int age;
		private String position;
		private int salary;
		private int vacationDays;
		
		Employee(){
			vacationDays = 20;
		}
		Employee(String na, int ag, String po, int sal){
			name = na;
			age = ag;
			position = po;
			salary = sal;
			vacationDays = 20;
		}
		Employee(String na, int ag, String po, int sal, int vac){
			name = na;
			age = ag;
			position = po;
			salary = sal;
			vacationDays = vac;
		}
		//vacationDays를 기본적으로 20일로 설정한다
		public String getname(){
			return name;
		}
		public int getage() {
			return age;
		}
		public String getposition() {
			return position;
		}
		public int getsalary() {
			return salary;
		}
		public int getvacationDays() {
			return vacationDays;
		}
		//getter
		public void setname(String name) {
			this.name = name;
		}
		public void setage(int age) {
			this.age = age;
		}
		public void setposition(String position) {
			this.position = position;
		}
		public void setsalary(int salary) {
			this.salary = salary;
		}
		public void setvacationDays(int vacationDays) {
			this.vacationDays = vacationDays;
		}
		//setter
		
		public boolean equals(Employee emp) {
			if (this.name.contentEquals(emp.name) && this.age == emp.age && this.position == emp.position)
				return true;
			else
				return false;
		}
		public String toString() {
			return "Name : "+this.name+", Age : "+this.age+", Position : "
				+this.position+", Salary : "+this.salary+", VacationDays : "+this.vacationDays;
		}
		public boolean vacation(int vacationDays) {
			if (this.vacationDays < vacationDays) {
				System.out.println("남은 휴가 일수가 부족합니다.");
				return false;
			}
			else
				this.vacationDays = this.vacationDays - vacationDays;
				System.out.printf("휴가를 사용하였습니다.남은 휴가 일 수 : %d\n", this.vacationDays);
				return true;
		}
}
