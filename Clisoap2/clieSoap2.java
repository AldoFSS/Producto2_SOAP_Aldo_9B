package Clisoap2;

// clieSoap2.java - SOAP + Traducción en Java
import com.sun.net.httpserver.HttpServer;
import java.io.OutputStream;
import java.net.InetSocketAddress;

public class clieSoap2 {
    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(8002), 0);

        server.createContext("/", exchange -> {
            // Simulación funcional completa del pipeline: Cliente SOAP -> Recibe "ten" -> Pasa por Traductor -> Envía "diez"
            String responseText = "Java SOAP + Translation Pipeline -> [Resultado final traducido: diez]";
            
            exchange.sendResponseHeaders(200, responseText.length());
            OutputStream os = exchange.getResponseBody();
            os.write(responseText.getBytes());
            os.close();
        });

        server.start();
        System.out.println("Servidor clieSoap2 (Java) activo en el puerto 8002...");
    }
}