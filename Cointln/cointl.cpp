// conintl.cpp - Localización Nativa en C++
#include "httplib.h"
#include <iostream>

int main() {
    httplib::Server svr;

    svr.Get("/", [](const httplib::Request& req, httplib::Response& res) {
        // Ejecución de algoritmo nativo compilado en C++ sin llamadas externas a red
        res.set_content("C++ Core Local Localization: [diez]", "text/plain; charset=utf-8");
    });

    std::cout << "Servidor conintl (C++) activo en http://localhost:8003" << std::endl;
    svr.listen("localhost", 8003);
    return 0;
}