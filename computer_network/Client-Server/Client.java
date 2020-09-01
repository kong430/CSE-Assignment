import java.io.BufferedOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.net.*;

public class Client {
	public static final int BUFFER_SIZE = 10240;
	public static void main(String[] args) {
		String serverIP = args[0];
		int port = Integer.parseInt(args[1]);
		String file_name = args[2];
		
		BufferedOutputStream bos =null;
		DataInputStream dis = null;
		DataOutputStream dos = null;
		long fileSize = 0;
		File copyFile = null;
		
		try {			
			Socket socket = new Socket(serverIP, port);
			dis = new DataInputStream(socket.getInputStream());
			dos = new DataOutputStream(socket.getOutputStream());
			dos.writeUTF(file_name);
			
			if (dis.read()==0) {
				System.out.println("File not exist, exit connection");
				System.exit(0);
			}
			else System.out.println("Ready to receive file ["+ file_name+"]");
			
			copyFile = new File("received_"+file_name);
			bos = new BufferedOutputStream(new FileOutputStream(copyFile,false));
			fileSize = dis.readLong();
			int totalChunks = (int) (fileSize/BUFFER_SIZE);
			int lastBytes = (int) (fileSize%BUFFER_SIZE);
			int readBytes;
			long BytesCnt = 0;
			byte[] buffer = new byte[BUFFER_SIZE];
			
			System.out.println("Received bytes will be stored in ["+copyFile+"]");
			System.out.println("File size of ["+file_name+"] is "+fileSize);
			System.out.println("Total "+totalChunks+" 10KB chunks and one "+ lastBytes+" bytes chunk");	
			
			for (int i=0;i<totalChunks;i++) {
				if ((readBytes = dis.read(buffer, 0, BUFFER_SIZE))!=-1) {
					bos.write(buffer, 0, readBytes);
					BytesCnt+=readBytes;
					System.out.println("In progress... "+ BytesCnt*100/fileSize + "% received (total "+BytesCnt+" bytes)");
					}
			}
			if (lastBytes>0) {
				if ((readBytes=dis.read(buffer, 0, BUFFER_SIZE))!=-1) {
					bos.write(buffer, 0, readBytes);
					BytesCnt+=readBytes;
					System.out.println("In progress... "+ BytesCnt*100/fileSize + "% received (total "+BytesCnt+" bytes)");
					}
			}
			dos.writeLong(BytesCnt);
			System.out.println("Successfully received ["+file_name+"] as file ["+copyFile.getName()+"]");
		}catch(Exception e) {
			e.printStackTrace();
		}
		finally {
			try {
				if (dis!=null) dis.close();
				if (dos!=null) dos.close();
				if (bos!=null) bos.close();
			}catch(Exception e) {
				e.printStackTrace();
			}
		}
	}
}