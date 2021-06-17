from flask import Flask, render_template,Response
import serial
from flask_socketio import SocketIO,send,emit,disconnect
import time
from cv2 import cv2
arduino = serial.Serial('/dev/ttyACM0',9600)
#arduino = serial.Serial('COM4',9600)
app=Flask(__name__)
camera = cv2.VideoCapture(0)
socketio = SocketIO(app, cors_allowed_origins='*')
@socketio.on('connect')
def test_control():
    print("nadhem connecte")


@socketio.on('get')
def marche(a):
    print("aaaaaaaaaa,,,,,,,,,,,,,,,,,,aaaaaaaaaaaaaaaaaaaaaaaaaaaaa")
    msg=a['status']
    arduino.write(msg.encode()) 
    print(a['status'])
    socketio.emit("b",1)
    line = arduino.readline().decode('utf-8').rstrip()
    print(line)
    time.sleep(0.1)     
@app.route('/')
def hello_world():
   # arduino.write(msg.encode())
   # socketio.emit("b",1)
    

    return render_template('index.html')
def gen_frames():
    while True:
        success, frame = camera.read()  # read the camera frame
        if not success:
            break
        else:
            ret, buffer = cv2.imencode('.jpg', frame)
            frame = buffer.tobytes()
            yield (b'--frame\r\n'
                   b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n') 
		 # concat frame one by one and show result
@app.route('/video_feed')
def video_feed():
    return Response(gen_frames(), mimetype='multipart/x-mixed-replace; boundary=frame')

if __name__ == '__main__':
   app.run(debug=True)
