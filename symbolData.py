import json
from dailyData import DailyData

# Model for a collection of market data for a symbol
class SymbolData:

	# List of all daily data for the symbol
	@property
	def dailyData(self):
		return self.__dailyData

	# Populate the dailyData property
	def __populateDailyData(self, dailyMarketData):
		for day in dailyMarketData:
			dayOpen = dailyMarketData[day]["1. open"]
			dayHigh = dailyMarketData[day]["2. high"]
			dayLow = dailyMarketData[day]["3. low"]
			dayClose = dailyMarketData[day]["4. close"]
			dayVolume = dailyMarketData[day]["5. volume"]
			dayData = DailyData(day, dayOpen, dayHigh, dayLow, dayClose, dayVolume)
			
			self.__dailyData.append(dayData)



	# Parse a raw response
	def __parseResponse(self, rawDailyQuoteResponse):
		data = json.loads(rawDailyQuoteResponse)
		dailyMarketData = data["Time Series (Daily)"]
		self.__populateDailyData(dailyMarketData)

	# Takes the raw response from QuoteRequest.execute() and
	# converts the data into a more readable format
	def __init__(self, symbol, rawDailyQuoteResponse):
		self.symbol = symbol
		self.__dailyData = list()
		self.__parseResponse(rawDailyQuoteResponse)


	