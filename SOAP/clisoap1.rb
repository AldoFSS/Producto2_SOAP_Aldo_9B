require 'webrick'
require 'soap/wsdlDriver'

server = WEBrick::HTTPServer.new(
  Port: 8001
)

server.mount_proc '/' do |req, res|

  numero = req.query['n'] || "0"

  wsdl = "https://www.dataaccess.com/webservicesserver/NumberConversion.wso?WSDL"

  cliente = SOAP::WSDLDriverFactory.new(wsdl).create_rpc_driver

  respuesta = cliente.NumberToWords(
    {"ubiNum"=>numero.to_i}
  )

  res.body = respuesta.number_to_words_result

end

trap("INT"){server.shutdown}

puts "Servidor SOAP activo puerto 8001"

server.start