## 
## Webserver auf Raspberry Pi, der FLASK benutzt


#!/usr/bin/python
from flask import Flask
from flask import request
app = Flask(__name__)

## Eingabe vom IP/temp gibt Zugriff auf nachfolgende Methode für HTTP-GET von ESP
@app.route("/temp")
def temp():
	f = open("temp").read()
	return f

## Eingabe vom IP/luft_feucht gibt Zugriff auf nachfolgende Methode für HTTP-GET von ESP
@app.route("/luft_feucht")
def temp():
        f = open("luft_feucht").read()
        return f

## Eingabe vom IP/feinstaub gibt Zugriff auf nachfolgende Methode für HTTP-GET von ESP
@app.route("/feinstaub")
def temp():
        f = open("feinstaub").read()
        return f

## Bei senden von HTTP-GET werden Daten an den Server zur Speicherung in Variablen übertragen um einen Zwischenspeicher für alle
## ESP zu gewährleisten
@app.route("/",methods=['GET'])
def hello():

        if request.method == 'GET':
                temp = request.args.get('temp')
                if temp:      
                        f = open('temp','w')
                        f.write(str(temp))
                        f.close()
        if request.method == 'GET':
                luft_feucht = request.args.get('luft_feucht')
                if luft_feucht:
                        f = open('luft_feucht','w')
                        f.write(str(luft_feucht))
                        f.close()
        if request.method == 'GET':
                feinstaub = request.args.get('feinstaub')
                if feinstaub:
                        f = open('feinstaub','w')
                        f.write(str(feinstaub))
                        f.close()
                
## Öffnet .csv - Datei, die davor heruntergeladen wurde. Anschließend wird der Inhalt der Datei bearbeitet, sodass nur die relevanten
## Daten ausgegeben werden  
	feinstaub_werte = open("/home/pi/feinstaub_werte").read()
	feinstaub_werte = feinstaub_werte.split()
	feinstaub_werte = feinstaub_werte[len(feinstaub_werte)-1]
	feinstaub_werte = feinstaub_werte.split(";")
	feinstaub_werte = feinstaub_werte[len(feinstaub_werte)-1]
	feinstaub_werte = int(feinstaub_werte)

## wertet die oben gewonnenen Daten aus, um die Bewertung der Luftqualität durch einen Smiley zu gewähren
## wird eventuell noch geändert
	grueneLuft = 20
	if feinstaub_werte<= grueneLuft:
		return "0"

	gelbeLuft = 30
        if feinstaub_werte<= gelbeLuft:
                return "1"

	orangeneLuft = 40
        if feinstaub_werte<= orangeneLuft:
                return "2"
	

    	return "3"

## startet den Webserver auf Port 8080
if __name__ == "__main__":
    app.run('0.0.0.0',8080)
