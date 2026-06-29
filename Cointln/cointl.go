package main

import (
	"fmt"
	"net/http"
	"strconv"
	"github.com/divan/num2words"
	translategooglefree "github.com/bas24/googletranslatefree"
)

func handler(w http.ResponseWriter, r *http.Request) {

	numero := r.URL.Query().Get("n")

	n, err := strconv.Atoi(numero)

	if err != nil {
		http.Error(w, "Número inválido", 400)
		return
	}

	ingles := num2words.Convert(n)

	espanol, err := translategooglefree.Translate(
		ingles,
		"en",
		"es",
	)

	if err != nil {
		http.Error(w, err.Error(), 500)
		return
	}

	fmt.Fprint(w, espanol)
}

func main() {

	http.HandleFunc("/", handler)

	fmt.Println("Servidor activo puerto 8003")

	http.ListenAndServe(":8003", nil)
}