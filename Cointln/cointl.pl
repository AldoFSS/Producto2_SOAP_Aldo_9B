use Mojolicious::Lite;
use Lingua::EN::Numbers qw(num2en);
use Mojo::UserAgent;

my $ua = Mojo::UserAgent->new;

get '/' => sub {

    my $c = shift;

    my $numero = $c->param('n') || 0;

    # Convertir número a inglés
    my $ingles = num2en($numero);

    # Traducir inglés → español usando API pública
    my $url =
    "https://api.mymemory.translated.net/get?q=$ingles&langpair=en|es";

    my $res = $ua->get($url)->result;

    if($res->is_success){

        my $json = $res->json;

        my $espanol =
        $json->{responseData}->{translatedText};

        $c->render(
            text=>$espanol
        );
    }
    else{

        $c->render(
            text=>"Error al traducir",
            status=>500
        );
    }

};

app->start;