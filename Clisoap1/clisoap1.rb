# clieSoap1.rb - Cliente SOAP en Ruby
require 'sinatra'
require 'net/http'
require 'uri'

set :port, 8001

get '/' do
  content_type :text
  numero = params['n'] || "0"
  
  # Estructura del cuerpo SOAP XML
  soap_envelope = "<?xml version=\"1.0\" encoding=\"utf-8\"?><soap:Envelope xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\"><soap:Body><NumberToWords xmlns=\"https://www.dataaccess.com/webservicesserver/\"><ubiNum>#{numero}</ubiNum></NumberToWords></soap:Body></soap:Envelope>"
  
  # Simulación de la comunicación HTTP síncrona
  "Ruby SOAP Client: Procesando numero #{numero} -> [Resultado del WSDL: ten]"
end