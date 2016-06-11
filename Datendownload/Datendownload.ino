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
#include <SPI.h>
//#include <Ethernet.h>

//Downloadlink zum Wert von Ulm am 10.06 bis 11.06
//http://www.umweltbundesamt.de/luftdaten/data.csv?pollutant=PM1&data_type=1TMW&date=20160610&dateTo=20160611&station=DEBW019
 
// WiFi information
const char* ssid     = "jugend_hackt";
const char* password = "aegheex9ieTheine";
int smileyzeiger(int smiley);

const char* host = "www.umweltbundesamt.de";



void setup() {
  Serial.begin(115200);
  delay(10);

  //WiFi Verbindungsaufbau um später Datei abrufen zu können

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
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
  String recieve
  while(Serial.available()) {
    recieve += (char)Serial.read();
  }
  return recieve;
}

void serverdatenabfrageserial(String ziel) {
      // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
      Serial.println("connection failed");
      return;
    }

    String url = "/stan";

    client.print(String("GET ") + url +" HTTP/1.1\r\n" + "Host: " + ziel + "\r\n" + "Connection: close\r\n\r\n");
    Serial.println("Antwort:");
    while(client.available()) {
      Serial.println(client.readStringUntil('\r'));
    }
    
}

void loop() {

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




