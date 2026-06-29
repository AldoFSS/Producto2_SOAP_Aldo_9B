use Mojolicious::Lite;
use SOAP::Lite;
use Mojo::UserAgent;
use JSON qw(decode_json);

my $cliente = SOAP::Lite
->service(
'http://www.dataaccess.com/webservicesserver/NumberConversion.wso?WSDL'
);

my $ua = Mojo::UserAgent->new;

get '/' => sub {

    my $c = shift;

    my $numero = $c->param('n') || 0;

    my $ingles = eval {
        $cliente->NumberToWords($numero);
    };

    if($@){
        $c->render(
            text=>"Error SOAP: $@",
            status=>500
        );
        return;
    }

    my $url =
    "https://api.mymemory.translated.net/get?q=$ingles&langpair=en|es";

    my $res = $ua->get($url)->result;

    if($res->is_success){

        my $json = $res->json;

        my $espanol =
        $json->{responseData}->{translatedText};

        $c->render(text=>$espanol);
    }
    else{

        $c->render(
            text=>"Error traduciendo",
            status=>500
        );
    }
};

app->start;