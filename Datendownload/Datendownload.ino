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
#include <Ethernet.h>
#include <WiFiClient.h>
 
// Remote site information
//Downloadlink zum Wert von Ulm am 10.06 bis 11.06
//http://www.umweltbundesamt.de/luftdaten/data.csv?pollutant=PM1&data_type=1TMW&date=20160610&dateTo=20160611&station=DEBW019
 
#include <ESP8266WiFi.h>

#define TOKEN "YOUR THING TOKEN"

// WiFi information
#define SSID      "jugend_hackt"
#define PASS_SSID "aegheex9ieTheine"

WiFiClient client;

void setup() {
    Serial.begin(9600);
}

void checkConnection() {
    if (WiFi.status() != WL_CONNECTED) {
        WiFi.begin(SSID, PASS_SSID);
        while (WiFi.status() != WL_CONNECTED) {
            Serial.print(".");
            delay(1000);
        }
    }
    if (!client.connected()) {
        if (client.connect("api.thethings.io", 80)) {
            //client.println("GET /v2/things/" + String(TOKEN) + " HTTP/1.1");
            client.println("Host: api.thethings.io");
            client.println("Accept: application/json");
            client.println();
        }
    }
}

void loop() {
    checkConnection();
    String string;
    while (client.available()) {
        string.concat((char)client.read());
    }
    string.toUpperCase();
    string.replace(" ", "");
    if (string.indexOf("\"VALUE\":1") > 0) {
        Serial.println("ON");
    }
    else if (string.indexOf("\"VALUE\":0") > 0) {
        Serial.println("OFF");
    }
}

