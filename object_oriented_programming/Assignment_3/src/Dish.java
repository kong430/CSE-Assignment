
public class Dish {
	private int tableNum;
	private String name;
	private String tool;
	private int time;
	
	public int gettableNum() {
		return tableNum;
	}
	
	public String getname() {
		return name;
	}
	
	public String gettool() {
		return tool;
	}
	
	public int gettime() {
		return time;
	}
	
	public Dish(int tableNum, String name) {
		this.tableNum = tableNum;
		this.name = name;
		setTool(name);
		setTime(tool);
	}
	
	public void setTool(String name) {
		if (name.equals("ramen")||name.equals("stew")) {
			tool = "pot";
		}
		if (name.equals("friedrice")){
			tool = "fryingpan";
		}
		if (name.equals("ovenroast")) {
			tool = "oven";
		}
	}
	
	public void setTime(String tool) {
		if (tool.equals("pot")) {
			time = 350;
		}
		if (tool.equals("fryingpan")) {
			time = 500;
		}
		if (tool.equals("oven")) {
			time = 1300;
		}
	}
}
