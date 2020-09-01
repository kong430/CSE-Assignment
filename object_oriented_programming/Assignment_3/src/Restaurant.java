import java.util.ArrayList;
import java.util.Scanner;
import java.io.FileInputStream;
import java.io.FileNotFoundException;

public class Restaurant {
	static TableSet tbset = new TableSet();
	static ArrayList<Dish> dishes_lee;
	static ArrayList<Dish> dishes_kang;
	
	public static TableSet loadingData(){
		Scanner inputStream = null;
		try {
			inputStream = new Scanner(new FileInputStream("OrderSheet.txt"));
		} catch (FileNotFoundException e) {
			System.out.println(e.getMessage());
		}
		int tableNum;
		String menu;
		String line = inputStream.nextLine();
		tableNum = (int)line.charAt(7)-48;
		menu = inputStream.nextLine();
		for (int i=0;i<5;i++) {
			while(menu.charAt(0)!='T') {
				tbset.addtoTable(i, tableNum, menu);
				if (!inputStream.hasNextLine()) break;
				menu = inputStream.nextLine();
			}	
			if (menu.charAt(0)=='T') {
				tableNum = (int)menu.charAt(7)-48;
				menu = inputStream.nextLine();
				continue;
			}
		}
		inputStream.close();
		return tbset;
	}
	public static void devideDishes() {
		for (int i=0;i<5;i++) {
			if (i%2==0) {
				for (int j=0;j<tbset.gettableSet()[i].getdishSet().size();j++)
				{
					dishes_lee.add(new Dish(tbset.gettableSet()[i].getTableNum(), tbset.gettableSet()[i].getdishSet().get(j).getname()));
<<<<<<< HEAD
					}
=======
				}
>>>>>>> 2f21290eb9da2b0919673a329a8b363cda85ed85
			}
			else {
				for (int j=0;j<tbset.gettableSet()[i].getdishSet().size();j++) {
					dishes_kang.add(new Dish(tbset.gettableSet()[i].getTableNum(), tbset.gettableSet()[i].getdishSet().get(j).getname()));
					}
<<<<<<< HEAD
=======
			    }
>>>>>>> 2f21290eb9da2b0919673a329a8b363cda85ed85
			}
		}
	}
	public static void main(String[] args) throws InterruptedException{

		tbset = loadingData();
		dishes_lee = new ArrayList<Dish>();
		dishes_kang = new ArrayList<Dish>();
		Kitchen kitchen = new Kitchen();
		
		devideDishes();
		
		Chef lee = new Chef("Lee", kitchen, dishes_lee);
		Chef kang = new Chef("Kang", kitchen, dishes_kang);
		
		lee.start();
		kang.start();
	}

}
