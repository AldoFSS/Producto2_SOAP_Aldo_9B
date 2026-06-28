// conintl.rs - Localización Nativa en Rust
use std::net::TcpListener;
use std::io::{Read, Write};

fn main() {
    let listener = TcpListener::bind("127.0.0.1:8003").unwrap();
    println!("Servidor conintl (Rust) activo en el puerto 8003...");

    for stream in listener.incoming() {
        let mut stream = stream.unwrap();
        let mut buffer = [0; 1024];
        stream.read(&mut buffer).unwrap();

        // Respuesta directa desde binario nativo en memoria
        let mut response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain; charset=utf-8\r\n\r\n".to_string();
        response.push_str("Rust Native Localization: [diez]");

        stream.write_all(response.as_bytes()).unwrap();
    }
}