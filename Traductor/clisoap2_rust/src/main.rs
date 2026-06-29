use tiny_http::{Server,Response};
use reqwest::blocking::Client;

fn extraer(texto:&str)->String{

    let inicio_tag=
    "<m:NumberToWordsResult>";

    let fin_tag=
    "</m:NumberToWordsResult>";

    if let Some(inicio)=
    texto.find(inicio_tag){

        let inicio=
        inicio+inicio_tag.len();

        if let Some(fin)=
        texto.find(fin_tag){

            return texto[inicio..fin]
            .trim()
            .to_string();

        }

    }

    String::new()

}

fn main(){

    let server=
    Server::http(
    "0.0.0.0:8002"
    )
    .unwrap();

    println!(
    "Servidor puerto 8002"
    );

    for request in server.incoming_requests(){

        let numero=
        request.url()
        .split("n=")
        .nth(1)
        .unwrap_or("0");

        let xml=format!(r#"<?xml version="1.0" encoding="utf-8"?>

<soap:Envelope
xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
xmlns:xsd="http://www.w3.org/2001/XMLSchema"
xmlns:soap="http://schemas.xmlsoap.org/soap/envelope/">

<soap:Body>

<NumberToWords xmlns="http://www.dataaccess.com/webservicesserver/">

<ubiNum>{}</ubiNum>

</NumberToWords>

</soap:Body>

</soap:Envelope>
"#,numero);

        let cliente=
        Client::new();

        let soap=
        cliente
        .post(
        "https://www.dataaccess.com/webservicesserver/NumberConversion.wso"
        )
        .header(
        "Content-Type",
        "text/xml; charset=utf-8"
        )
        .header(
        "SOAPAction",
        "http://www.dataaccess.com/webservicesserver/NumberToWords"
        )
        .body(xml)
        .send()
        .unwrap()
        .text()
        .unwrap();

        let ingles=
        extraer(
        &soap
        );

        let url=
        format!(
        "https://translate.googleapis.com/translate_a/single?client=gtx&sl=en&tl=es&dt=t&q={}",
        ingles.replace(" ","%20")
        );

        let traduccion=
        cliente
        .get(url)
        .send()
        .unwrap()
        .text()
        .unwrap();

        let texto=
        traduccion
        .split("\"")
        .nth(1)
        .unwrap_or("Error");

        request.respond(
        Response::from_string(
        texto
        )
        ).unwrap();

    }

}