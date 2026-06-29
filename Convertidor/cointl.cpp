#include <iostream>
#include <string>
#include <winsock2.h>

#pragma comment(lib,"ws2_32.lib")

using namespace std;

string unidades[]={
"cero",
"uno",
"dos",
"tres",
"cuatro",
"cinco",
"seis",
"siete",
"ocho",
"nueve",
"diez",
"once",
"doce",
"trece",
"catorce",
"quince",
"dieciseis",
"diecisiete",
"dieciocho",
"diecinueve"
};

string decenas[]={
"",
"",
"veinte",
"treinta",
"cuarenta",
"cincuenta",
"sesenta",
"setenta",
"ochenta",
"noventa"
};

string convertir(int n){

if(n<20)
return unidades[n];

if(n<100){

int d=n/10;
int u=n%10;

if(u==0)
return decenas[d];

if(d==2)
return "veinti"+unidades[u];

return decenas[d]+" y "+unidades[u];
}

if(n<1000){

int c=n/100;
int r=n%100;

string centena;

switch(c){

case 1:
centena=(r==0)?
"cien":
"ciento";
break;

case 2:
centena="doscientos";
break;

case 3:
centena="trescientos";
break;

case 4:
centena="cuatrocientos";
break;

case 5:
centena="quinientos";
break;

case 6:
centena="seiscientos";
break;

case 7:
centena="setecientos";
break;

case 8:
centena="ochocientos";
break;

case 9:
centena="novecientos";
break;

}

if(r==0)
return centena;

return centena+" "+convertir(r);

}

return "numero demasiado grande";
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
htons(8003);

addr.sin_addr.s_addr=
INADDR_ANY;

bind(
servidor,
(sockaddr*)&addr,
sizeof(addr)
);

listen(
servidor,5
);

cout<<"Servidor Cointln puerto 8003"<<endl;

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

int n=
stoi(numero);

string texto=
convertir(n);

string respuesta=
"HTTP/1.1 200 OK\r\n"
"Content-Type:text/html\r\n\r\n"+
texto;

send(
cliente,
respuesta.c_str(),
respuesta.size(),
0
);

closesocket(cliente);

}

}