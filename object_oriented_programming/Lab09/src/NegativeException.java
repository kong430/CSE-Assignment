//���� ���� �Է��ϸ� �߻��ϴ� exception
public class NegativeException extends Exception {
	public NegativeException() {
		super("work time must be positive");
	}
	public NegativeException(String s) {
		super(s);
	}
}
