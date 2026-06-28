// clieSoap1.cs - Cliente SOAP Puro en .NET 10
var builder = WebApplication.CreateBuilder(args);
var app = builder.Build();

app.MapGet("/", async (HttpContext context) => {
    // Captura el parámetro 'n' de la URL query string
    string n = context.Request.Query["n"] ?? "0";

    try {
        // Inicialización del cliente SOAP autogenerado por la referencia de servicio
        var client = new ServiceReference1.NumberConversionSoapTypeClient(
            ServiceReference1.NumberConversionSoapTypeClient.EndpointConfiguration.NumberConversionSoap
        );

        // Llamado asíncrono enviando el número convertido a ulong
        var response = await client.NumberToWordsAsync(ulong.Parse(n));
        
        // Retorna el string del resultado en inglés
        return response.Body.NumberToWordsResult;
    }
    catch (Exception ex) {
        return $"Error en la llamada SOAP .NET: {ex.Message}";
    }
});

app.Run("http://localhost:8001");