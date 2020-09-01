import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;

public class Upload extends Thread {
	public ServerSocket server;
	public FFile file;
	
	public Upload(ServerSocket ser, FFile ff) {
		server = ser;
		file = ff;
	}
	
	public void run() {
		while (true) {
			Socket socket = null;
			DataInputStream dis = null;
			DataOutputStream dos = null;
			
			try {			
				socket = server.accept();
				System.out.println("Upload: Connected to "+socket.getInetAddress()+" ,"+socket.getPort());
				
				ArrayList<Integer> bitMap = file.getBitMap();
			
				dis = new DataInputStream(socket.getInputStream());
				dos = new DataOutputStream(socket.getOutputStream());
				
				//BitMap 전송 시작
				dos.writeUTF("BitMap from Uploader");
				for (int i = 0; i < bitMap.size();i++) {
                   dos.write(bitMap.get(i));
				}
				//BitMap 전송 끝
	            dos.write(0);
	            
	            //Upload 시작
	            int cnt = 0;
                while(true){
                	//요청받은 chunk_num 읽어옴
                    int num = dis.readInt();
                    if(num == 0) break;
                    dos.write(file.readChunk(num));
                    cnt++;
                    System.out.println("Upload: Send chunk "+num);
                }
                //upload 끝
                dos.write(0);
                
                if(cnt==0){
                    System.out.println("Upload: No chunk to Upload");
                }

                dis.close();
                dos.close();
			}catch(Exception e) {
				e.printStackTrace();
			}
		}
	}
}