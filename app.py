from flask import Flask, render_template, Response, jsonify, request, redirect, url_for, session
import serial
from cv2 import cv2
import time
arduino = serial.Serial('/dev/ttyACM0', 9600)
#arduino = serial.Serial('COM3',9600)
app = Flask(__name__)
camera = cv2.VideoCapture(0)
app.secret_key = "125478"
@app.route("/getDist", methods=['POST'])
def getDist():

    msg =request.form['direction']
    arduino.write(msg.encode())

    dist=arduino.readline().decode('utf-8').rstrip()
   
    return jsonify({'dist': dist})



@app.route('/process', methods=['POST'])
def process():
    msg=request.form['direction']
    arduino.write(msg.encode())
    return jsonify({'ok': msg})

@app.route("/")
@app.route("/index")
def root():
    print("server time : ", time.strftime('%A %B, %d %Y %H:%M:%S'))
    if 'visit' in session:

        return render_template('index.html')
    else:
        return redirect(url_for('login'))


@app.route('/login', methods=['GET','POST'])
def login():

    if request.method=='POST':
        codeInv = request.form['codeInv']
        if codeInv =='123456':
            session['visit'] ="visiteur"
            return redirect(url_for('root'))
        else:

            return render_template('login.html', x='votre code est incorrect. veuillez le verifier')
    else:
        if (session.get('visit')) :

            return redirect(url_for('root'))
        else:
            return render_template('login.html')


def gen_frames(camera):
    while True:

        success, image = camera.read()  
        ret, buffer = cv2.imencode('.jpg', image)
        frame = buffer.tobytes()


        yield (b'--frame\r\n'
               b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')
        
@app.route('/dec')
def dec():

    session.clear()
    return redirect(url_for('login'))

@app.route('/video_feed')
def video_feed():
    global video

    return Response(gen_frames(camera), mimetype='multipart/x-mixed-replace; boundary=frame')

if __name__ == '__main__':
    app.run(debug=True)
