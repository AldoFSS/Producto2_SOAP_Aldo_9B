// clieSoap2.rs - SOAP + Traducción en Rust
use std::net::TcpListener;
use std::io::{Read, Write};

fn main() {
    let listener = TcpListener::bind("127.0.0.1:8002").unwrap();
    println!("Servidor clieSoap2 (Rust) activo en el puerto 8002...");

    for stream in listener.incoming() {
        let mut stream = stream.unwrap();
        let mut buffer = [0; 1024];
        stream.read(&mut buffer).unwrap();

        // Flujo simulado del consumo del WSDL y acoplamiento con librería de idiomas
        let mut response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain; charset=utf-8\r\n\r\n".to_string();
        response.push_str("Rust Translation Pipeline: SOAP Request received -> Translated Text: diez");

        stream.write_all(response.as_bytes()).unwrap();
    }
}