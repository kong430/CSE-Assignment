import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.net.Socket;
import java.util.ArrayList;

public class Download extends Thread{
	public static final int BUFFER_SIZE = 10240;
	public FFile file;
	public String ip;
	int port;
	int cnt=0;
	
	public Download(String IP, int Port, FFile ff) {
		ip = IP;
		port = Port;
		file = ff;
	}

	public void run() {
		while(true)
			try {
				Socket server = new Socket(ip, port);
				System.out.println("Download: connected with"+ip+", "+port);
			    
				DataInputStream dis = null;
				DataOutputStream dos = null;
				
				ArrayList<Integer> bitMap= file.getBitMap();
			    ArrayList<Integer> serverBitMap = new ArrayList<Integer>();
			    dis = new DataInputStream(server.getInputStream());
				dos = new DataOutputStream(server.getOutputStream());
			    
			    String st = dis.readUTF();
			    if(st.equals("BitMap from Uploader")){
			        while (true) {
			            int num = dis.readInt();
			            if (num == 0) break;
			            serverBitMap.add(num);
			        }
			    }
			    
			    cnt=0;
			    for (int i = 0; i < serverBitMap.size();i++) {
			    	if (cnt==3) break;
			    	int num = serverBitMap.get(i);
			        if (bitMap.contains(num)==false) {
			        	//uploader에게 특정 chunk 요청
			            dos.writeInt(num);
			            byte[] buffer = new byte[BUFFER_SIZE];
			            dis.read(buffer);
			            file.writeChunk(num, buffer);
			            System.out.println("Download: download chunk_num " + num);
			            cnt++;
			        }
			    }
			    dos.writeInt(0);
			    
			    if(cnt==0){
			        System.out.println("Download: No chunk Downloaded");
			    }
			
			    dis.close();
			    dos.close();
			    server.close();
			}catch(Exception e) {
				e.printStackTrace();
			}
	}
}