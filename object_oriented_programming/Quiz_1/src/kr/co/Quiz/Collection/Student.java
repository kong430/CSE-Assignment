package kr.co.Quiz.Collection;
import java.util.Random;

public class Student {
	private String name;
	private int StudentNumber;
	private int Korean;
	private int Math;
	private int English;
	private double Avg;
	
	public Student(String name, int Korean, int Math, int English) {
		this.name = name;
		this.Korean = Korean;
		this.Math = Math;
		this.English = English;
		Random rnd = new Random();
		int num = rnd.nextInt(9999)+1;
		StudentNumber = 2018000000+num;
		Avg = (Korean+Math+English)/3.0;
	}
	
	public Student(Student st) {
		name = st.name;
		StudentNumber = st.StudentNumber;
		Korean = st.Korean;
		Math = st.Math;
		English = st.English;
		Avg = st.Avg;
	}
	
	public static void makeRank(Student[] StudentList) {
		Student tmp;
		int n= StudentList.length;
		for (int i=n-1;i>0;i--) {
			for (int j=0;j<i;j++) {
				if (StudentList[j].StudentNumber>StudentList[j+1].StudentNumber) {
					tmp = StudentList[j];
					StudentList[j] = StudentList[j+1];
					StudentList[j+1] = tmp;
				}
			}
		}
	}
	
	int score;
	public String Grade(int score) {
		if (score>=90) return "A";
		else if (80<=score && score<90) return "B";
		else if (70<=score && score<80) return "C";
		else if (60<=score && score<70) return "D";
		else return "F";
	}
	
	public String toString() {
		return "이름 : "+name+" 학번 : "+ StudentNumber+"\n"+"국어 : "+Grade(Korean)
				+" 수학 : "+Grade(Math)+" 영어 : "+Grade(English)+"\n평균 : "+Avg ;
	}
	
	
}