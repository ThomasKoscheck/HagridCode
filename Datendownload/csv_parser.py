#!/usr/bin/python3.4
import csv
import urllib.request
import RPi.GPIO as GPIO
import time
import os

#Folgendes nimmt das Aktuelle Datum und konvertiert es in ein fuer die url
#funktionierendes Format

datetime = time.localtime()
heute = time.strftime("%Y%m%d", datetime)
gestern = str(int(heute)-1)

#print(heute+ " " + gestern) #test

os.system("rm -f ~/feinstaub_werte")
urllib.request.urlretrieve("http://www.umweltbundesamt.de/luftdaten/data.csv?pollutant=PM1&data_type=1TMW&date=%s&dateTo=%s&station=DEBW019" % (gestern,heute), "/home/pi/feinstaub_werte" )

#Folgender Code ist nich sehr schoen. Er soll die letzte Zahl der Datei
#feinstaub_werte extrahieren

feinstaub_werte = open("feinstaub_werte").read()
feinstaub_werte = feinstaub_werte.split()
feinstaub_werte = feinstaub_werte[len(feinstaub_werte)-1]
feinstaub_werte = feinstaub_werte.split(sep = ";")
feinstaub_werte = feinstaub_werte[len(feinstaub_werte)-1]
feinstaub_werte = int(feinstaub_werte)

print(feinstaub_werte) #test

#Schreibt pins an
grueneLuft = 20
gelbeLuft = 30
orangeneLuft = 40

GPIO.setmode(GPIO.BCM)
GPIO.setup(0, GPIO.OUT) #gruen
GPIO.setup(2, GPIO.OUT) #gelb
GPIO.setup(3, GPIO.OUT) #orange
GPIO.setup(7, GPIO.OUT) #rot

if feinstaub_werte <= grueneLuft:
        GPIO.output(0, GPIO.HIGH)
        GPIO.output(2, GPIO.LOW)
        GPIO.output(3, GPIO.LOW)	
        GPIO.output(7, GPIO.LOW)

elif feinstaub_werte <= gelbeLuft:
        GPIO.output(0, GPIO.LOW)
        GPIO.output(2, GPIO.HIGH)
        GPIO.output(3, GPIO.LOW)
        GPIO.output(7, GPIO.LOW)

elif feinstaub_werte <= orangeneLuft:
        GPIO.output(0, GPIO.LOW)
        GPIO.output(2, GPIO.LOW)
        GPIO.output(3, GPIO.HIGH)
        GPIO.output(7, GPIO.LOW)

elif feinstaub_werte > orangeneLuft:
        GPIO.output(0, GPIO.LOW)
        GPIO.output(2, GPIO.LOW)
        GPIO.output(3, GPIO.LOW)
        GPIO.output(7, GPIO.HIGH)
else:
	print("Fehler bei der Dateneingabe")

GPIO.cleanup()

