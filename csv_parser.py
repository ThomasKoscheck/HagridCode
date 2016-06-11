#!/usr/bin/python3.4
import csv
import urllib.request
import os
import time
import serial

#Folgendes nimmt das Aktuelle Datum und konvertiert es in ein fuer die url
#funktionierendes Format

datetime = time.localtime()
heute = time.strftime("%Y%m%d", datetime)
gestern = str(int(heute)-1)

#print(heute+ " " + gestern) #test

os.system("rm feinstaub_werte")
urllib.request.urlretrieve("http://www.umweltbundesamt.de/luftdaten/data.csv?pollutant=PM1&data_type=1TMW&date=%s&dateTo=%s&station=DEBW019" % (gestern,heute), "feinstaub_werte" )

#Folgender Code ist nich sehr schoen. Er soll die letzte Zahl der Datei
#feinstaub_werte extrahieren

feinstaub_werte = open("feinstaub_werte").read()
feinstaub_werte = feinstaub_werte.split()
feinstaub_werte = feinstaub_werte[len(feinstaub_werte)-1]
feinstaub_werte = feinstaub_werte.split(sep = ";")
feinstaub_werte = feinstaub_werte[len(feinstaub_werte)-1]

print(feinstaub_werte) #test

#Schicke feinstaub_werte auf als string /dev/ttyUSB0

ser = serial.Serial('/dev/ttyUSB0')
print(ser.name)
ser.write(feinstaub_werte.encode())
ser.close()

#~ print(feinstaub_werte)
