# Python script to passively monitor a motiona sensor that
# will take a picture using the Pi Camera and label the image
# with the date and time for organisation

# Importing the required library elements
from time     import sleep
from gpiozero import MotionSensor
from picamera import PiCamera
from signal   import pause

import os
import datetime

# Defining the different resurces that are used
camera = PiCamera()
sensor = MotionSensor(4)

# Initializing the camera
camera.resolution = (1024, 768)
camera.rotation = 90
camera.start_preview()
sleep(2)

# Wait for the motion sensor to finish powering on
sleep(1)
print("ready")
# A function to take a picture and appropriately store it
# with the date and time
def take_pic():
  print("MOTION!")
  date = datetime.datetime.now()
  day  = date.strftime("%d-%m-%Y")
  time = date.strftime("%H:%M:%S")
  try:
    os.mkdir("/home/pi/{}".format(day))
  except FileExistsError:
    pass
  file_location = "/home/pi/{}/{}.jpg".format(day, time)
  camera.capture(file_location)

# When the sensor detects motion, it will call the function
# to take a picture
sensor.when_motion = take_pic

# Pauses the system to run the script indefinatly
pause()
