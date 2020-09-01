import java.util.Random;

public class Gasoline extends Oil {
	private int price;
	private double VAT;
	
	public Gasoline(int price, String company) {
		super(company, "gasoline");
		this.price = price;
		Random rnd = new Random();
		VAT = (rnd.nextInt(30)+1)/100.0;
	}
	
	public double getOilPrice() {
		double priceInStore = price+price*VAT;
		return priceInStore;
	}
	
	public String toString() {
		return super.toString()+"\nsupply price : "+price+"\n";
	}
}
