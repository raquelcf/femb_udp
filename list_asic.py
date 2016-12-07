#!/usr/bin/env python33

import sys 
import string
from femb_udp_cmdline import FEMB_UDP

femb = FEMB_UDP()

# Read ADC serial data write buffer
print "ADC serial data write buffer"
for reg in range (0x200, 0x224, 1):
  val = femb.read_reg_i2c(reg)
  print str(hex(reg)) + "\t" + str(hex(val))

print
print "ADC serial data read back"

# Read ADC serial data, read back buffer
for reg in range (0x228, 0x24C, 1):
  val = femb.read_reg(reg)
  print str(hex(reg)) + "\t" + str(hex(val))



# Read FE serial data write buffer
print "FE serial data write buffer"
for reg in range (0x250, 0x274, 1):
  val = femb.read_reg(reg)
  print str(hex(reg)) + "\t" + str(hex(val))

print
print "FE serial data read back"

# Read FE serial data, read back buffer
for reg in range (0x278, 0x29C, 1):
  val = femb.read_reg_i2c(reg)
  try:
    print str(hex(reg)) + "\t" + str(hex(val))
  except:
    print str(hex(reg)) + "\t" + str(val)

