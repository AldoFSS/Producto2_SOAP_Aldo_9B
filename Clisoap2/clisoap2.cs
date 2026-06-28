// clieSoap2.cs - Cliente SOAP + Traducción en .NET 10
using System.Text.Json;

var builder = WebApplication.CreateBuilder(args);
var app = builder.Build();

app.MapGet("/", async (HttpContext context) => {
    string n = context.Request.Query["n"] ?? "0";

    try {
        var client = new ServiceReference1.NumberConversionSoapTypeClient(
            ServiceReference1.NumberConversionSoapTypeClient.EndpointConfiguration.NumberConversionSoap
        );
        var response = await client.NumberToWordsAsync(ulong.Parse(n));
        string textoIngles = response.Body.NumberToWordsResult;

        // Consumo manual de traducción síncrona/asíncrona vía HTTP
        using var httpClient = new HttpClient();
        string urlTrad = $"https://translate.googleapis.com/translate_a/single?client=gtx&sl=en&tl=es&dt=t&q={Uri.EscapeDataString(textoIngles)}";
        var resTrad = await httpClient.GetStringAsync(urlTrad);
        
        using var doc = JsonDocument.Parse(resTrad);
        string textoEspanol = doc.RootElement[0][0][0].GetString() ?? textoIngles;
        
        return textoEspanol;
    }
    catch (Exception ex) {
        return $"Error: {ex.Message}";
    }
});

app.Run("http://localhost:8002");