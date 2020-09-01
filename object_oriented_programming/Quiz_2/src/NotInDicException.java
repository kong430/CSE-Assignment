
public class NotInDicException extends Exception{
	public NotInDicException() {
		super("this word not exists in dictionary");
	}
	public NotInDicException(String e) {
		super(e);
	}
}
