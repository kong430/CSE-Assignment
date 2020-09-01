import kr.co.Lab05.Collection.*;
import java.util.Calendar;
import java.util.Random;

public class Program {
	
	public static void main(String[] args) {
		Calendar cal = Calendar.getInstance();
		Employee e1 = new Employee("Park", 4500);
		
		int year = cal.get(Calendar.YEAR);
		int month = cal.get(Calendar.MONTH)+1;
		int day = cal.get(Calendar.DAY_OF_MONTH);
		
		System.out.println("����� : "+year+'/'+month+'/'+day);
		System.out.println("Name : "+ e1.getName() + "\n���� : "+ e1.getYearlySalary() 
				+ "\n���� : "+ e1.getMonthlySalary() +"\n��� : "+ e1.getBalance());
		
		Random rnd = new Random();
		int incentive_month = rnd.nextInt(12)+1;
		int year_enter = 1;
		int month_enter = 0;

		while (e1.getBalance() < 20000) {
			if (month_enter == 12*year_enter+1) {
				year_enter++;
				Random rnd2 = new Random();
				double increase_Salary = rnd2.nextInt(10);
				e1.increaseYearlySalary(increase_Salary);
				System.out.println(year_enter+"���� ������ "+increase_Salary+"% �λ�Ǿ����ϴ�.");
				incentive_month = rnd.nextInt(12)+1;
			}
			if (month == incentive_month) {
				e1.receiveSalary();
				System.out.println(year_enter +"���� "+month+"���� �μ�Ƽ�긦 �޾ҽ��ϴ�.");
			}
			cal.add(Calendar.MONTH, 1);
			month = cal.get(Calendar.MONTH)+1;
			year = cal.get(Calendar.YEAR);
			month_enter++;
			e1.receiveSalary();
		}
		System.out.println("��¥ : "+year+'/'+month+'/'+day);
		System.out.println("Name : "+ e1.getName() + "\n���� : "+ e1.getYearlySalary() 
		+ "\n���� : "+ e1.getMonthlySalary() +"\n��� : "+ e1.getBalance());
	}
}
