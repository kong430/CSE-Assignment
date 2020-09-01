import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.net.*;

public class Server {
	public static final int BUFFER_SIZE = 10240;
	public static void main(String[] args) {
		int port = Integer.parseInt(args[0]);
		
		BufferedInputStream bis = null;
		Socket socket = null;
		ServerSocket server = null;
		DataInputStream dis = null;
		DataOutputStream dos = null;
		String file_name = null;
		File file = null;

		try {			
			server = new ServerSocket(port);
			
			System.out.println("This is port num "+port+", "+"ready to connected");
			socket = server.accept();
			System.out.println("Client Accepted");
			
			dis = new DataInputStream(socket.getInputStream());
			dos = new DataOutputStream(socket.getOutputStream());
			
			file_name = dis.readUTF();
			file = new File(file_name);
			
			if (!file.exists()) {
				System.out.println("File ["+file_name+"] not Exist");
				dos.write(0);
				System.exit(0);
			}
			else dos.write(1);
			System.out.println("File ["+file_name +"] ready for transmission");
			
			long fileSize = file.length();
			int totalChunk = (int)fileSize/BUFFER_SIZE;
			int lastBytes = (int)fileSize%BUFFER_SIZE;
			long readBytes=0;
			long totalTransmitted_Bytes = 0;
			byte[] buffer = new byte[BUFFER_SIZE];
			long completeBytes;
			
			System.out.println("File size of ["+file_name+"] is "+fileSize);
			System.out.println("Total "+totalChunk+" 10KB chuncks and one "+ lastBytes+" bytes chunk");
			
			dos.writeLong(fileSize);
			bis = new BufferedInputStream(new FileInputStream(file));
			
			for (int i=0;i<totalChunk;i++) {
				if ((readBytes=bis.read(buffer, 0, BUFFER_SIZE))!=-1){
					dos.write(buffer, 0, (int)readBytes);
					totalTransmitted_Bytes += readBytes;
					System.out.println("In progress... "+ totalTransmitted_Bytes*100/fileSize + "% transmitted (total "+totalTransmitted_Bytes+" bytes)");
				}
			}
			
			if (lastBytes>0) {
				if ((readBytes = bis.read(buffer, 0, lastBytes))!=-1) {
					dos.write(buffer, 0, (int)readBytes);
					totalTransmitted_Bytes += readBytes;
					System.out.println("In progress... "+ totalTransmitted_Bytes*100/fileSize + "% transmitted (total "+totalTransmitted_Bytes+" bytes)");
				}
			}
			
			System.out.println("File transmission completed");
			completeBytes = dis.readLong();
			System.out.println("Client successfully received "+completeBytes+" bytes of file");
		}catch(Exception e) {
			e.printStackTrace();
		}
		finally {
			try {
			if (bis!=null) bis.close();
			if (dos!=null) dos.close();
			if (dis!=null) dis.close();
			}catch(Exception e) {
				e.printStackTrace();
			}
		}
		
	}

}
