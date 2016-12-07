#!/usr/bin/env python33

import sys 
import importlib
import os
import string
from femb_udp_cmdline import FEMB_UDP
import socket
import struct
import datetime
import uuid
#from femb_config import FEMB_CONFIG
import time
from femb_rootdata import FEMB_ROOTDATA
import math

#femb_config = FEMB_CONFIG()

#from setup_gui import *
#from setup_config import *

config_type = os.environ["CONFIG_TYPE"]
mod = "femb_config_" + config_type
config = importlib.import_module(mod)

femb_config = config.FEMB_CONFIG()


def calcMeanAndRms( data ):
        mean = 0
        count = 0
        for samp in data:
                if (samp & 0x3F) == 0x0 or (samp & 0x3F) == 0x3F:
                        continue
                mean = mean + int(samp)
                count = count + 1
        if count > 0 :
                mean = mean / float(count)
        else:
                mean = 0

	rms = 0
	count = 0
	for samp in data:
                if (samp & 0x3F) == 0x0 or (samp & 0x3F) == 0x3F:
                        continue
		rms = rms + (samp - mean)*(samp-mean)
		count = count + 1
	if count > 1 :
                rms = math.sqrt( rms / float(count - 1 ) )
        else:
                rms = 0

        return (mean,rms)

noiseMeasurements = []
for ch in range(0,128,1):
	chan = int(ch)
        femb_config.selectChannel( chan/16, chan % 16, 1)
        time.sleep(0.05)
        data = femb_config.femb.get_data()
	meanAndRms = calcMeanAndRms(data)
	rms = 0
	if len(meanAndRms) == 2 :
		rms = round(meanAndRms[1],2)
	#print meanAndRms[0]
	#print meanAndRms[1]
	#print "Ch " + str(ch) + "\tRMS " + str(rms)
	noiseMeasurements.append(rms)

for asic in range(0,8,1):
	line = "ASIC " + str(asic)
	baseCh = int(asic)*16
	for ch in range(baseCh,baseCh + 16,1):
		line = line + "\t" + str( noiseMeasurements[ch])
	print line
