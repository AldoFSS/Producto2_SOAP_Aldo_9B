<?php
// Instanciación del formateador regional configurando idioma español ('es') y modo deletreo
$formateador = new NumberFormatter("es", NumberFormatter::SPELLOUT);

// Procesamiento directo del número enviado desde los parámetros GET de la URL
$res = $formateador->format($_GET['n']);
echo $res;
?>