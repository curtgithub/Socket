package socketjclient;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author owner
 */
public class SocketJClient {

    public static void main(String[] args) {
        String serverName = "localhost";
        int port = 8080;
        Socket server = null;
        System.out.println("Connecting to " + serverName + " on port " + port);

        try {
            server = new Socket(serverName, port);
        } catch (IOException ex) {
            System.out.println("CLIENT server is not running!");
            System.exit(-1);
        }

        int nbytes = 1024;
        byte[] ibytes = new byte[nbytes];
       
        try {

            System.out.println("CLIENT Connected to server: " + server.getRemoteSocketAddress());
            System.out.println("CLIENT server = " + server.toString());

            InputStream inFromServer = server.getInputStream();
            DataInputStream in = new DataInputStream(inFromServer);
            OutputStream outToServer = server.getOutputStream();
            DataOutputStream out = new DataOutputStream(outToServer);
            
            for (int i = 0; i < 10; i++) {
                
                String omsg = "Requst #" + (i + 1);
                byte[] obytes = omsg.getBytes();
                out.write(obytes, 0, obytes.length);
                System.out.println("CLIENT sent to server -> " + omsg);
                
                nbytes = in.read(ibytes, 0, ibytes.length);
                System.out.println("CLIENT: read nbytes = " + nbytes);
                String imsg = new String(ibytes, 0, nbytes);
                imsg = imsg + "\n";
                System.out.println("CLIENT: received message -> " + imsg);
                
            }

            server.close();
        } catch (IOException ex) {
            Logger.getLogger(SocketJClient.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
