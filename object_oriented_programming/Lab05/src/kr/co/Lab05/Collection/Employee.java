package kr.co.Lab05.Collection;

public class Employee {
	
	private String name;
	private double yearly_salary;
	private double monthly_salary;
	private double balance;
	
	/**
	 * Employee Ŭ������ ������
	 * @param name �̸�
	 * @param yearly_salary ����
	 */
	public Employee(String name, double yearly_salary) {
		this.name = name;
		this.yearly_salary = yearly_salary;
		monthly_salary = yearly_salary/12;
		balance = 0;
	}
	/**
	 * �̸��� ��ȯ�ϴ� getter
	 * @return
	 */
	public String getName() {
		return name;
	}

	/**
	 * ������ ��ȯ�ϴ� getter
	 * @return
	 */
	public double getYearlySalary() {
		return yearly_salary;
	}
	
	/**
	 * ������ ��ȯ�ϴ� getter
	 * @return
	 */
	public double getMonthlySalary() {
		return monthly_salary;
	}
	
	/**
	 * ����� ��ȯ�ϴ� getter
	 * @return
	 */
	public double getBalance() {
		return balance;
	}
	/**
	 * ������ ���������ִ� method
	 * @param byPercent
	 */
	public void increaseYearlySalary(double byPercent) {
		yearly_salary += 0.01*byPercent*yearly_salary;
		monthly_salary = yearly_salary/12;
	}
	/**
	 * ������ �޴� method
	 */
	public void receiveSalary() {
		balance += monthly_salary; 
	}

}
