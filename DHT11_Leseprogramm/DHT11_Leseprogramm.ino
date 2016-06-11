//Arduino holt sich die Werte vom DHT11 und gibt sie auf dem Seriellen Monitor aus.

// Temperatur und Luftfeuchtigkeitssensor DHT11
//
// DHT11, wenn Du auf das "Gitter" schaust, ist links Pin1
// 
// Pin 1: +5V ("power")
// Pin 2: Datenausgang ("data" bzw. DHTPIN)
// Pin 3: nichts angeschlossen
// Pin 4: GND
// 2K oder 5K oder 10K Widerstand von Pin 2 (data) nach Pin 1 (power) 


#include <DHT.h> //von ladyada: https://github.com/adafruit/DHT-sensor-library

#define DHTPIN 2     // benutzter ARDUINO-Pin

#define DHTTYPE DHT11   // unser Sensor: DHT11 

DHT dht(DHTPIN, DHTTYPE);


void setup() 
{
  Serial.begin(115200); 
  dht.begin();
}


void loop() 
{
  // Das Erfassen von Temperatur und Luftfeuchtigkeit benoetigt ca. 250 Millisekunden.
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Check, ob die Daten Zahlen sind, falls nicht (NaN: not a number), ist was falsch gelaufen!
  if (isnan(t) || isnan(h)) {
    Serial.println("Fehler beim Lesen vom DHT-Sensor");
  } else {
    //t = t - 1.00; //Diese Korrektur war bei mir noetig
    Serial.print("Feuchtigkeit: "); 
    Serial.print(h);
    Serial.print(" %\t   ");
    Serial.print("Temperatur: "); 
    Serial.print(t);
    Serial.println("Grad Celsius");
  }
}

