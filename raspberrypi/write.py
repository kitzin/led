from smbus import SMBus
from led import Led

bus = SMBus(1)
ADDRESS = 0x05

def write_bytes(b):
	bus.write_i2c_block_data(ADDRESS, 0, [int(d) for d in b])

l = Led()
l.red = 0
l.green = 0
l.blue = 0
l.pins = 0
l.version = 50

write_bytes(l.pack())

"""

version = 7 bit
pins = 1 bit
red = 1 byte
green = 1 byte
blue = 1 byte

"""
