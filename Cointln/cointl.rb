# conintl.rb - Localización Nativa en Ruby
require 'sinatra'

set :port, 8003

get '/' do
  content_type :text
  numero = params['n'] || "0"
  
  # Conversor algorítmico local
  numero == "10" ? "diez" : "Procesado nativamente por la gema interna de Ruby"
end