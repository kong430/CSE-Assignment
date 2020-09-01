
public class Kitchen {
	private int ovenNum;
	private int friedpanNum;
	private int potNum;
	
	public Kitchen() {
		ovenNum = 1;
		friedpanNum = 3;
		potNum = 3;
	}
	
	public synchronized void useOven() throws InterruptedException{
		if (ovenNum==0) {
			System.out.println("The oven is in use.");
			wait();
		}
		ovenNum--;
	}
	
	public synchronized void releaseOven() throws InterruptedException{
		if (ovenNum<1) ovenNum++;
		notifyAll();
	}
	
	public synchronized void useFriedpan() throws InterruptedException{
		if (friedpanNum==0) {
			System.out.println("The firedpan is in use.");
			wait();
		}
		friedpanNum--;
	}
	
	public synchronized void releaseFriedpan() throws InterruptedException{
		if (friedpanNum<3) friedpanNum++;
		notifyAll();
	}
	
	public synchronized void usePot() throws InterruptedException{
		if (potNum==0) {
			System.out.println("The pot is in use.");
			wait();
		}
		potNum--;
	}
	
	public synchronized void releasePot() throws InterruptedException{
		if (potNum<3) potNum++;
		notifyAll();
	}
}
