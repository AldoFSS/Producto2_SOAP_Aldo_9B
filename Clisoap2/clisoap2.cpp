// clieSoap2.cpp - SOAP + Traducción en C++
#include "httplib.h"
#include <iostream>

int main() {
    httplib::Server svr;

    svr.Get("/", [](const httplib::Request& req, httplib::Response& res) {
        // Simulación síncrona del paso intermedio de traducción usando sockets en C++
        std::string respuestaTraducida = "C++ Core: Traduciendo respuesta remota de SOAP WSDL al Español -> [diez]";
        
        res.set_content(respuestaTraducida, "text/plain; charset=utf-8");
    });

    std::cout << "Servidor clieSoap2 (C++) activo en http://localhost:8002" << std::endl;
    svr.listen("localhost", 8002);
    return 0;
}