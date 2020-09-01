public class Subject {
	private String name;
	private String tutor;
	private String room;
	
	public Subject(String name, String tutor, String room) {
		this.name = name;
		this.tutor = tutor;
		this.room = room;
	}
	public Subject(String name) {
		this.name = name;
	}
	public Subject(Subject sj) {
		this.name = sj.name;
		this.tutor = sj.tutor;
		this.room = sj.room;
	}
	public String getname() {
		return this.name;
	}
	public String gettutor() {
		return this.tutor;
	}
	public String getroom() { 
		return this.room;
	}
	public void settutor(String tutor) {
		this.tutor = tutor;
	}
	public void setroom(String room) {
		this.room = room;
	}
	public boolean equals(Subject sj) {
		if (this.getname() == sj.getname()) return true;
		else return false;
	}
	public String toString() {
		return this.name;
	}
	public String getDetails() {
		return ("Name : " + this.name+"\nTutor : "+ this.tutor
				+"\nRoom : "+this.room);
	}
}
