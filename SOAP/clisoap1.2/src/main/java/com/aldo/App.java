package com.aldo;

import static spark.Spark.*;
import java.io.*;
import java.net.*;
import java.nio.charset.StandardCharsets;

public class App {

    public static void main(String[] args){

        port(8001);

        get("/", (req,res)->{

            String numero=req.queryParams("n");

            String xml =
            "<?xml version=\"1.0\" encoding=\"utf-8\"?>" +
            "<soap:Envelope xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\">" +
            "<soap:Body>" +
            "<NumberToWords xmlns=\"http://www.dataaccess.com/webservicesserver/\">" +
            "<ubiNum>"+numero+"</ubiNum>" +
            "</NumberToWords>" +
            "</soap:Body>" +
            "</soap:Envelope>";

            URL url = new URL(
            "https://www.dataaccess.com/webservicesserver/NumberConversion.wso"
            );

            HttpURLConnection con =
            (HttpURLConnection)url.openConnection();

            con.setRequestMethod("POST");
            con.setRequestProperty(
            "Content-Type",
            "text/xml;charset=UTF-8"
            );

            con.setDoOutput(true);

            OutputStream os=con.getOutputStream();
            os.write(xml.getBytes(StandardCharsets.UTF_8));
            os.close();

            BufferedReader br=
            new BufferedReader(
            new InputStreamReader(
            con.getInputStream()
            ));

            String linea;
            String respuesta="";

            while((linea=br.readLine())!=null){
                respuesta+=linea;
            }

            br.close();

            int inicio=
            respuesta.indexOf(
            "<m:NumberToWordsResult>"
            );

            int fin=
            respuesta.indexOf(
            "</m:NumberToWordsResult>"
            );

            return respuesta.substring(
            inicio+25,
            fin
            );

        });

        System.out.println("Servidor puerto 8001");
    }
}