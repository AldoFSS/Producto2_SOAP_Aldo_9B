
import com.sun.net.httpserver.HttpServer;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.HashMap;
import java.util.Map;

public class clieSoap1 {
    public static void main(String[] args) throws Exception {
        // Inicializa un servidor HTTP nativo en el puerto 8001
        HttpServer server = HttpServer.create(new InetSocketAddress(8001), 0);

        server.createContext("/", exchange -> {
            Map<String, String> params = queryToMap(exchange.getRequestURI().getQuery());
            String numero = params.getOrDefault("n", "0");

            // En un ambiente real, aquí se invocaría la clase stub generada por 'wsimport'
            // Simulamos la lógica del llamado síncrono al servicio SOAP de DataAccess
            String responseText = "Invocando Stub SOAP de Java para el numero: " + numero + " -> [Resultado Remoto: ten]";
            
            exchange.sendResponseHeaders(200, responseText.length());
            OutputStream os = exchange.getResponseBody();
            os.write(responseText.getBytes());
            os.close();
        });

        server.start();
        System.out.println("Servidor clieSoap1 (Java) activo en el puerto 8001...");
    }

    private static Map<String, String> queryToMap(String query) {
        Map<String, String> result = new HashMap<>();
        if (query == null) return result;
        for (String param : query.split("&")) {
            String[] entry = param.split("=");
            if (entry.length > 1) result.put(entry[0], entry[1]);
        }
        return result;
    }
}