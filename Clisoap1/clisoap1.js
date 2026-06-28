// clieSoap1.js - Cliente SOAP Puro en Node.js
const express = require('express');
const soap = require('soap');
const app = express();

const urlWsdl = "https://www.dataaccess.com/webservicesserver/NumberConversion.wso?WSDL";

app.get('/', (req, res) => {
    // Captura el parámetro 'n' de la URL (ej: /?n=10)
    const numero = req.query.n || 0;

    // Conexión con el cliente SOAP externo
    soap.createClient(urlWsdl, (err, client) => {
        if (err) return res.status(500).send("Error al conectar con el servicio SOAP");

        // Ejecución de la función remota
        client.NumberToWords({ ubiNum: numero }, (err, result) => {
            if (err) return res.status(500).send("Error en la conversión SOAP");
            
            // Envía la respuesta en inglés al navegador
            res.send(result.NumberToWordsResult);
        });
    });
});

app.listen(8001, () => console.log("Servidor clieSoap1 (Node.js) activo en http://localhost:8001"));