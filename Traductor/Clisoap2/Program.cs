using System.ServiceModel;
using System.Text.Json;

var builder = WebApplication.CreateBuilder(args);
var app = builder.Build();

app.MapGet("/", async (HttpRequest request) =>
{
    var numero = request.Query["n"].ToString();

    var binding = new BasicHttpsBinding();

    var endpoint = new EndpointAddress(
        "https://www.dataaccess.com/webservicesserver/NumberConversion.wso"
    );

    var factory = new ChannelFactory<INumberConversion>(
        binding,
        endpoint
    );

    var cliente = factory.CreateChannel();

    // SOAP → inglés
    var ingles = await cliente.NumberToWordsAsync(
        ulong.Parse(numero)
    );

    // Traducir usando API pública
    var http = new HttpClient();

    var url =
    $"https://api.mymemory.translated.net/get?q={Uri.EscapeDataString(ingles)}&langpair=en|es";

    var response = await http.GetStringAsync(url);

    using JsonDocument json =
    JsonDocument.Parse(response);

    var español =
    json.RootElement
        .GetProperty("responseData")
        .GetProperty("translatedText")
        .GetString();

    return español;
});

app.Run();

[ServiceContract(
    Namespace="http://www.dataaccess.com/webservicesserver/"
)]
public interface INumberConversion
{
    [OperationContract(
        Action="http://www.dataaccess.com/webservicesserver/NumberToWords",
        ReplyAction="*"
    )]
    Task<string> NumberToWordsAsync(
        ulong ubiNum
    );
}