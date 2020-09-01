
public class PriceList {
	private Oil[][] priceList;
	private int vertical;
	
	//행은 지역들, 1열은 휘발유 2열은 경유
	
	public PriceList() {
		this.vertical = 2;
		priceList = new Oil[2][2];
	}
	
	public int getVertical() {
		return this.vertical;
	}
	
	public void setPriceList(int i, int j, Oil oil) {
		priceList[i][j] = oil;
		int priceInStore = 0;
		oil.setpriceInStore(priceInStore);
		
	}

	public void extendList(int amount) {
		Oil[][] new_priceList = new Oil[priceList.length+amount][priceList[1].length];
		for (int i=0;i<priceList.length;i++) {
			for (int j=0;j<priceList[1].length;j++) {
				new_priceList[i][j] = priceList[i][j];
			}
		}
		this.vertical += amount;
		priceList = new_priceList;
	}
	
	public String getRegionInfo(int i) {
			return priceList[i-1][0].toString()+"\n"+priceList[i-1][1].toString();
	}
	
	public void printList() {
		int i=0;
		System.out.println("\t\tGasoline\tDiesel");
		System.out.println("=============================================");
		while (true) {
			if (priceList[i][0]==null) break;
			System.out.print("Region #"+(i+1)+"\t");
			System.out.print(priceList[i][0].getpriceInStore()+"\t\t");
			System.out.println(priceList[i][1].getpriceInStore());
			System.out.println("\n");
			i++;
		}
	}
}
