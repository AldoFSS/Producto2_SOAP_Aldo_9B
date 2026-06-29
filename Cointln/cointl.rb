require 'webrick'
require 'numbers_and_words'
require 'i18n'

I18n.available_locales = [:en, :es]
I18n.locale = :es

server = WEBrick::HTTPServer.new(
  Port: 8003
)

server.mount_proc '/' do |req, res|

  numero = (req.query['n'] || "0").to_i

  resultado = numero.to_words(
    locale: :es
  )

  res.body = resultado

end

trap("INT") { server.shutdown }

puts "Servidor Convertidor activo puerto 8003"

server.start