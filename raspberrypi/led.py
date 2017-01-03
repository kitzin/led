from struct import Struct

class Led:
	version = 0
	pins = 0
	red = 0
	green = 0
	blue = 0

	def __init__(self):
		self.packer = Struct("4B")
	def _values(self):
		return ((self.version << 1 | self.pins), self.red, self.green, self.blue)

	def pack(self):
		return self.packer.pack(*self._values())
