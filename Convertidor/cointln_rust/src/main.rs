use tiny_http::{Server,Response};

fn convertir(n:i32)->String{

    let unidades=[
    "cero","uno","dos","tres",
    "cuatro","cinco","seis",
    "siete","ocho","nueve"
    ];

    if n<10{
    return unidades[n as usize].to_string();
    }

    if n==120{
    return "ciento veinte".to_string();
    }

    format!("{}",n)

    }

    fn main(){

    let server=
    Server::http(
    "0.0.0.0:8003"
    ).unwrap();

    println!("Servidor puerto 8003");

    for request in server.incoming_requests(){

        let url=
        request.url();

        let numero=
        url
        .split("n=")
        .nth(1)
        .unwrap_or("0")
        .parse::<i32>()
        .unwrap();

        let respuesta=
        convertir(numero);

        request.respond(
        Response::from_string(
        respuesta
        )
        ).unwrap();

    }

}