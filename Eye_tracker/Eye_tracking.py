"""
Demonstration of the GazeTracking library.
Check the README.md for complete documentation.
"""

import cv2
from gaze_tracking import GazeTracking
import serial
import time

gaze = GazeTracking()
webcam = cv2.VideoCapture(0)
arduino = serial.Serial(port='COM7', baudrate=115200, timeout=.1)

def send_data(x):
    arduino.write(bytes(x,  'utf-8'))
    time.sleep(0.1)
    #print(bytes(x,  'utf-8'))
    
def read_data():
    data = arduino.readline()
    print(data)


while True:
    # We get a new frame from the webcam
    _, frame = webcam.read()

    # We send this frame to GazeTracking to analyze it
    gaze.refresh(frame)

    frame = gaze.annotated_frame()
    text = ""

    if gaze.is_blinking():
        text = "Blinking"
        send_data('1')
    elif gaze.is_right():
        text = "Looking right"
        send_data('2')
    elif gaze.is_left():
        text = "Looking left"
        send_data('3')
    elif gaze.is_center():
        text = "Looking center"
        send_data('0')
    #send_data('\r\n')
    time.sleep(0.05)
    print(text)
    #read_data()
    cv2.putText(frame, text, (90, 60), cv2.FONT_HERSHEY_DUPLEX, 1.6, (147, 58, 31), 2)

    left_pupil = gaze.pupil_left_coords()
    right_pupil = gaze.pupil_right_coords()
    cv2.putText(frame, "Left pupil:  " + str(left_pupil), (90, 130), cv2.FONT_HERSHEY_DUPLEX, 0.9, (147, 58, 31), 1)
    cv2.putText(frame, "Right pupil: " + str(right_pupil), (90, 165), cv2.FONT_HERSHEY_DUPLEX, 0.9, (147, 58, 31), 1)

    cv2.imshow("Demo", frame)

    if cv2.waitKey(1) == 27:
        break
   
webcam.release()
cv2.destroyAllWindows()
