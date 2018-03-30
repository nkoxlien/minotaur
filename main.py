import quoteRequest.py

API_KEY = "apikey"

#Grab the symbol from the user and return it
def getSymbol():
	return raw_input("Enter ticker: ")

#Grab the type of data to query
def getFunction():
	invalid = True
	function = ""
	
	while(invalid):
		function = input("Enter quote type (1. daily, 2. intraday, 3. daily adjusted): ")	
		if(function < 1 or function > 3):
			print "Invalid type.\n"
		else:
			invalid = False

	return function

symbol = getSymbol()

if len(symbol > 0):
	function = getFunction()
	request = QuoteRequest(symbol, function, API_KEY)