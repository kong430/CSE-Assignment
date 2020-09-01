
public class WordDefinitionPair {

	private String word;
	private String definition;
	
	public WordDefinitionPair(String word, String definition) {
		this.word = word;
		this.definition = definition;
	}
	
	public String getword() {
		return word;
	}
	
	public String getdefinition() {
		return definition;
	}
	
	public void setword(String word) {
		this.word = word;
	}
	
	public void setdefinition(String definition) {
		this.definition = definition;
	}
}