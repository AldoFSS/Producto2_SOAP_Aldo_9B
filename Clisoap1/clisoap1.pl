#!/usr/bin/perl
use strict;
use warnings;
use CGI;
use SOAP::Lite;

# Configurar la salida para el navegador web
my $q = CGI->new;
print $q->header(-type => 'text/plain', -charset => 'utf-8');

# Obtener el número desde la URL (ej: ?n=10)
my $numero = $q->param('n') // 0;

my $wsdl = 'https://www.dataaccess.com/webservicesserver/NumberConversion.wso?WSDL';

eval {
    # Consumo del servicio SOAP
    my $soap = SOAP::Lite->service($wsdl);
    my $resultado = $soap->NumberToWords($numero);
    
    print "Resultado SOAP (Inglés): " . $resultado;
};
if ($@) {
    print "Error al conectar con el servicio SOAP: $@";
}