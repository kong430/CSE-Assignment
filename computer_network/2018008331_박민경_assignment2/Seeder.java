import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.net.ServerSocket;

public class Seeder {
	public static final int BUFFER_SIZE = 10240;
    private static FFile file;
    private static Upload upload;

    public static void main(String args[])throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("configuration.txt"));
        String thisCon = null;
        int thisPort = 0;
        String[] ip = new String[5];
		int[] port = new int[5];

        for (int i = 0; i < 5; i++) {
        	thisCon = br.readLine();
        	if (i==0) {
        		thisPort = Integer.parseInt(thisCon.split(" ")[1]);
        		break;
        	}
			ip[i] = thisCon.split(" ")[0];
			port[i] = Integer.parseInt(thisCon.split(" ")[1]);
        }
        
        String thisfile = "origin-file";
         
        file = new FFile(thisfile);
        byte[] buff = new byte[BUFFER_SIZE];

        file.seederChunk();
       
        ServerSocket server = new ServerSocket(thisPort);
        upload = new Upload(server, file);

        upload.start();
    }

}
