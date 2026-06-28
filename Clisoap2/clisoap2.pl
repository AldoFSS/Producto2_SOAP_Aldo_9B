#!/usr/bin/perl
use strict;
use warnings;
use CGI;
use SOAP::Lite;
use LWP::UserAgent;
use JSON;
use URI::Escape;

my $q = CGI->new;
print $q->header(-type => 'text/plain', -charset => 'utf-8');

my $numero = $q->param('n') // 0;
my $wsdl = 'https://www.dataaccess.com/webservicesserver/NumberConversion.wso?WSDL';

eval {
    # 1. Obtener número en inglés vía SOAP
    my $soap = SOAP::Lite->service($wsdl);
    my $texto_ingles = $soap->NumberToWords($numero);
    $texto_ingles =~ s/^\s+|\s+$//g; # Limpiar espacios

    # 2. Conectar con la API de traducción externa
    my $ua = LWP::UserAgent->new;
    my $url_trad = "https://translate.googleapis.com/translate_a/single?client=gtx&sl=en&tl=es&dt=t&q=" . uri_escape($texto_ingles);
    
    my $respuesta = $ua->get($url_trad);
    
    if ($respuesta->is_success) {
        my $datos = decode_json($respuesta->decoded_content);
        my $texto_espanol = $datos->[0]->[0]->[0];
        print $texto_espanol;
    } else {
        print $texto_ingles . " (No se pudo traducir)";
    }
};
if ($@) {
    print "Error en el proceso: $@";
}