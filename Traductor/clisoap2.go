package main

import (
	"bytes"
	"encoding/xml"
	"fmt"
	"io"
	"net/http"
	googletranslatefree "github.com/bas24/googletranslatefree"
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

	numero := r.URL.Query().Get("n")

	if numero == "" {
		http.Error(w, "Falta parámetro n", 400)
		return
	}

	payload := `<?xml version="1.0" encoding="utf-8"?>
<soap:Envelope xmlns:soap="http://schemas.xmlsoap.org/soap/envelope/">
<soap:Body>
<NumberToWords xmlns="http://www.dataaccess.com/webservicesserver/">
<ubiNum>` + numero + `</ubiNum>
</NumberToWords>
</soap:Body>
</soap:Envelope>`

	req, _ := http.NewRequest(
		"POST",
		"https://www.dataaccess.com/webservicesserver/NumberConversion.wso",
		bytes.NewBuffer([]byte(payload)),
	)

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

	ingles := result.Body.NumberToWordsResponse.NumberToWordsResult

	// Traducción inglés → español
	espanol, err := googletranslatefree.Translate(
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

	fmt.Println("Servidor activo puerto 8002")

	http.ListenAndServe(":8002", nil)
}