package kr.co.Lab05.Collection;

public class Employee {
	
	private String name;
	private double yearly_salary;
	private double monthly_salary;
	private double balance;
	
	/**
	 * Employee 클래스의 생성자
	 * @param name 이름
	 * @param yearly_salary 연봉
	 */
	public Employee(String name, double yearly_salary) {
		this.name = name;
		this.yearly_salary = yearly_salary;
		monthly_salary = yearly_salary/12;
		balance = 0;
	}
	/**
	 * 이름을 반환하는 getter
	 * @return
	 */
	public String getName() {
		return name;
	}

	/**
	 * 연봉을 반환하는 getter
	 * @return
	 */
	public double getYearlySalary() {
		return yearly_salary;
	}
	
	/**
	 * 월급을 반환하는 getter
	 * @return
	 */
	public double getMonthlySalary() {
		return monthly_salary;
	}
	
	/**
	 * 재산을 반환하는 getter
	 * @return
	 */
	public double getBalance() {
		return balance;
	}
	/**
	 * 연봉을 증가시켜주는 method
	 * @param byPercent
	 */
	public void increaseYearlySalary(double byPercent) {
		yearly_salary += 0.01*byPercent*yearly_salary;
		monthly_salary = yearly_salary/12;
	}
	/**
	 * 월급을 받는 method
	 */
	public void receiveSalary() {
		balance += monthly_salary; 
	}

}
