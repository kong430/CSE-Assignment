package kr.co.Quiz1;
import java.util.Scanner;
import kr.co.Quiz.Collection.*;

public class Program {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		System.out.print("�л� ���� �Է� �ϼ��� : ");
		Scanner scanner = new Scanner(System.in);
		
		Student[] StudentList;
		int size = scanner.nextInt();
		StudentList = new Student[size];
		
		for (int i=0;i<size;i++) {
			System.out.print("�л� �̸��� �Է��ϼ��� : ");
			String Name_in = scanner.next();
			System.out.print("���� ������ �Է��ϼ��� : ");			
			int Korean_in = scanner.nextInt();
			System.out.print("���� ������ �Է��ϼ��� : ");
			int Math_in = scanner.nextInt();
			System.out.print("���� ������ �Է��ϼ��� : ");
			int English_in = scanner.nextInt();
			StudentList[i] = new Student(Name_in, Korean_in, Math_in, English_in);
		}
		Student.makeRank(StudentList);
		
		for (int i=0;i<size;i++) {
		System.out.println(i+1 +". " + StudentList[i].toString());
		}
	}
}
