using System.ServiceModel;

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

    var resultado =
        await cliente.NumberToWordsAsync(
            ulong.Parse(numero)
        );

    return resultado;
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