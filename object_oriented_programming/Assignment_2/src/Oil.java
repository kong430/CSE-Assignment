
public abstract class Oil {
	private String company;
	private String oilType;
	private double priceInStore;
	
	public Oil(String Company, String oilType) {
		this.company = Company;
		this.oilType = oilType;
		priceInStore = 0;
	}
	
	public double getpriceInStore() {
		return priceInStore;
	}
	
	public void setpriceInStore(double priceInStore) {
		this.priceInStore = getOilPrice();
	}
	
	public String toString() {
		return "company : "+company+"\noil type : "+oilType;
	}
	
	public abstract double getOilPrice();
}