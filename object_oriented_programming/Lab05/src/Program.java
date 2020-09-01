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
		
		System.out.println("계약일 : "+year+'/'+month+'/'+day);
		System.out.println("Name : "+ e1.getName() + "\n연봉 : "+ e1.getYearlySalary() 
				+ "\n월급 : "+ e1.getMonthlySalary() +"\n재산 : "+ e1.getBalance());
		
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
				System.out.println(year_enter+"년차 연봉이 "+increase_Salary+"% 인상되었습니다.");
				incentive_month = rnd.nextInt(12)+1;
			}
			if (month == incentive_month) {
				e1.receiveSalary();
				System.out.println(year_enter +"년차 "+month+"월에 인센티브를 받았습니다.");
			}
			cal.add(Calendar.MONTH, 1);
			month = cal.get(Calendar.MONTH)+1;
			year = cal.get(Calendar.YEAR);
			month_enter++;
			e1.receiveSalary();
		}
		System.out.println("날짜 : "+year+'/'+month+'/'+day);
		System.out.println("Name : "+ e1.getName() + "\n연봉 : "+ e1.getYearlySalary() 
		+ "\n월급 : "+ e1.getMonthlySalary() +"\n재산 : "+ e1.getBalance());
	}
}
