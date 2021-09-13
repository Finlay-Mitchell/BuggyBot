import cv2


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
        minVal, maxVal, minLoc, maxLoc = cv2.minMaxLoc(cv2.cvtColor(img, cv2.COLOR_BGR2GRAY))
        cv2.circle(img, maxLoc, 5, (0, 255, 0), 2)
        gray = cv2.GaussianBlur(cv2.cvtColor(img, cv2.COLOR_BGR2GRAY), (41, 41), 0)
        minVal, maxVal, minLoc, maxLoc = cv2.minMaxLoc(gray)
        # cv2.circle(img, maxLoc, 41, (255, 0, 0), 2)
        cv2.drawMarker(img, maxLoc, (0, 0, 255), 1080, 1920)
        cv2.circle(img, maxLoc, 5, (0, 0, 255), 4)
        cv2.imshow("Cross", img)

    cap.release()
    cv2.destroyAllWindows()
