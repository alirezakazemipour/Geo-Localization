from PyQt5.QtCore import QByteArray as qb
from PyQt5.QtNetwork import QUdpSocket,QHostAddress
from PyQt5.QtCore import QIODevice as io
from PyQt5.QtCore import *
import numpy as np
import cv2
import  sys


bf = cv2.BFMatcher()
sift = cv2.xfeatures2d.SIFT_create() # opencv 3
I1 = cv2.imread('/home/alireza/Documents/Geo-Localization/map.jpg')
G1 = cv2.cvtColor(I1,cv2.COLOR_BGR2GRAY)
keypoints1, desc1 = sift.detectAndCompute(G1, None); # opencv 3


img_port=1234


send_data_socket=QUdpSocket()
ROBOT_IP = QHostAddress("127.0.0.1")
ROBOT_data_port=5678

def receive_data():

    print("image Rec")
    datagram = qb()
    datagram.resize(rec_data_socket.pendingDatagramSize())
    datagram, host, port=rec_data_socket.readDatagram(datagram.size())
    datagram=qb(datagram)
    rec_data_socket.flush()
    buf=np.asarray(bytearray(datagram),dtype=np.uint8)
    mat=cv2.imdecode(buf,cv2.IMREAD_COLOR)
    datagram.clear()

    find_match(mat)


def find_match(x):

    # cv2.imshow("x",x)

    window = x

    keypoints2, desc2 = sift.detectAndCompute( window, None );  # opencv 3

    matches = bf.knnMatch( desc1, desc2, k=2 )
    # matches = flann.knnMatch(desc1, desc2 ,k=2)
    good_matches = []
    points = []
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
    try:
        H, mask = cv2.findHomography( points1, points2, cv2.RANSAC, 5.0 )  # 5 pixels margin
        mask = mask.ravel().tolist()

        # print( mask )

        cx = 0
        cy = 0
        for k in range( len( points[0] ) ):
            # cv2.circle(I1,(int(points[0][k][0]),int(points[0][k][1])),2,(0,0,255),-1)
            cx += int( points[0][k][0] )
            cy += int( points[0][k][1] )
        cx = cx // len( points[0] )
        cy = cy // len( points[0] )
    except:
        cx = cy =0
        sendLocation(cx,cy)


def sendLocation(x,y):

    d=int(np.sqrt(x*x+y*y))
    datagram=qb()
    SendDataPacket = QDataStream(datagram,io.WriteOnly)
    StartPacket = qb(1,"S")
    SendDataPacket << StartPacket
    SendDataPacket.writeInt(d)
    send_data_socket.writeDatagram( datagram, ROBOT_IP, ROBOT_data_port )
    send_data_socket.flush()
    print( "Data sent" )
    datagram.clear()



if __name__=="__main__":

    app = QCoreApplication(sys.argv)
    print("program started")
    rec_data_socket = QUdpSocket()
    rec_data_socket.bind(img_port)
    rec_data_socket.readyRead.connect(receive_data)

app.exec_()