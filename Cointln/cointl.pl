#!/usr/bin/perl
use strict;
use warnings;
use CGI;

my $q = CGI->new;
print $q->header(-type => 'text/plain', -charset => 'utf-8');

# Recibir el número desde la URL
my $numero = $q->param('n') // 0;

# Diccionario local para la conversión nativa (Rango básico de prueba)
my @unidades = ('cero', 'uno', 'dos', 'tres', 'cuatro', 'cinco', 'seis', 'siete', 'ocho', 'nueve', 'diez');

if ($numero >= 0 && $numero <= 10) {
    print $unidades[$numero];
} else {
    print "Número fuera de rango para la prueba local en Perl. Intenta del 0 al 10.";
}