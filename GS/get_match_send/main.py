from PyQt5.QtCore import QByteArray as qb
from PyQt5.QtNetwork import QUdpSocket,QHostAddress
import sys,PyQt5.QtCore
from PyQt5.QtCore import *
import numpy as np
import cv2


bf = cv2.BFMatcher()
sift = cv2.xfeatures2d.SIFT_create() # opencv 3
I1 = cv2.imread('/home/alireza/Documents/Geo-Localization/map.jpg')
G1 = cv2.cvtColor(I1,cv2.COLOR_BGR2GRAY)
keypoints1, desc1 = sift.detectAndCompute(G1, None); # opencv 3


data_port=1234

def receive_data():
    print("image Rec")
    datagram = qb()
    datagram.resize(rec_data_socket.pendingDatagramSize())
    datagram, host, port=rec_data_socket.readDatagram(datagram.size())
    datagram=qb(datagram)
    rec_data_socket.flush()
    buf=np.asarray(bytearray(datagram),dtype=np.uint8)
    mat=cv2.imdecode(buf,cv2.CV_LOAD_IMAGE_COLOR)
    datagram.clear()
    cv2.imshow("frame",mat)
    find_match(mat)


def find_match(x):

    window = x

    keypoints2, desc2 = sift.detectAndCompute( window, None );  # opencv 3

    matches = bf.knnMatch( desc1, desc2, k=2 )
    # matches = flann.knnMatch(desc1, desc2 ,k=2)
    good_matches = []
    alpha = 0.25
    for m1, m2 in matches:
        # m1 is the best match
        # m2 is the second best match
        if m1.distance < alpha * m2.distance:
            good_matches.append( m1 )

    # apply RANSAC
    points1 = [keypoints1[m.queryIdx].pt for m in good_matches]
    points1 = np.array( points1, dtype=np.float32 )

    points2 = [keypoints2[m.trainIdx].pt for m in good_matches]
    points2 = np.array( points2, dtype=np.float32 )
    H, mask = cv2.findHomography( points1, points2, cv2.RANSAC, 5.0 )  # 5 pixels margin
    mask = mask.ravel().tolist()
    # print( mask )

    good_matches = [m for m, msk in zip( good_matches, mask ) if msk == 1]

    I = cv2.drawMatches( I1, keypoints1, window, keypoints2, good_matches, None, flags=2 )
    cv2.imshow( "result", I )
    cv2.waitKey( 0 )


if __name__=="__main__":

  app = QCoreApplication(sys.argv)
  print("program started")
  rec_data_socket = QUdpSocket()
  rec_data_socket.bind(data_port)
  # QObject.connect(rec_data_socket, SIGNAL("readyRead(PyQt_PyObject)"), receive_data)
  rec_data_socket.readyRead.connect(receive_data)

app.exec_()