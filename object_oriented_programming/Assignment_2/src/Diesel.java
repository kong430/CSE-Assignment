import java.util.Random;

public class Diesel extends Oil{
	private int price;
	private double VAT;
	private double envTax;
	
	public Diesel(int price, String company) {
		super(company, "diesel");
		this.price = price;
		Random rnd = new Random();
		VAT = (rnd.nextInt(30)+1)/100.0;
		envTax = 500;		
	}
	
	public double getOilPrice() {
		double priceInStore = price+envTax+price*VAT;
		return priceInStore;
	}
	
	public String toString() {
		return super.toString()+"\nsupply price : "+price+"\n";
	}
}
