import java.text.SimpleDateFormat;
import java.util.ArrayList;

public class Chef extends Thread{
	private String name;
	private Kitchen kitchen;
	private ArrayList<Dish> dishes;
	
	public Chef(String name, Kitchen kitchen, ArrayList<Dish> dishes) {
		this.name = name;
		this.kitchen = kitchen;
		this.dishes = dishes;
	}
	
	public void run() {
		try {
			for (int i=0;i<dishes.size();i++) {
				dishes.get(i).setTool(dishes.get(i).getname());
				dishes.get(i).setTime(dishes.get(i).gettool());
					if (dishes.get(i).gettool().equals("pot"))
					{
						kitchen.usePot();
						Thread.sleep(dishes.get(i).gettime());
						System.out.println("Table #"+dishes.get(i).gettableNum()+" / "+dishes.get(i).getname()
								+" is completed by "+ name +". "+new SimpleDateFormat("yyyy-MM-dd HH:mm:ss.SSS").format(System.currentTimeMillis()));
						kitchen.releasePot();
					}
					else if (dishes.get(i).gettool().equals("fryingpan"))
					{
						kitchen.useFriedpan();
						Thread.sleep(dishes.get(i).gettime());
						System.out.println("Table #"+dishes.get(i).gettableNum()+" / "+dishes.get(i).getname()
								+" is completed by "+ name +". "+new SimpleDateFormat("yyyy-MM-dd HH:mm:ss.SSS").format(System.currentTimeMillis()));
						kitchen.releaseFriedpan();
					}
					else if (dishes.get(i).gettool().equals("oven"))
					{
						kitchen.useOven();
						Thread.sleep(dishes.get(i).gettime());
						System.out.println("Table #"+dishes.get(i).gettableNum()+" / "+dishes.get(i).getname()
								+" is completed by "+ name +". "+new SimpleDateFormat("yyyy-MM-dd HH:mm:ss.SSS").format(System.currentTimeMillis()));
						kitchen.releaseOven();
					}
			}
		}catch(InterruptedException e){
			e.printStackTrace();
		}
	}
}