from flask import Flask, render_template,Response
import serial
from flask_socketio import SocketIO,send,emit
import time
import cv2
arduino = serial.Serial('COM4',9600)
app=Flask(__name__)
socketio = SocketIO(app, cors_allowed_origins='*')
@socketio.on('connect')
def test_control():
    print("nadhem connecte")

@socketio.on('get')
def test_control1(a):
    print(a['status'])
    msg=a['status']
    arduino.write(msg.encode())


@app.route('/')
def hello_world():
    msg='F'
    arduino.write(msg.encode())
    socketio.emit("b",1)

    """Video streaming route. Put this in the src attribute of an img tag."""
    return render_template('index.html')

@app.route('/video_feed')
def video_feed():
    return Response(gen(),
                    mimetype='multipart/x-mixed-replace; boundary=frame')
def gen():
    """Video streaming generator function."""
    cap = cv2.VideoCapture('http://192.168.1.18:8080/video')

    # Read until video is completed
    while (cap.isOpened()):
        # Capture frame-by-frame
        ret, img = cap.read()
        if ret == True:
            img = cv2.resize(img, (0, 0), fx=0.5, fy=0.5)
            frame = cv2.imencode('.jpg', img)[1].tobytes()
            yield (b'--frame\r\n'b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')
            time.sleep(0.1)
        else:
            break

if __name__ == '__main__':
   app.run()