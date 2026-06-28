// clieSoap2.js - Cliente SOAP + Traducción en Node.js
const express = require('express');
const soap = require('soap');
const axios = require('axios');
const app = express();

const urlWsdl = "https://www.dataaccess.com/webservicesserver/NumberConversion.wso?WSDL";

app.get('/', (req, res) => {
    const numero = req.query.n || 0;

    soap.createClient(urlWsdl, (err, client) => {
        if (err) return res.status(500).send("Error SOAP");

        client.NumberToWords({ ubiNum: numero }, async (err, result) => {
            if (err) return res.status(500).send("Error en conversión");
            
            const textoIngles = result.NumberToWordsResult;

            try {
                // Consumo asíncrono con Axios de la API de traducción
                const urlTrad = `https://translate.googleapis.com/translate_a/single?client=gtx&sl=en&tl=es&dt=t&q=${encodeURIComponent(textoIngles)}`;
                const resTrad = await axios.get(urlTrad);
                const textoEspanol = resTrad.data[0][0][0];
                res.send(textoEspanol);
            } catch (error) {
                res.send(textoIngles + " (No se pudo traducir)");
            }
        });
    });
});

app.listen(8002, () => console.log("Servidor clieSoap2 (Node.js) activo en http://localhost:8002"));