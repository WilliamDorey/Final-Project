# Importing libraries
import serial
import sys

# Define Serial port and variable
port = serial.Serial("/dev/ttyS0", baudrate=2400)
out = sys.argv[1]

# Output the desired value
port.write(out)

# Recieve and display string of values from the
# serial connection
print("\r\nYou Recieved:")
length = port.read()
port.write("1")
i = ord(length)
rcv = ""
while i != 0:
  rcv += port.read()
  port.write('1')
  i = i-1
print(rcv)
