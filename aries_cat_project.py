# -*- coding: utf-8 -*-
"""Aries Cat Project

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1bbJIymvakE-qV2BsR0y444ngSwjj12iI

#Imports and Setup
"""

# !pip install RPi.GPIO
# !pip install schedule
# !pip install SpeechRecognition
# !pip install pygame
# !pip install inky
# !sudo pip install einky
# !pip install font-fredoka-one

import RPi.GPIO as GPIO
import time
import schedule
import pygame.mixer
import threading
import speech_recognition as sr
from inky import InkyPHAT
from PIL import Image, ImageFont, ImageDraw
from font_fredoka_one import FredokaOne

"""#Actions Library
Meowing, LED Screen, etc.

### Make Sounds

Different functions that play specific sounds
"""

#sound paths
MEDICATION: "medication.mp3"
SLEEPY: "sleepy.mp3"
FEED_ME: "feed.mp3"


def medication_meow():
  pygame.mixer.init()
  pygame.mixer.music.load(MEDICATION)
  pygame.mixer.music.play()

def sleepy_meow():
  pygame.mixer.init()
  pygame.mixer.music.load(SLEEPY)
  pygame.mixer.music.play()

def feed_meow():
  pygame.mixer.init()
  pygame.mixer.music.load(FEED_ME)
  pygame.mixer.music.play()

"""### E-paper text display
Currently, there is only display text function, which displays the input text -- requires an input string
"""

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

"""### Light up the LED

Currently, there is only one function that turns the LED on for 5 seconds
"""

def led_on():
  LED_PIN = 17 #TODO: add the correct pin number
  DELAY_TIME = 5  #TODO: adjust how long the LED should stay on

  GPIO.setmode(GPIO.BCM)
  GPIO.setup(LED_PIN, GPIO.OUT)

  #turn led on
  GPIO.output(LED_PIN, GPIO.HIGH)
  print("led is on")

  #delay turn off
  time.sleep(DELAY_TIME)

  GPIO.output(LED_PIN, GPIO.LOW)
  print("led is off")

  #clean up
  GPIO.cleanup()

"""# User Engagement and Disengagement

### Monitor and Reward User Engagement

After being touched n times in a certain timespan, the pi should know and react (e.g. by meowing + showing something on the screen + showing an LED pattern = sending a signal).

### Monitor user disengagement and initiate interaction

Patterns of no movement or low touching via the internal clock, when there's lack of activity.  I.e. the opposite of test 1, when the cat hasn't been touched in a long time, it should show a signal, probably an initiation to reconnect.
"""

TOUCH_PIN = 1 #TODO: add the correct pin number
TIME_SPAN = 10 #TODO: adjust the time span
INACTIVITY_TIME = 30 #TODO: adjust the time span


GPIO.setmode(GPIO.BCM)
GPIO.setup(TOUCH_PIN, GPIO.IN)

num_touches = 0
start_time = None
activity_end_time = time.time()


#responses
def respond(touches):
  if touches == 1:
    print("turn on LED screen") #TODO: change print with actions from library
  elif touches == 2:
    print("meow") #TODO: change print with actions from library
  elif touches == 5:
    print("display something") #TODO: change print with actions from library

  #case for disengagement
  elif touches == 10000:
    print("no activity") #TODO: change print with actions from library

#engagement/disengagement monitor
def engagement_monitor():
  global num_touches, start_time, activity_end_time
  while True:
    if GPIO.input(TOUCH_PIN):
      num_touches += 1
      activity_end_time = time.time()
      print("touched")

      if start_time is None:
        start_time = time.time()

    #activity check
    if start_time is not None and time.time() - start_time >= TIME_SPAN:
      #respond
      respond(num_touches)

      #reset
      num_touches = 0
      start_time = None

    #inactivity check
    if time.time() - activity_end_time >= INACTIVITY_TIME:
      respond(10000)

      #reset
      num_touches = 0
      start_time = None
      activity_end_time = time.time()

    #small delay
    time.sleep(0.1)

"""# Announce calendar events

(e.g., from internet messages that Abhay set up). Perhaps even allow the pi to connect to and display events from an online calendar (there are many python libraries for this).
"""

#TODO

"""# Trigger a medication reminder
at a certain time of day.  

"""

reminder_time = "10:00" #adjust

def medication_reminder():
  global reminder_time
  schedule.every().day.at(reminder_time).do(reminder_meow)

  #run continiously
  while True:
    schedule.run_pending()
    time.sleep(1)

"""#Respond to certain verbal inputs.  
Microphone detection of wake words and triggering a certain communicative signal (--> “Processing”).  There are python libraries for raspberry pi that do speech recognition so this is achievable in a very basic way.  We may need the cat’s “name” as a wake word and then a small set of recognized commands or keywords. This doesn't have to be more than proof of concept right now.
"""

# https://github.com/Uberi/speech_recognition/blob/master/examples/microphone_recognition.py

WAKE_WORD = "milo"  #TODO: adjust the name
KEYWORDS = ["sleep", "play", "help"]  #TODO: adjust the commands

#keyword actions
def keyword_act(keyword):
  if keyword == "sleep":
    print("sleeping") #TODO: change print with actions from library
  elif keyword == "play":
    print("playing") #TODO: change print with actions from library
  elif keyword == "help":
    print("display help") #TODO: change print with actions from library


def speech_recognition():
  # obtain audio from the microphone
  r = sr.Recognizer()
  with sr.Microphone() as source:
    print("waiting for wake word")
    audio = r.listen(source)

  try:
    recognized_text = r.recognize_google(audio)
    print("Milo thinks you said " + recognized_text)

    text_split = recognized_text.lower().split()

    if text_split[0] == WAKE_WORD and len(text_split) == 1:
      print("what can Milo do for you") #TODO: change with an action

    elif text_split[0] == WAKE_WORD and len(text_split) > 1:
      keyword = " ".join(words[1:])
      if keyword  in KEYWORDS:
        print("keyword recognized")
        keyword_act(keyword)
      else:
        print("Milo couldn't understand", keyword)

  except sr.UnknownValueError:
    print("Milo could not understand audio")
  except sr.RequestError as e:
    print("Could not request results from Google Speech Recognition service; {0}".format(e))

"""#Battery level monitoring
Low battery, charging - the batteries inside the cat are standard 1.5V C batteries.  They are not connected to the rest of the electronics in a way that we can read their levels.  We can guess (How? What events do we “sum” up to this end?) how long the parts have been on though, and provide an estimate from there. This should trigger a unique icon or message on the display screen along with the “urgent” meow. There is also not a way to charge the cat’s batteries right now, since  the cat is meant to run on disposable batteries.  Achieving this functionality may require a redesign of the entire robot.

The battery that powers the Pi also isn’t directly readable, so we need to have another time- or activity-based estimate there.  We have the charging bed and have a unique signature (meow + screen + LED) of asking for being charged  
"""

#TODO

"""#Main Code"""

def main():
  try:
    #engagement/disengagement monitor
    engagement_monitor_thread = threading.Thread(target=engagement_monitor)
    engagement_monitor_thread.start()

    #calendar event

    #medication reminder
    medication_reminder_thread = threading.Thread(target=medication_reminder)
    medication_reminder_thread.start()

    #speech recognition
    speech_recognition_thread = threading.Thread(target=speech_recognition)
    speech_recognition_thread.start()

    #battery level

    #wait until threads finish
    engagement_monitor_thread.join()

    medication_reminder_thread.join()
    speech_recognition_thread.join()


  except KeyboardInterrupt:
    GPIO.cleanup()
    pygame.mixer.quit()

if __name__ == "__main__":
    main()