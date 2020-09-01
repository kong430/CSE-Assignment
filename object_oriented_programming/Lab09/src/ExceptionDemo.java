import java.util.Scanner;
class ExceptionDemo {
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner input = new Scanner(System.in);
		Employee emp1 = new Employee("Lee");
		while (true)
			{
			System.out.print(emp1.workDay+"���� �ٹ� �ð��� �Է��ϼ��� : ");
			int work = input.nextInt();
			try {
				if (work<0) throw new NegativeException();
				else if (work==0) throw new Exception("Program Exit");
				else if (work>24) throw new TooMuchStuffException(work);
				else {
					emp1.workHrs += work;
					emp1.workDay++;
					System.out.println("�̸� : "+emp1.name);
					System.out.println("���� �ٹ� �ð� : "+emp1.workHrs);
					System.out.println("No Exception has been occurred");
				}
			}
		catch(NegativeException e){
			System.out.println(e.getMessage());
		}
		catch(TooMuchStuffException e) {
			System.out.println(e.getMessage()+"\n" + work+ " occurs TooMuchStuffException");
		}
		catch(Exception e) {
			System.out.println(e.getMessage());
			System.exit(0);
		}
		finally {
			System.out.println("End of try-catch statement");
		}
	}
	}
}
