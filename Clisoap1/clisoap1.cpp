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

string n=
req.substr(pos+2);

size_t fin=
n.find(" ");

if(fin!=string::npos)
n=n.substr(0,fin);

return n;
}

string convertirNumero(string numero){

CURL* curl=
curl_easy_init();

string respuesta;

if(curl){

string xml=
"<?xml version=\"1.0\" encoding=\"utf-8\"?>"
"<soap:Envelope "
"xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" "
"xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" "
"xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\">"
"<soap:Body>"
"<NumberToWords xmlns=\"http://www.dataaccess.com/webservicesserver/\">"
"<ubiNum>"+numero+"</ubiNum>"
"</NumberToWords>"
"</soap:Body>"
"</soap:Envelope>";

struct curl_slist* headers=NULL;

headers=
curl_slist_append(
headers,
"Content-Type: text/xml"
);

headers=
curl_slist_append(
headers,
"SOAPAction: \"http://www.dataaccess.com/webservicesserver/NumberToWords\""
);

curl_easy_setopt(
curl,
CURLOPT_URL,
"https://www.dataaccess.com/webservicesserver/NumberConversion.wso"
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

curl_easy_perform(curl);

curl_easy_cleanup(curl);

}

return respuesta;
}

int main(){

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

addr.sin_family=
AF_INET;

addr.sin_port=
htons(8001);

addr.sin_addr.s_addr=
INADDR_ANY;

bind(
servidor,
(sockaddr*)&addr,
sizeof(addr)
);

listen(
servidor,
5
);

cout<<"Servidor puerto 8001"<<endl;

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

string resultado=
convertirNumero(
numero
);

string respuesta=
"HTTP/1.1 200 OK\r\n"
"Content-Type:text/html\r\n\r\n"+
resultado;

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