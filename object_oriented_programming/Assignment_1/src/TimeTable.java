public class TimeTable {
	private Subject[][] timeTable;
	Subject[] sj_arr = new Subject[55];
	public TimeTable() {
		initialize();
	}
	private void initialize() {
		timeTable = new Subject[10][5];
		for (int i=0;i<10;i++)
			for (int j=0;j<5;j++) {
				if (i!=2 && i!=6) timeTable[i][j] = new Subject("----");
			}
		for (int j=0;j<5;j++) {
			timeTable[2][j] = new Subject("BREAK");
			timeTable[6][j] = new Subject("LUNCH");
		}
	}
	private int getNumByDay(String day) {
		if (day.equals("MON")) return 0;
		else if (day.equals("TUE")) return 1;
		else if (day.equals("WED")) return 2;
		else if (day.equals("THU")) return 3;
		else if (day.equals("FRI")) return 4;
		else return -1;
	}
	public Subject getSchedule(String day, int period) {
		int int_day = getNumByDay(day);
		return timeTable[period-1][int_day];
	}
	public Subject[] getAllSubjects() {
		int cnt = 0;
		for (int i=0;i<10;i++)
			for (int j=0;j<5;j++)
				if (timeTable[i][j].getname()!="----" && timeTable[i][j].getname()!="BREAK"
				&&timeTable[i][j].getname()!="LUNCH") {
					sj_arr[cnt] = timeTable[i][j];
					cnt++;
				}
		return sj_arr;
	}
	public Subject getSubjectByTitle(String title) {
		for (int i=0;i<10;i++) {
			for (int j=0;j<5;j++) {
				if (timeTable[i][j].getname().equals(title)) return timeTable[i][j];
			}
		}
		return null;
	}
	public boolean setSchedule(String day, int period, String name, String tutor, String room) {
		int int_day = getNumByDay(day);
		if (period == 3 || period == 7) return false;
		else {
		timeTable[period-1][int_day] = new Subject(name, tutor, room);
		return true;
		}
	}
	public void printTimetable() {
		for (int i=0;i<10;i++) {
			if (i==0) System.out.println("\tMON\tTUE\tWED\tTHU\tFRI");
			for (int j=0;j<5;j++) {
				if (j==0) System.out.print(i+1+"\t");
				System.out.print(timeTable[i][j].getname()+"\t");
			}
			System.out.print("\n");
		}
	}
}
