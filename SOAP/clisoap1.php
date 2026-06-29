<?php
// Definición del archivo descriptor del servicio web remoto
$wsdl = "https://www.dataaccess.com/webservicesserver/NumberConversion.wso?WSDL";

// Creación del cliente SOAP nativo usando la extensión previamente activada
$cliente = new SoapClient($wsdl);

// Ejecución de la función remota enviando el parámetro 'n' capturado de la URL
$respuesta = $cliente->NumberToWords(array("ubiNum" => $_GET['n']));

// Impresión del resultado directo (el número traducido al idioma inglés por defecto)
echo $respuesta->NumberToWordsResult;
?>