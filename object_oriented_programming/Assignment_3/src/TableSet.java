
public class TableSet {
	private Table[] tableSet;
	
	public TableSet() {
		tableSet = new Table[5];
		for (int i=0;i<tableSet.length;i++) {
			tableSet[i] = new Table();
		}
	}
	
	public void addtoTable(int index, int TableNum, String name) {
		tableSet[index].getdishSet().add(new Dish(TableNum, name));
		tableSet[index].setTableNum(TableNum);
	}
	
	public Table[] gettableSet() {
		return tableSet;
	}
}
