import RPi.GPIO as GPIO
import time
import schedule
import pygame.mixer
import threading
import speech_recognition as sr
from inky import InkyPHAT
from PIL import Image, ImageFont, ImageDraw
from font_fredoka_one import FredokaOne
import epd2in7b

def display_text(text):

  #create instance
  inky_display = InkyPHAT(color)

  #set up display
  inky_display.set_border(inky_display.RED)
  inky_display.set_rotation(180)

  #clear the previous display
  inky_display.clear()

  #set up the text
  color = inky_display.BLACK
  font = ImageFont.truetype(FredokaOne, 22)

  #text position
  text_width, text_height = inky_display.text_dimensions(text, font)
  display_width = inky_display.WIDTH
  display_height = inky_display.HEIGHT
  x = (display_width - text_width) // 2
  y = (display_height - text_height) // 2

  #show the text
  inky_display.text((x, y), text, color, font)
  inky_display.show()


def main():
  display_text("hello")

  if __name__ == "__main__":
    main()