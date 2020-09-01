import java.util.Random;

public class City {
	private String name;
	private int location_x;
	private int location_y;
	private Random rnd;
	
	public City(String name, int location_x, int location_y)
	{
		this.name = name;
		this.location_x = location_x;
		this.location_y = location_y;		
	}
	public City(String name)
	{
		this.name = name;
		rnd = new Random();
		location_x = rnd.nextInt(361);
		location_y = rnd.nextInt(361);
	}
	public String getName()
	{
		return name;
	}
	public int getLocation_x()
	{
		return location_x;
	}
	public int getLocation_y()
	{
		return location_y;
	}
	public boolean equals(City city)
	{
		if(name == city.getName() &&
				location_x == city.getLocation_x() &&
				location_y == city.getLocation_y())
		{
			return true;
		}
		return false;
	}
	public String toString()
	{
		return name + ", " + location_x + ", " + location_y;
	}
	public static double getDistance(City a, City b)
	{
		double x = Math.pow((a.getLocation_x() - b.getLocation_x()),2);
		double y = Math.pow((a.getLocation_y() - b.getLocation_y()),2);
		
		return Math.sqrt(x+y);
	}
}
