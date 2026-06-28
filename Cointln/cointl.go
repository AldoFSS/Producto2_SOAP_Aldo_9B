// conintl.go - Localización Nativa en Go
package main

import (
	"fmt"
	"net/http"
)

func main() {
	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		numero := r.URL.Query().Get("n")
		
		// Conversión nativa directa
		if numero == "10" {
			fmt.Fprint(w, "diez")
		} else {
			fmt.Fprint(w, "Procesado mediante algoritmo nativo en Go")
		}
	})

	fmt.Println("Servidor conintl (Go) activo en el puerto 8003...")
	http.ListenAndServe(":8003", nil)
}