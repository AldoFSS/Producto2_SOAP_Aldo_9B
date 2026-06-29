use Mojolicious::Lite;
use SOAP::Lite;

# Crear cliente SOAP una sola vez
my $cliente = SOAP::Lite
->service(
'http://www.dataaccess.com/webservicesserver/NumberConversion.wso?WSDL'
);

get '/' => sub {

    my $c = shift;

    my $numero = $c->param('n') || 0;

    my $resultado = eval {
        $cliente->NumberToWords($numero);
    };

    if($@){
        $c->render(
            text=>"Error SOAP: $@",
            status=>500
        );
        return;
    }

    $c->render(
        text=>$resultado
    );
};

app->start;