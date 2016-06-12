#!/usr/bin/python
from flask import Flask
from flask import request
app = Flask(__name__)

@app.route("/temp")
def type1():
	f = open("temp").read()
	return f

@app.route("/luftfeucht")
def type2():
        f = open("luftfeucht").read()
        return f

@app.route("/feinstaub")
def type3():
        f = open("feinstaub").read()
        return f
@app.route("/feinstaub")
def type4():
        feinstaub_werte = open("luftquali").read()
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


@app.route("/",methods=['GET'])
def hello():

        if request.method == 'GET':
                temp = request.args.get('temp')
                if temp:      
                        f = open('temp','w')
                        f.write(str(temp))
                        f.close()
        if request.method == 'GET':
                luft_feucht = request.args.get('luftfeucht')
                if luft_feucht:
                        f = open('luftfeucht','w')
                        f.write(str(luftfeucht))
                        f.close()
        if request.method == 'GET':
                feinstaub = request.args.get('feinstaub')
                if feinstaub:
                        f = open('feinstaub','w')
                        f.write(str(feinstaub))
                        f.close()
        if request.method == 'GET':
                feinstaub = request.args.get('luftquali')
                if feinstaub:
                        f = open('luftquali','w')
                        f.write(str(feinstaub))
                        f.close()        
                
        
	feinstaub_werte = open("/home/pi/feinstaub_werte").read()
	feinstaub_werte = feinstaub_werte.split()
	feinstaub_werte = feinstaub_werte[len(feinstaub_werte)-1]
	feinstaub_werte = feinstaub_werte.split(";")
	feinstaub_werte = feinstaub_werte[len(feinstaub_werte)-1]
	feinstaub_werte = int(feinstaub_werte)
	f = open('feinstaub','w');
	f.write(str(feinstaub_werte))
	f.close()
	


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
    app.run('0.0.0.0',8080)
