//24�� �ʰ��ϴ� ���ڸ� �Է��ϸ� �߻��ϴ� exception
public class TooMuchStuffException extends Exception{
	private int inputNum;
	public TooMuchStuffException() {
		super("Too much stuff!");
	}
	public TooMuchStuffException(int inputNum) {
		super("Too much stuff!");
		this.inputNum = inputNum;
	}
	public int getinputNum() {
		return inputNum;
	}
}
