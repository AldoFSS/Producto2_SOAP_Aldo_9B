#include <iostream>
#include <string>
#include <winsock2.h>
#include <curl/curl.h>

#pragma comment(lib,"ws2_32.lib")

using namespace std;

size_t WriteCallback(
void* contents,
size_t size,
size_t nmemb,
string* output
){
output->append(
(char*)contents,
size*nmemb
);

return size*nmemb;
}

string extraerNumero(string req){

size_t pos=req.find("n=");

if(pos==string::npos)
return "";

string n=req.substr(pos+2);

size_t fin=n.find(" ");

if(fin!=string::npos)
n=n.substr(0,fin);

return n;
}

string peticionHTTP(
string url,
string xml="",
bool soap=false
){

CURL* curl=
curl_easy_init();

string respuesta;

if(curl){

curl_easy_setopt(
curl,
CURLOPT_URL,
url.c_str()
);

curl_easy_setopt(
curl,
CURLOPT_WRITEFUNCTION,
WriteCallback
);

curl_easy_setopt(
curl,
CURLOPT_WRITEDATA,
&respuesta
);

if(soap){

struct curl_slist* headers=NULL;

headers=
curl_slist_append(
headers,
"Content-Type:text/xml"
);

headers=
curl_slist_append(
headers,
"SOAPAction:\"http://www.dataaccess.com/webservicesserver/NumberToWords\""
);

curl_easy_setopt(
curl,
CURLOPT_HTTPHEADER,
headers
);

curl_easy_setopt(
curl,
CURLOPT_POSTFIELDS,
xml.c_str()
);

}

curl_easy_perform(curl);

curl_easy_cleanup(curl);

}

return respuesta;

}

string convertirNumero(string numero){

string xml=
"<?xml version=\"1.0\"?>"
"<soap:Envelope "
"xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\">"
"<soap:Body>"
"<NumberToWords xmlns=\"http://www.dataaccess.com/webservicesserver/\">"
"<ubiNum>"+numero+"</ubiNum>"
"</NumberToWords>"
"</soap:Body>"
"</soap:Envelope>";

string respuesta=
peticionHTTP(
"https://www.dataaccess.com/webservicesserver/NumberConversion.wso",
xml,
true
);

size_t ini=
respuesta.find(
"<m:NumberToWordsResult>"
);

size_t fin=
respuesta.find(
"</m:NumberToWordsResult>"
);

if(
ini==string::npos ||
fin==string::npos
)
return "";

ini+=25;

return respuesta.substr(
ini,
fin-ini
);

}

string traducir(string texto){

string url=
"https://translate.googleapis.com/translate_a/single?client=gtx&sl=en&tl=es&dt=t&q="+texto;

return peticionHTTP(url);

}

int main(){

curl_global_init(
CURL_GLOBAL_DEFAULT
);

WSADATA wsa;

WSAStartup(
MAKEWORD(2,2),
&wsa
);

SOCKET servidor=
socket(
AF_INET,
SOCK_STREAM,
0
);

sockaddr_in addr;

addr.sin_family=AF_INET;
addr.sin_port=htons(8002);
addr.sin_addr.s_addr=INADDR_ANY;

bind(
servidor,
(sockaddr*)&addr,
sizeof(addr)
);

listen(
servidor,
5
);

cout<<"Servidor puerto 8002"<<endl;

while(true){

SOCKET cliente=
accept(
servidor,
NULL,
NULL
);

char buffer[4096];

recv(
cliente,
buffer,
4096,
0
);

string peticion(buffer);

string numero=
extraerNumero(
peticion
);

string ingles=
convertirNumero(
numero
);

string espanol=
traducir(
ingles
);

string respuesta=
"HTTP/1.1 200 OK\r\n"
"Content-Type:text/html\r\n\r\n"+
espanol;

send(
cliente,
respuesta.c_str(),
respuesta.size(),
0
);

closesocket(
cliente
);

}

}