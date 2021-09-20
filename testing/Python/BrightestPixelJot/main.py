import cv2
import numpy as np


class imgPos:
    def __init__(self):
        self.__debugVerbosity = 0

    def log(self, data):
        if self.__debugVerbosity == 0:
            print(f"[log] -> {data}")
        elif self.__debugVerbosity == 1:
            print(f"[warning] -> {data}")
        else:
            print(f"[important] ->")

    @staticmethod
    def brightest_pixel_blob(image):
        img = image.copy()
        hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
        h, s, v = cv2.split(hsv)
        limit = v.max()
        hsv_min = np.array((0, 0, limit), np.uint8)
        hsv_max = np.array((255, 255, limit), np.uint8)
        img = cv2.inRange(hsv, hsv_min, hsv_max)
        moments = cv2.moments(img, 1)
        x_moment = moments['m01']
        y_moment = moments['m10']
        area = moments['m00']
        x = int(x_moment / area)
        y = int(y_moment / area)
        cv2.imshow("blob", img)

    @staticmethod
    def average_brightest_position(image):
        img = image.copy()
        min_val, max_val, min_loc, max_loc = cv2.minMaxLoc(cv2.cvtColor(img, cv2.COLOR_BGR2GRAY))
        cv2.circle(img, max_loc, 5, (0, 255, 0), 2)
        gray = cv2.GaussianBlur(cv2.cvtColor(img, cv2.COLOR_BGR2GRAY), (41, 41), 0)
        min_val, max_val, min_loc, max_loc = cv2.minMaxLoc(gray)
        # cv2.circle(img, maxLoc, 41, (255, 0, 0), 2)
        cv2.drawMarker(img, max_loc, (0, 0, 255), 1080, 1920)
        cv2.circle(img, max_loc, 5, (0, 0, 255), 4)
        cv2.imshow("Cross", img)


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
        orig = img.copy()
        cv2.imshow("image", img)

        imgPos.average_brightest_position(orig)
        imgPos.brightest_pixel_blob(orig)

    cap.release()
    cv2.destroyAllWindows()
