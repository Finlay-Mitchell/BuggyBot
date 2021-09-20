import cv2
import numpy as np

if __name__ == "__main__":
    cap = cv2.VideoCapture("http://192.168.0.21:81/stream")
    cv2.namedWindow("image")

    if not cap.isOpened():
        print("Error opening capture device")
        exit()


    while 1:
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

        ret, img = cap.read()
