/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package socketjserver;

/**
 *
 * @author owner
 */
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author owner
 */
public class SocketJServer extends Thread {

    private ServerSocket serverSocket;

    public SocketJServer(int port) throws IOException {
        int backlog = 1;
        InetAddress bindAddr = InetAddress.getLoopbackAddress();
        System.out.println("SocketJServer bindAddr = " + bindAddr.toString());
        serverSocket = new ServerSocket(port, backlog, bindAddr);
        serverSocket.setSoTimeout(100000);

    }

    public void run() {
        while (true) {

            try {
                System.out.println("SERVER: Waiting for client on port "
                        + serverSocket.getLocalPort() + "...");
                Socket client = serverSocket.accept();
                System.out.println("SERVER: connected to " + client.getRemoteSocketAddress());
                DataInputStream in = new DataInputStream(client.getInputStream());
                DataOutputStream out = new DataOutputStream(client.getOutputStream());

                int nbytes = 1024;
                byte[] ibytes = new byte[nbytes];

                try {
                    while ((nbytes = in.read(ibytes, 0, ibytes.length)) != -1) {

                        System.out.println("SERVER: read nbytes = " + nbytes);
                        String imsg = new String(ibytes, 0, nbytes);
                        System.out.println("SERVER: received message -> " + imsg);

                        String omsg = "Processed: " + imsg;
                        byte[] obytes = omsg.getBytes();
                        out.write(obytes, 0, obytes.length);
                        System.out.println("SERVER: sent nbytes = " + obytes.length);
                        System.out.println("SERVER: sent messgage -> " + omsg);

                    }
                } catch (IOException ex) {
                    System.out.println("SERVER: client closed connection.");
                    client.close();
                }

            } catch (IOException ex) {
                Logger.getLogger(SocketJServer.class.getName()).log(Level.SEVERE, null, ex);
                System.exit(0);
            }

        }
    }

    public static void main(String[] args) {
        int port = 8080;

        Thread t;
        try {
            t = new SocketJServer(port);
            t.start();

        } catch (IOException ex) {
            Logger.getLogger(SocketJServer.class
                    .getName()).log(Level.SEVERE, null, ex);
        }

    }
}
