# stream.py
import cv2
from flask import Flask, Response

app = Flask(__name__)
cap = cv2.VideoCapture(2, cv2.CAP_DSHOW)

def generate():
    while True:
        ret, frame = cap.read()
        if not ret:
            continue
        ret, buffer = cv2.imencode('.jpg', frame)
        frame = buffer.tobytes()
        yield (b'--frame\r\nContent-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')

@app.route('/video')
def video():
    return Response(generate(), mimetype='multipart/x-mixed-replace; boundary=frame')

app.run(host='0.0.0.0', port=8080)