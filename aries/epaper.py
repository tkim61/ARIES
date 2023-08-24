import sys
import os
picdir = os.path.join(os.path.dirname(os.path.dirname(os.path.realpath(__file__))), 'pic')
libdir = os.path.join(os.path.dirname(os.path.dirname(os.path.realpath(__file__))), 'lib')
if os.path.exists(libdir):
    sys.path.append(libdir)

import logging
from waveshare_epd import epd2in13_V3
import time
from PIL import Image,ImageDraw,ImageFont
import traceback

logging.basicConfig(level=logging.DEBUG)

#try:
 #   logging.info("epd2in13_V3  TESTING ")
  #  
   # epd = epd2in13_V3.EPD()
    #logging.info("init and Clear")
    #epd.init()
    #epd.Clear(0xFF)

   # logging.info("clear over") 
   # time.sleep(3)   
# Drawing on the image
  #  blackbird = Image.open('var/www/html/Scripts/eink.jpg')
#    font24 = ImageFont.truetype(os.path.join(picdir, 'Font.ttc'), 24)
    
 #   logging.info("1.Drawing on the image...")
   # image = Image.new('1', (epd.width, epd.height), 255)  # 255: clear the frame    
   # draw = ImageDraw.Draw(image)
 #   image.paste(blackbird, (0,0)
  #  EPD.EPD(EPD.getbuffer(image))

#from waveshare_epd import epd2in13


try:

    epd = epd2in13_V3.EPD()
    epd.init()
    epd.Clear(0)
	
    w = epd.height
    h = epd.width
    print('width:',w)
    print('height:',h)

    time.sleep(3)
    image1 = Image.new('1', (epd.height, epd.width), 255)
    blackbird = Image.open('/var/www/html/eink.jpg')
    image1.paste(blackbird,(0, 0))
    epd.display(epd.getbuffer(image1))

except IOError as e:
    print(e)


