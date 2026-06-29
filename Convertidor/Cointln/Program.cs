using Humanizer;

var builder=WebApplication.CreateBuilder(args);

var app=builder.Build();

app.MapGet("/",(HttpRequest request)=>{

int numero=
int.Parse(
request.Query["n"]
);

var resultado=
numero.ToWords(
new System.Globalization.CultureInfo(
"es"
)
);

return resultado;

});

app.Run();