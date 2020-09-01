import java.util.Scanner;
public class TimeTableApp {
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner input = new Scanner(System.in);
		TimeTable tt = new TimeTable();
		while (true) {
			System.out.println("================Main Menu================");
			System.out.println("(1) Add a class to my time table");
			System.out.println("(2) View the class");
			System.out.println("(3) Print the entire time table");
			System.out.println("(4) Exit the program");
			int num = input.nextInt();
			
			if (num==1) {
				System.out.print("Day : ");
				String day = input.next();
				System.out.print("Period : ");
				int period = input.nextInt();
				System.out.print("Name : ");
				String name = input.next();
				System.out.print("Tutor : ");
				String tutor = input.next();
				System.out.print("Room : ");
				String room = input.next();
				day = day.toUpperCase();
				
				if (tt.setSchedule(day, period, name, tutor, room)==true) {
					System.out.println("Class successfully added");	
				}
				else System.out.println("Class was NOT successfully added");
			}
			else if (num==2) {
				System.out.println("==============View the Class==============");
				System.out.println("(1) At a specific period");
				System.out.println("(2) By subject title");
				int num_2 = input.nextInt();
				if (num_2 == 1) {
					System.out.print("Day : ");
					String day = input.next();
					System.out.print("Period : ");
					int period = input.nextInt();
					day = day.toUpperCase();
					System.out.println("At that time you have\n"+tt.getSchedule(day, period).getDetails());
				}
				else if (num_2==2) {
					System.out.println("=============By subject title=============");
					System.out.println("(1) Specific title");
					System.out.println("(2) View all subjects");
					int num_2_2 = input.nextInt();
					if (num_2_2 ==1) {
						System.out.print("Title : ");
						String name = input.next();
						if (tt.getSubjectByTitle(name)!=null) {
							System.out.println(tt.getSubjectByTitle(name).getDetails());
						}	
						else System.out.println("It doesn't exist");
					}
					else if (num_2_2 == 2) {
						tt.getAllSubjects();
						for (int i=0;i<tt.sj_arr.length;i++) {
							if (tt.sj_arr[i] == null) break;
							System.out.println("------------");
							System.out.println(tt.sj_arr[i].getDetails());
							System.out.println("------------");
						}
					}
					else System.out.println("Insert 1 ~ 2");
				}
				else System.out.println("Insert 1 ~ 2");
			}
			else if (num==3) {
				tt.printTimetable();
			}
			else if (num==4) {
				System.out.println("Exit the application");
				break;
			}
			else System.out.println("Insert 1 ~ 4");
		}
	}
}
