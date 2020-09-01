
public class AlreadyExistInDicException extends Exception {
	public AlreadyExistInDicException() {
		super("this word already exists in dictionary");
	}
	public AlreadyExistInDicException(String e) {
		super(e);
	}
}
