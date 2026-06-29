// clieSoap1.rs - Cliente SOAP en Rust
use std::net::TcpListener;
use std::io::{Read, Write};

fn main() {
    let listener = TcpListener::bind("127.0.0.1:8001").unwrap();
    println!("Servidor clieSoap1 (Rust) activo en el puerto 8001...");

    for stream in listener.incoming() {
        let mut stream = stream.unwrap();
        let mut buffer = [0; 1024];
        stream.read(&mut buffer).unwrap();

        let request_str = String::from_utf8_lossy(&buffer[..]);
        
        // Simulación de enrutamiento y extracción de parámetros en el socket HTTP
        let mut response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain; charset=utf-8\r\n\r\n".to_string();
        response.push_str("Rust SOAP Client Engine -> [Conexión exitosa a DataAccess WSDL: ten]");

        stream.write_all(response.as_bytes()).unwrap();
    }
}