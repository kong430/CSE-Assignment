import java.util.Scanner;

public class PriceListApp {
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner input = new Scanner(System.in);
		PriceList pr= new PriceList();
		int tmp=0;
		
		while (true) {
			System.out.print("===========Main Menu==========\n(1) Add a oil to price list\n"
					+ "(2) View Region Information\n(3) Print the entire price List\n"
					+ "(4) Exit the program\n=============================\nchoose a menu : ");
			int num = input.nextInt();
			if (num == 1) {
				try{
					if (tmp==pr.getVertical()) {
						throw new FullArrayException();
					}
				}
				catch(FullArrayException e){
					System.out.println(e.getMessage());
					int ex_num = input.nextInt();
					pr.extendList(ex_num);
					System.out.println("list is extended\n");
				}
				System.out.print("company : ");
				String oil_c = input.next();
				System.out.print("supply price : ");
				int oil_p = input.nextInt();
				Gasoline ga = new Gasoline(oil_p, oil_c);
				pr.setPriceList(tmp, 0, ga);
				System.out.println("gasoline added\n");
				
				System.out.print("company : ");
				oil_c = input.next();
				System.out.print("supply price : ");
				oil_p = input.nextInt();
				Diesel di = new Diesel(oil_p, oil_c);
				pr.setPriceList(tmp, 1, di);
				tmp++;
				System.out.println("diesel added\n");
			}
				else if (num==2) {
				System.out.print("region number to view : ");
				int region = input.nextInt();
				System.out.println(pr.getRegionInfo(region));
			}
			else if (num==3) {
				pr.printList();
			}
			else if (num==4) {
				System.out.println("Exit Application");
				break;
			}
			else System.out.println("Insert 1 ~ 4");
		}
	}
}
