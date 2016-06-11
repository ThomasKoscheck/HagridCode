#!/usr/bin/python
from flask import Flask
app = Flask(__name__)

@app.route("/")
def hello():
	feinstaub_werte = open("feinstaub_werte").read()
	feinstaub_werte = feinstaub_werte.split()
	feinstaub_werte = feinstaub_werte[len(feinstaub_werte)-1]
	feinstaub_werte = feinstaub_werte.split(";")
	feinstaub_werte = feinstaub_werte[len(feinstaub_werte)-1]
	feinstaub_werte = int(feinstaub_werte)


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

if __name__ == "__main__":
    app.run(host = '0.0.0.0')
