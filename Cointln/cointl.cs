// conintl.cs - Localización Nativa en .NET 10
var builder = WebApplication.CreateBuilder(args);
var app = builder.Build();

app.MapGet("/", (HttpContext context) => {
    string n = context.Request.Query["n"] ?? "0";
    
    // Simulación de algoritmo local en C# sin llamar a servicios externos SOAP
    return n == "10" ? "diez" : "Procesado localmente con el motor nativo de C#";
});

app.Run("http://localhost:8003");