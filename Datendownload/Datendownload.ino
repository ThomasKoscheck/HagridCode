#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
//#include <WiFi.h>
#include <SPI.h>

//Downloadlink zum Wert von Ulm am 10.06 bis 11.06
//http://www.umweltbundesamt.de/luftdaten/data.csv?pollutant=PM1&data_type=1TMW&date=20160610&dateTo=20160611&station=DEBW019 
// WiFi information
char ssid[] = "jugend_hackt"; //  your network SSID (name)
char pass[] = "aegheex9ieTheine";
int smileyzeiger(int smiley);
const char* host = "www.google.com";    //  10.0.15.98

int status = WL_IDLE_STATUS;

const int httpsPort = 80;
void setup();
void loop();
void serverdatenabfrageserial(String ziel);
void feinstaubauswertung(int fnstb);
void senddata(String data);
String getdata();
boolean isDataThere();
WiFiClient client;
char server[] = "www.google.com";

String getanfrage()  {
  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected to server");
    // Make a HTTP request:
    client.println("GET /search?q=arduino HTTP/1.1");
    client.println("Host: www.google.com");
    client.println("Connection: close");
    client.println();
  }
}

String datenempfang() {
  String empfang = "";

  while (client.available()) {
    char c = client.read();
    Serial.write(c);
    empfang += c;
    
  }


  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting from server.");
    client.stop();  
}
}






void setup() {
  Serial.begin(115200);
  delay(10);

  //WiFi Verbindungsaufbau um später Datei abrufen zu können

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  Serial.print("Trying to connect");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

String serialrecieve()  {
  String recieve;
  while(Serial.available()) {
    recieve += (char)Serial.read();
  }
  return recieve;
}

/*void serverdatenabfrageserial(String ziel) {
      // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
      Serial.println("connection failed");
      return;
    }

    String url = "";

    client.print(String("GET ") + url +" HTTP/1.1\r\n" + "Host: " + ziel + "\r\n" + "Connection: close\r\n\r\n");
    Serial.println("Antwort:");
    while(client.available()) {
      Serial.println(client.readStringUntil('\r'));
    }    
}
*/
void loop() {
  getanfrage();
  delay(300);
  getanfrage();
  delay(700);
  }

void feinstaubauswertung(int fnstb)  {    //fnstb == Feinstaub //nicht schön
  int grueneLuft = 20;  
  int gelbeLuft = 30;
  int orangeneLuft = 40;    /*Werte größer als orangeneLuft -> rot*/

  if(fnstb<=grueneLuft) {
    smileyzeiger(1);
  }
  
  else if(fnstb<=gelbeLuft) {
    smileyzeiger(2);
  }
  
  else if(fnstb<=orangeneLuft) {
    smileyzeiger(3);
  }

  else if(fnstb>orangeneLuft) {
    smileyzeiger(4);
  }

  else {
    Serial.println("Fehler bei der Datenverarbeitung");
  }   
}




