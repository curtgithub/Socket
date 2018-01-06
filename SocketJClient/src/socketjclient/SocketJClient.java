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

      Logger logger = Logger.getLogger("SocketJClient");

      String serverName = "localhost";
      int port = 8080;
      Socket server = null;

      String msg = "Connecting to " + serverName + " on port " + port;
      logger.log(Level.INFO, msg);

      try {
         server = new Socket(serverName, port);
      } catch (IOException ex) {
         msg = "Server is not running!";
         logger.log(Level.SEVERE, msg);
         System.exit(-1);
      }

      int nbytes = 1024;
      byte[] ibytes = new byte[nbytes];

      try {

         msg = "Connected to server: " + server.getRemoteSocketAddress();
         logger.log(Level.INFO, msg);
         msg = "Server = " + server.toString();
         logger.log(Level.INFO, msg);

         InputStream inFromServer = server.getInputStream();
         DataInputStream in = new DataInputStream(inFromServer);
         OutputStream outToServer = server.getOutputStream();
         DataOutputStream out = new DataOutputStream(outToServer);

         for (int i = 0; i < 10; i++) {

            String omsg = "Requst #" + (i + 1);
            byte[] obytes = omsg.getBytes();
            out.write(obytes, 0, obytes.length);
            msg = "Sent to server -> " + omsg;
            logger.log(Level.INFO, msg);

            nbytes = in.read(ibytes, 0, ibytes.length);
            msg = "Read nbytes = " + nbytes;
            logger.log(Level.INFO, msg);
            String imsg = new String(ibytes, 0, nbytes);
            imsg = imsg + "\n";
            msg = "Received message -> " + imsg;
            logger.log(Level.INFO, msg);

         }

         server.close();
      } catch (IOException ex) {
         Logger.getLogger(SocketJClient.class.getName()).log(Level.SEVERE, null, ex);
      }
   }
}
