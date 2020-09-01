import java.util.Scanner;
import java.io.PrintWriter;
import java.io.FileOutputStream;
import java.io.FileNotFoundException;

public class Program {

	public static void main(String[] args) throws EmptyException {
		// TODO Auto-generated method stub
		Scanner input = new Scanner(System.in);
		PrintWriter outputStream = null;
		DictionaryArray da = new DictionaryArray();
		while (true) {
			System.out.print("===========Main Menu==========\n(1) Add a word to dictionary\n"
					+ "(2) Show definition of word\n(3) Show word list\n"
					+ "(4) Remove word\n(5) print all contents\n(6) Exit Program\n=============================\nchoose a menu : ");
			int num = input.nextInt();
			switch(num){
		       case 1 : 
		           try {
		        	   System.out.println("word : ");
		        	   String in_word = input.next();
		        	   System.out.println("definition : ");
		        	   String in_definition = input.next();
		        	   da.insertEntry(in_word, in_definition);
		           }
		           catch(AlreadyExistInDicException e) {
		        	   System.out.println(e.getMessage());
		           }
		           break;
		       case 2 : 
		           try {
		        	   System.out.println("word for searching : ");
		        	   String in_word = input.next();
		        	   da.getDefinition(in_word);
		           }
		           catch(EmptyException e) {
		        	   System.out.println(e.getMessage());
		           }
		           catch(NotInDicException e) {
		        	   System.out.println(e.getMessage());
		           }
		           break;
		       case 3 :
		    	   try {
		    		   da.printWords();
		    	   }
		    	   catch(EmptyException e) {
		    		  System.out.println(e.getMessage());
		    	   }
		    	   break;
		       case 4 : 
		    	   try {
		    		   System.out.println("word to remove : ");
		    		   String in_word = input.next();
		    		   da.removeWord(in_word);
		    	   }
		    	   catch(EmptyException e) {
		    		  System.out.println(e.getMessage());
		    	   }
		    	   catch(NotInDicException e) {
		    		  System.out.println(e.getMessage());
		    	   }
		    	   break;
		       case 5:
		    	   try {
		    		   da.printAll();
		    	   }
		    	   catch(EmptyException e) {
		    		   System.out.println(e.getMessage());
		    	   }
		    	   break;
		       case 6:
		    	   try {
		    		   System.out.println("Enter a file name : ");
		    		   String st = input.next();
		    		   outputStream = new PrintWriter(new FileOutputStream(st));
		    		   for (int i=0;i<da.getDicList().size();i++) {
		    			   outputStream.println((i+1)+". word : "+da.getDicList().get(i).getword());
		    			   outputStream.println("   definition : "+ da.getDicList().get(i).getdefinition());
		    		   }
		    		   System.out.println("saved as "+st+".txt");
		    		   System.out.println("exit program");
		    		   outputStream.close();
		    	   }
		    	   catch(FileNotFoundException e) {
		    		   System.out.println(e.getMessage());
		    	   }
		    	   System.exit(0);
		    	   break;
		    
			default : System.out.println("Insert 1 ~ 6");
			}
		}
	}
}
