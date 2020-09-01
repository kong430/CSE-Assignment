//24를 초과하는 숫자를 입력하면 발생하는 exception
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
