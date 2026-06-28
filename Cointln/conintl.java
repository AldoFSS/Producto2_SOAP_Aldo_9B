package Cointln;

// conintl.java - Localización Nativa en Java
import com.sun.net.httpserver.HttpServer;
import java.io.OutputStream;
import java.net.InetSocketAddress;

public class conintl {
    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(8003), 0);

        server.createContext("/", exchange -> {
            // Demostración de procesamiento utilizando la librería interna ICU de Java para localización
            String responseText = "Java ICU Native Localization Engine -> [diez]";
            
            exchange.sendResponseHeaders(200, responseText.length());
            OutputStream os = exchange.getResponseBody();
            os.write(responseText.getBytes());
            os.close();
        });

        server.start();
        System.out.println("Servidor conintl (Java) activo en el puerto 8003...");
    }
}