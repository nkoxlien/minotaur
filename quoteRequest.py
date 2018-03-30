import urllib.request

#Data model for a single request for a stock quote
class QuoteRequest:

	def __init__(self, symbol, function, apiKey):
		self.symbol = symbol
		self.apiKey = apiKey
		functionEnum = Function()
		if function == 1:
			self.function = functionEnum.Daily
		else if function == 2:
			self.function = functionEnum.Intraday
		else:
			self.function = functionEnum.DailyAdjusted

	#Executes an AlphaVantage
	def execute():
		queryString = "https://www.alphavantage.co/query?function=" + function + "&symbol=" + symbol + "&outputsize=full&apikey=" + API_KEY
		respons = urllib.request.urlopen(queryString).read()