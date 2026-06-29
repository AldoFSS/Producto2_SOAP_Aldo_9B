<?php
// Inclusión automática de las librerías descargadas por Composer
require_once "../vendor/autoload.php";
use Stichoza\GoogleTranslate\GoogleTranslate;

$wsdl = "https://www.dataaccess.com/webservicesserver/NumberConversion.wso?WSDL";
$cliente = new SoapClient($wsdl);

$respuesta = $cliente->NumberToWords(array("ubiNum" => $_GET['n']));

// Instanciación del traductor configurando idioma origen (inglés) e idioma destino (español)
$traductor = new GoogleTranslate('es', 'en');
$res = $traductor->translate($respuesta->NumberToWordsResult);

echo $res;
?>