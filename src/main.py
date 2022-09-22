import serial
from influxdb import InfluxDBClient
import time
import signal
import utils

ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
SHUTDOWN = False

def signal_handler(signal,frame):
   global SHUTDOWN
   SHUTDOWN = True
   ser.close()
   print('Exiting...')

signal.signal(signal.SIGINT, signal_handler)

client = InfluxDBClient(host = 'influx', port = 8086, username = 'python', password = 'python')


while not SHUTDOWN:
   
   line =  str(ser.readline().decode('ascii'))
   if(len(line)!=0):
      data= utils.parse_string(line)
      print(data)
      client.write_points(data, database = 'progetto', protocol = 'json')
   
   
   time.sleep(5)
