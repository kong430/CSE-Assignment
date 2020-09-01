import java.io.BufferedReader;
import java.io.FileReader;
import java.net.ServerSocket;
import java.util.Random;

public class Leecher1 {
    private static Upload upload;
    private static Download download;

    public static void main(String[] args){
    	try {
			BufferedReader br = new BufferedReader(new FileReader("configuration.txt"));
			String thisCon = null;
			String thisFile = "copy-1";
			String[] ip = new String[5];
			int[] port = new int[5];
			int thisPort = 0;
			
			for(int i = 0; i < 5; i++){
				thisCon = br.readLine();
				if (i==1) {
					thisPort = Integer.parseInt(thisCon.split(" ")[1]);
				}
				ip[i] = thisCon.split(" ")[0];
				port[i] = Integer.parseInt(thisCon.split(" ")[1]);
			}
		ServerSocket server = new ServerSocket(thisPort);
		    
		Random rand = new Random();
		int random = rand.nextInt(4)+1;
		
		FFile file = new FFile(thisFile);
		
		upload = new Upload(server, file);
		download = new Download(ip[random], port[random], file);
		  
		upload.start();
		download.start();
		
    	}catch(Exception e) {
    		e.printStackTrace();
    	}
    }
}