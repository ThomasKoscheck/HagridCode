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
#include <WiFiClient.h>

//Downloadlink zum Wert von Ulm am 10.06 bis 11.06
//http://www.umweltbundesamt.de/luftdaten/data.csv?pollutant=PM1&data_type=1TMW&date=20160610&dateTo=20160611&station=DEBW019
 
// WiFi information
const char* ssid     = "666666";
const char* password = "12345678";

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


void loop() {
    delay(5000);
    Serial.print("connecting to ");
    Serial.println(host);

    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
    }

    // We now create a URI for the request
    String url = "/stan";

    Serial.print("Requesting URL: ");
    Serial.println(url);

    // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
    delay(10);

    // Read all the lines of the reply from server and print them to Serial
    Serial.println("Respond:");
    while(client.available()){
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }

    Serial.println();
    Serial.println("closing connection");
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


<<<<<<< HEAD
void feinstaubauswertung(int fnstb)  {    //fnstb == Feinstaub //nicht schön
  int guteLuft = 20;  //BEISPEILWERTE TBC
  int maesigeLuft = 40;
  int mieseLuft = 60;
  int youaredead = 80;

  if(fnstb<=guteLuft)  {
    smileyzeiger(1);
  }
  else if(fnstb<=maesigeLuft) {
    smileyzeiger(2);
  }
  else if(fnstb<=mieseLuft) {
    smileyzeiger(3);
    
  }
  
 /* switch(feinstaub) {
    case(feinstaub<guteLuft):
      smileyzeiger(1);
      break;
    case(feinstaub<maesigeLuft):
      smileyzeiger(2);
      break;
    case(feinstaub<schlechteLuft):
      smileyzeiger(3);
      break;
    case(feinstaub<youaredead):
      smileyzeiger(4);
      break;
    default:
      return;
      break;
    

    }*/
  }

=======
>>>>>>> refs/remotes/origin/master
