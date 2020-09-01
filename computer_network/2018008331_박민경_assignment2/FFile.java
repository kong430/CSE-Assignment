import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.ArrayList;
import java.util.Collections;

public class FFile {
	public static final int BUFFER_SIZE = 10240;
    public RandomAccessFile raf;
    public ArrayList<Integer> bitMap;

    public FFile(String filename){
        try {
			raf = new RandomAccessFile(filename, "rw");
			bitMap = new ArrayList<Integer>();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
    }
    
    public synchronized ArrayList<Integer> getBitMap(){
    	return this.bitMap;
    }

    public synchronized byte[] readChunk(int chunk_num)
    {
    	byte[] buff = new byte[10240];
        try {
        	raf.seek(0);
			raf.seek(10240*chunk_num);
		    raf.read(buff);
        } catch (IOException e) {
			e.printStackTrace();
		}
        return buff;
    }
    
    public synchronized void writeChunk(int chunk_num, byte[] buff)
    {
        if(bitMap.contains(chunk_num)){
            return;
        }
        bitMap.add(chunk_num);
        Collections.sort(bitMap);
       
        try {
        	raf.seek(0);
			raf.seek(10240*chunk_num);
			raf.write(buff);
		} catch (IOException e) {
			e.printStackTrace();
		}
    }
   
    public synchronized void seederChunk(){
    	int cnt = 1;
        byte[] buff = new byte[BUFFER_SIZE];
        try {
			raf.seek(0);
		    while(raf.read(buff)!=-1){
		    bitMap.add(cnt);
		    cnt++;
		    }
		} catch (IOException e) {
			e.printStackTrace();
		}
    }
}
