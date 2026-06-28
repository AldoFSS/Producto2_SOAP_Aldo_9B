// clieSoap1.cpp - Cliente SOAP en C++
#include "httplib.h"
#include <iostream>
#include <string>

int main() {
    httplib::Server svr;

    svr.Get("/", [](const httplib::Request& req, httplib::Response& res) {
        std::string numero = req.get_param_value("n");
        if(numero.empty()) numero = "0";

        // Simulación del empaquetado del sobre SOAP a través de peticiones HTTP en C++
        std::string respuestaSimulada = "C++ SOAP Network Response para " + numero + " -> [ten]";
        
        res.set_content(respuestaSimulada, "text/plain; charset=utf-8");
    });

    std::cout << "Servidor clieSoap1 (C++) activo en http://localhost:8001" << std::endl;
    svr.listen("localhost", 8001);
    return 0;
}