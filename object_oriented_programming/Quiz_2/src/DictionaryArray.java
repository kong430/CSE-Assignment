import java.util.ArrayList;

public class DictionaryArray implements Dictionary{
	private ArrayList<WordDefinitionPair> DicList;
	public DictionaryArray() {
		DicList = new ArrayList<WordDefinitionPair>();
	}
	public ArrayList<WordDefinitionPair> getDicList() {
		return DicList;
	}
	public boolean isEmpty() {
		if (DicList.isEmpty()) return true;
		else return false;
	}
	public void insertEntry(String word, String definition) throws AlreadyExistInDicException {
		int tmp = 0;
		for (int i=0;i<DicList.size();i++) {
			if(word.equals(DicList.get(i).getword())) {
				tmp++;
				break;
			}
		}
		if (tmp==0) DicList.add(new WordDefinitionPair(word, definition));
		else throw new AlreadyExistInDicException();
	}
	
	public void getDefinition(String word) throws EmptyException, NotInDicException {
		int tmp = 0;
		int i;
		for (i=0;i<DicList.size();i++) {
			if(word.equals(DicList.get(i).getword())){
				tmp++;
				break;
			}
		}
		if (DicList.isEmpty()) throw new EmptyException();
		else if (tmp==0) throw new NotInDicException();
		else if (tmp==1) System.out.println(word + " mean : " +DicList.get(i).getdefinition());
	}
	
	public void removeWord(String word) throws NotInDicException, EmptyException{
		int tmp =0;
		int i;
		for (i=0;i<DicList.size();i++) {
			if (word.equals(DicList.get(i).getword())){
				tmp++;
				break;
			}
		}
		if (DicList.isEmpty()) throw new EmptyException();
		else if (tmp==0) throw new NotInDicException();
		else if (tmp==1) DicList.remove(i);
	}
	
	public void printWords() throws EmptyException {
		if (DicList.isEmpty()) throw new EmptyException();
		else {
			for (int i=0;i<DicList.size();i++)
				System.out.println((i+1)+". "+DicList.get(i).getword());
		}
	}
	public void printAll() throws EmptyException {
		if (DicList.isEmpty()) throw new EmptyException();
		else {
			for (int i=0;i<DicList.size();i++) {
				System.out.println("*********************************");
				System.out.println("Word : "+DicList.get((i)).getword());
				System.out.println("Definition : "+DicList.get((i)).getdefinition());
			}
		}
	}
}
