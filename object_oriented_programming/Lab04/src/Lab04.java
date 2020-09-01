public class Lab04 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub

		System.out.println();
		System.out.println();
		System.out.println();
		City seoul = new City("Seoul",23,45);
		System.out.println(seoul.toString());
		
		City paris = new City("Paris",123,41);
		System.out.println(paris.toString());
		
		City racoonCity = new City("RacoonCity");
		System.out.println(racoonCity.toString());
		
		City megaCity = new City("Mega City");
		System.out.println(megaCity.toString());
		
		System.out.println("Seoul-Paris : " + City.getDistance(seoul, paris));
		System.out.println("Seoul-Racoon City : " + City.getDistance(seoul, racoonCity));
		System.out.println("Paris-Mega City : " + City.getDistance(paris, megaCity));
		
	}

}
