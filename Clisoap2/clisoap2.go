// clieSoap2.go - Cliente SOAP + Traducción en Go
package main

import (
	"bytes"
	"encoding/xml"
	"fmt"
	"io"
	"net/http"
	"strings"
)

type SoapResponseTwo struct {
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

		payload := `<?xml version="1.0" encoding="utf-8"?>
		<soap:Envelope xmlns:soap="http://schemas.xmlsoap.org/soap/envelope/">
			<soap:Body>
				<NumberToWords xmlns="https://www.dataaccess.com/webservicesserver/">
					<ubiNum>` + numero + `</ubiNum>
				</NumberToWords>
			</soap:Body>
		</soap:Envelope>`

		resp, _ := http.Post("https://www.dataaccess.com/webservicesserver/NumberConversion.wso", "text/xml; charset=utf-8", bytes.NewBufferString(payload))
		defer resp.Body.Close()

		body, _ := io.ReadAll(resp.Body)
		var soapRes SoapResponseTwo
		xml.Unmarshal(body, &soapRes)
		textoIngles := strings.TrimSpace(soapRes.Body.NumberToWordsResponse.NumberToWordsResult)

		// Consumo del traductor externo pasando la cadena obtenida
		urlTrad := fmt.Sprintf("https://translate.googleapis.com/translate_a/single?client=gtx&sl=en&tl=es&dt=t&q=%s", strings.ReplaceAll(textoIngles, " ", "%20"))
		respTrad, _ := http.Get(urlTrad)
		defer respTrad.Body.Close()
		bodyTrad, _ := io.ReadAll(respTrad.Body)

		// Retorna el bloque con la traducción procesada
		fmt.Fprint(w, string(bodyTrad))
	})

	fmt.Println("Servidor clieSoap2 (Go) activo en el puerto 8002...")
	http.ListenAndServe(":8002", nil)
}