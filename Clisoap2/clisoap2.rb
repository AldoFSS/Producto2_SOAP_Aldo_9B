# clieSoap2.rb - SOAP + Traducción en Ruby
require 'sinatra'
require 'net/http'
require 'json'
require 'uri'

set :port, 8002

get '/' do
  content_type :text
  numero = params['n'] || "0"
  
  # Simula el consumo SOAP que retorna "ten" y se procesa mediante API de traducción
  texto_ingles = "ten"
  url = URI("https://translate.googleapis.com/translate_a/single?client=gtx&sl=en&tl=es&dt=t&q=#{URI.encode_www_form_component(texto_ingles)}")
  
  res = Net::HTTP.get(url)
  datos = JSON.parse(res)
  texto_espanol = datos[0][0][0] rescue texto_ingles
  
  "Ruby Translation Engine: #{texto_ingles} -> Traducido a: #{texto_espanol}"
end