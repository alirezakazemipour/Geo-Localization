import numpy as np
import cv2
import glob


bf = cv2.BFMatcher()
flann =cv2.FlannBasedMatcher()
sift = cv2.xfeatures2d.SIFT_create() # opencv 3
I1 = cv2.imread('/home/alireza/Documents/Geo-Localization/map.jpg')
G1 = cv2.cvtColor(I1,cv2.COLOR_BGR2GRAY)
I_copy = I1.copy()
keypoints1, desc1 = sift.detectAndCompute(G1, None); # opencv 3
fnames=glob.glob("/home/alireza/Documents/Geo-Localization/slidingWindows/*.jpg")
fnames.sort()

cv2.namedWindow("result",cv2.WINDOW_NORMAL)
cv2.namedWindow("distance",cv2.WINDOW_NORMAL)

for fname in fnames:
        # print(fname)
        window=cv2.imread(fname,cv2.COLOR_BGR2GRAY)

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
        points.append(points1)
        H, mask = cv2.findHomography( points1, points2, cv2.RANSAC, 5.0 )  # 5 pixels margin
        mask = mask.ravel().tolist()
        # print( mask )

        good_matches = [m for m, msk in zip( good_matches, mask ) if msk == 1]
        I = cv2.drawMatches( I1, keypoints1, window, keypoints2, good_matches,None,flags=2 )
        cv2.imshow("result",I)
        cx=0
        cy=0

        for k in range(len(points[0])):
            # cv2.circle(I1,(int(points[0][k][0]),int(points[0][k][1])),2,(0,0,255),-1)
            cx+=int(points[0][k][0])
            cy+=int(points[0][k][1])
        cx=cx//len(points[0])
        cy=cy//len(points[0])
        cv2.circle( I_copy, (cx, cy), 8, (0, 0, 255), -1 )
        cv2.line(I_copy,(0,0),(cx,cy),(255,0,0),2)
        cv2.imshow("distance",I_copy)
        cv2.waitKey(0)

cv2.destroyAllWindows()