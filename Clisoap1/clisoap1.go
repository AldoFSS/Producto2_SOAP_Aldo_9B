// clieSoap1.go - Cliente SOAP Puro en Go
package main

import (
	"bytes"
	"encoding/xml"
	"fmt"
	"io"
	"net/http"
	"strings"
)

// Estructura XML para decodificar la respuesta del servicio SOAP
type SoapResponse struct {
	XMLName xml.Name `xml:"Envelope"`
	Body    struct {
		NumberToWordsResponse struct {
			NumberToWordsResult string `xml:"NumberToWordsResult"`
		} `xml:"NumberToWordsResponse"`
	} `xml:"Body"`
}

func main() {
	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		numero := r.URL.Query().Get("n")
		if numero == "" { numero = "0" }

		// Construcción manual del sobre XML de SOAP (SOAP Envelope)
		payload := `<?xml version="1.0" encoding="utf-8"?>
		<soap:Envelope xmlns:soap="http://schemas.xmlsoap.org/soap/envelope/">
			<soap:Body>
				<NumberToWords xmlns="https://www.dataaccess.com/webservicesserver/">
					<ubiNum>` + numero + `</ubiNum>
				</NumberToWords>
			</soap:Body>
		</soap:Envelope>`

		// Envío de la petición HTTP POST al servicio remoto
		resp, err := http.Post("https://www.dataaccess.com/webservicesserver/NumberConversion.wso", "text/xml; charset=utf-8", bytes.NewBufferString(payload))
		if err != nil {
			http.Error(w, "Error al conectar con SOAP", 500)
			return
		}
		defer resp.Body.Close()

		body, _ := io.ReadAll(resp.Body)
		var soapRes SoapResponse
		xml.Unmarshal(body, &soapRes)

		// Envía el texto plano en inglés devuelto por el XML
		fmt.Fprint(w, strings.TrimSpace(soapRes.Body.NumberToWordsResponse.NumberToWordsResult))
	})

	fmt.Println("Servidor clieSoap1 (Go) activo en el puerto 8001...")
	http.ListenAndServe(":8001", nil)
}