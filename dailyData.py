
# Model for a single day of market data for a symbol
class DailyData:

	@property
	def day(self):
		return self.__day

	@day.setter	
	def day(self, value):
		self.__day = value

	@property
	def priceOpen(self):
		return self.__priceOpen

	@priceOpen.setter
	def priceOpen(self, value):
		self.__priceOpen = priceOpen

	@property
	def high(self):
		return self.__high

	@high.setter
	def high(self, value):
		self.__high = high

	@property
	def low(self):
		return self.__low

	@low.setter
	def low(self, value):
		self.__low = low

	@property
	def priceClose(self):
		return self.__priceClose

	@priceClose.setter
	def priceClose(self, value):
		self.__priceClose = priceClose

	@property
	def volume(self):
		return self.__volume

	@volume.setter
	def volume(self, value):
		self.__volume = volume

	def __init__(self, day, priceOpen, high, low, priceClose, volume):
		self.__day = day
		self.__priceOpen = priceOpen
		self.__high = high
		self.__low = low
		self.__priceClose = priceClose
		self.__volume = volume