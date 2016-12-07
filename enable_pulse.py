#!/usr/bin/env python33

import sys
import importlib
import os

config_type = os.environ["CONFIG_TYPE"]
mod = "femb_config_" + config_type
config = importlib.import_module(mod)

femb_config = config.FEMB_CONFIG()

#Configure values for pulser mode, gain, shape, base
#argv[1] = pulse mode = srcflag
#argv[2] = chip number (pulse by chip/channel only, option argv[1]==2 )
#argv[3] = channel number (pulse by chip/channel only, option argv[1]==2)
#argv[4] = gain
#argv[5] = shape
#argv[6] = base

#Configures board in test pulse mode
#srcflag = 0 means external input is enabled
#srcflag = 1 means internal FPGA DAC is enabled with default settings
#srcflag = 2 calls Raquel's modifications to enable DAC channel-by-channel
#srcflag = 99 means turn it off

### work in progress doesn't like number of arguments...

if config_type == 'sbnd':

    #if len(sys.argv) < 5:
     #   print "Invalid number of arguments, usage: python enable_pulse.py <SOURCEFLAG> <gain> <shape> <base> (+ 2 optional for chip and channel)"
    if len(sys.argv) > 7:
        print "Invalid number of arguments, usage: python enable_pulse.py <SOURCEFLAG> <chip> <channel> <gain> <shape> <base>  (chip and channel only used if <SOURCEFLAG>==2)"
    if len(sys.argv) < 7:
        print "Invalid number of arguments, usage: python enable_pulse.py <SOURCEFLAG> <chip> <channel> <gain> <shape> <base>  (chip and channel only used if <SOURCEFLAG>==2)"
   # if len(sys.argv) != 5:
  #  if len(sys.argv) != 2:
    #    print "Invalid number of arguments, usage: python enable_pulse.py <SOURCEFLAG> <gain> <shape> <base>  "
   # else:
    #    femb_config.enablePulseMode(sys.argv[1])      
   # if len(sys.argv) == 5:
    #    if sys.argv[1] ==2:
     #       raise RuntimeError("Invalid number of arguments for chip and channel ")
      #  else:
       #     femb_config.enablePulseMode(sys.argv[1],0,0)   
        #    print "Internal pulse mode for all channels"     

    if len(sys.argv) == 7:
        try:
          args = map(int, sys.argv[1:])
        except ValueError, e:
          raise RuntimeError("Arguments need to be integers!!! (%s)" % str(e))
        if args[0] !=2:
            print "Pulse mode (external or internal, at all channels"
            #raise RuntimeError("Invalid flag for chip and channel pulse mode ")
            femb_config.enablePulseMode(sys.argv[1],sys.argv[2],sys.argv[3])
        else:
            #femb_config.enablePulseModebychannel(args[1],args[2]) 
            #femb_config.enablePulseModebychannel(sys.argv[2],sys.argv[3]) 
            femb_config.enablePulseMode(sys.argv[1],sys.argv[2],sys.argv[3]) 
            print "Internal pulse mode for single channel"     
