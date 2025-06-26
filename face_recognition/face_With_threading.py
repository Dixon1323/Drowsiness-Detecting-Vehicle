import cv2
from deepface import DeepFace
import threading

cap = cv2.VideoCapture(0, cv2.CAP_DSHOW)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)

face_match = False
reference_img = cv2.imread("reference.jpg")

def check_face(frame):
    global face_match
    try:
        if DeepFace.verify(frame, reference_img)['verified']:
            face_match = True
        else:
            face_match = False
    except ValueError:
        pass

def process_frames():
    while True:
        ret, frame = cap.read()
        if ret:
            check_face(frame)
            key = cv2.waitKey(1)
            if key == ord("q"):
                break
        else:
            break

def display_frames():
    while True:
        ret, frame = cap.read()
        if ret:
            if face_match:
                cv2.putText(frame, "MATCH!", (20, 450), cv2.FONT_HERSHEY_SCRIPT_SIMPLEX, 2, (0, 255, 0), 3)
            else:
                cv2.putText(frame, "NO MATCH!", (20, 450), cv2.FONT_HERSHEY_SCRIPT_SIMPLEX, 2, (0, 0, 255), 3)

            cv2.imshow("video", frame)

            key = cv2.waitKey(1)
            if key == ord("q"):
                break
        else:
            break

threading.Thread(target=process_frames).start()
threading.Thread(target=display_frames).start()

cv2.destroyAllWindows()
