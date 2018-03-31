import urllib2
from functions import Functions

#Data model for a single request for a stock quote
class QuoteRequest:

	def __init__(self, symbol, function, apiKey):
		self.symbol = symbol
		self.apiKey = apiKey
		functionEnum = Functions()
		if function == 1:
			self.function = functionEnum.Daily
		elif function == 2:
			self.function = functionEnum.Intraday
		else:
			self.function = functionEnum.DailyAdjusted

	#Executes an AlphaVantage API request
	def execute(self):
		queryString = "https://www.alphavantage.co/query?function=" + self.function + "&symbol=" + self.symbol + "&outputsize=full&apikey=" + self.apiKey
		response = urllib2.urlopen(queryString).read()
		return response