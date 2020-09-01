//음수 값을 입력하면 발생하는 exception
public class NegativeException extends Exception {
	public NegativeException() {
		super("work time must be positive");
	}
	public NegativeException(String s) {
		super(s);
	}
}
