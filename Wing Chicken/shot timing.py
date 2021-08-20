import cv2
import socket
import numpy as np

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

cap = cv2.VideoCapture(0)
_, def1 = cap.read()
while True:
    _, frame = cap.read()

    lo=np.array([0,0,0])
    uo=np.array([100,150,255])
    x = 290;    y = 160;    w = 60;    h = 320  # roi 좌표
    roi = frame[y:y + h, x:x + w]  # roi 지정        ---①
    hsv = cv2.cvtColor(roi, cv2.COLOR_BGR2HSV)
    mask_o = cv2.inRange(hsv, lo, uo)
    res = cv2.bitwise_and(roi, roi, mask=mask_o)
    if np.sum(res)>0 :
        a='1'
        sock.sendto(a.encode(), ('127.0.0.1', 7777))
    else :
        print("000")

    cv2.imshow('o',res)

    if cv2.waitKey(1) & 0xff == ord('q'):
        break
cv2.destroyAllWindows()
