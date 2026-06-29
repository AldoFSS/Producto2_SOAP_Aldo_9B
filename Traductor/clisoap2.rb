require 'webrick'
require 'savon'
require 'google_translator'

server = WEBrick::HTTPServer.new(
  Port: 8002
)

server.mount_proc '/' do |req,res|

  numero = req.query['n']

  client = Savon.client(
    wsdl:"https://www.dataaccess.com/webservicesserver/NumberConversion.wso?WSDL"
  )

  respuesta = client.call(
    :number_to_words,
    message:{ubiNum:numero}
  )

  ingles = respuesta.body[
    :number_to_words_response
  ][
    :number_to_words_result
  ]

traductor = GoogleTranslator.new

espanol = traductor.translate(
    ingles,
    from: 'en',
    to: 'es'
)

  res.body = espanol

end

trap("INT"){server.shutdown}

puts "Servidor Traductor puerto 8002"

server.start