// clieSoap1.go - Cliente SOAP en Go
package main

import (
	"bytes"
	"encoding/xml"
	"fmt"
	"io"
	"net/http"
)

type Envelope struct {
	Body Body `xml:"Body"`
}

type Body struct {
	NumberToWordsResponse NumberToWordsResponse `xml:"NumberToWordsResponse"`
}

type NumberToWordsResponse struct {
	NumberToWordsResult string `xml:"NumberToWordsResult"`
}

func handler(w http.ResponseWriter, r *http.Request) {

	// Captura parámetro n de la URL
	numero := r.URL.Query().Get("n")

	if numero == "" {
		http.Error(w, "Falta parámetro n", 400)
		return
	}

	// XML SOAP
	payload := `<?xml version="1.0" encoding="utf-8"?>
<soap:Envelope xmlns:soap="http://schemas.xmlsoap.org/soap/envelope/">
    <soap:Body>
        <NumberToWords xmlns="http://www.dataaccess.com/webservicesserver/">
            <ubiNum>` + numero + `</ubiNum>
        </NumberToWords>
    </soap:Body>
</soap:Envelope>`

	req, err := http.NewRequest(
		"POST",
		"https://www.dataaccess.com/webservicesserver/NumberConversion.wso",
		bytes.NewBuffer([]byte(payload)),
	)

	if err != nil {
		http.Error(w, err.Error(), 500)
		return
	}

	req.Header.Set("Content-Type", "text/xml;charset=utf-8")
	req.Header.Set("SOAPAction", "NumberToWords")

	client := &http.Client{}

	resp, err := client.Do(req)

	if err != nil {
		http.Error(w, err.Error(), 500)
		return
	}

	defer resp.Body.Close()

	body, _ := io.ReadAll(resp.Body)

	var result Envelope

	xml.Unmarshal(body, &result)

	// Mostrar resultado
	fmt.Fprint(w,
		result.Body.NumberToWordsResponse.NumberToWordsResult)
}

func main() {

	http.HandleFunc("/", handler)

	fmt.Println("Servidor activo en puerto 8001")

	http.ListenAndServe(":8001", nil)

}