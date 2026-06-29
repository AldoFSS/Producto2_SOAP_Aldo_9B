package com.aldo;

import static spark.Spark.*;

import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;

public class App {

    public static void main(String[] args) {

        port(8002);

        get("/", (req,res)->{

            String numero=req.queryParams("n");

            HttpClient client=
            HttpClient.newHttpClient();

            // SOAP manual
            String soap=
            """
            <?xml version="1.0" encoding="utf-8"?>
            <soap:Envelope
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xmlns:xsd="http://www.w3.org/2001/XMLSchema"
            xmlns:soap="http://schemas.xmlsoap.org/soap/envelope/">

              <soap:Body>

                <NumberToWords
                xmlns="http://www.dataaccess.com/webservicesserver/">

                  <ubiNum>%s</ubiNum>

                </NumberToWords>

              </soap:Body>

            </soap:Envelope>
            """.formatted(numero);

            HttpRequest soapReq=
            HttpRequest.newBuilder()
            .uri(
                URI.create(
                "https://www.dataaccess.com/webservicesserver/NumberConversion.wso"
                )
            )
            .header(
            "Content-Type",
            "text/xml;charset=UTF-8"
            )
            .POST(
            HttpRequest.BodyPublishers.ofString(
            soap
            ))
            .build();

            HttpResponse<String> soapRes=
            client.send(
            soapReq,
            HttpResponse.BodyHandlers.ofString()
            );

            String xml=soapRes.body();

            // Extraer texto inglés
            String ingles=
            xml.split("<m:NumberToWordsResult>")[1]
               .split("</m:NumberToWordsResult>")[0];

            // Traducir inglés → español
            HttpRequest tradReq=
            HttpRequest.newBuilder()
            .uri(
            URI.create(
            "https://translate.googleapis.com/translate_a/single?client=gtx&sl=en&tl=es&dt=t&q="
            +ingles.replace(" ","%20")
            ))
            .build();

            HttpResponse<String> tradRes=
            client.send(
            tradReq,
            HttpResponse.BodyHandlers.ofString()
            );

            String json=
            tradRes.body();

            String español=
            json.split("\"")[1];

            return español;

        });

        System.out.println(
        "Servidor puerto 8002"
        );

    }
}