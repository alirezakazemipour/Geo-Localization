import numpy as np
import cv2

I1 = cv2.imread('/home/alireza/Documents/farahi_ws/map.jpg')
G1 = cv2.cvtColor(I1,cv2.COLOR_BGR2GRAY)

I2 = cv2.imread("/home/alireza/Documents/farahi_ws/test.jpg")
G2 = cv2.cvtColor(I2,cv2.COLOR_BGR2GRAY)

sift = cv2.xfeatures2d.SIFT_create() # opencv 3
# use "sift = cv2.SIFT()" if the above fails

# detect keypoints and compute their disriptor vectors
keypoints1, desc1 = sift.detectAndCompute(G1, None); # opencv 3
keypoints2, desc2 = sift.detectAndCompute(G2, None); # opencv 3

print("No. of keypoints1 =", len(keypoints1))
print("No. of keypoints2 =", len(keypoints2))

print("Descriptors1.shape =", desc1.shape)
print("Descriptors2.shape =", desc2.shape)

# stop here!!
# exit() # comment this line out to move on!

# brute-force matching
bf = cv2.BFMatcher()

# for each descriptor in desc1 find its
# two nearest neighbours in desc2
matches = bf.knnMatch(desc1,desc2, k=2)

good_matches = []
alpha = 0.75
for m1,m2 in matches:
    # m1 is the best match
    # m2 is the second best match
    if m1.distance < alpha *m2.distance:
        good_matches.append(m1)

# apply RANSAC
points1 = [keypoints1[m.queryIdx].pt for m in good_matches]
points1 = np.array(points1,dtype=np.float32)

points2 = [keypoints2[m.trainIdx].pt for m in good_matches]
points2 = np.array(points2,dtype=np.float32)
H, mask = cv2.findHomography(points1, points2, cv2.RANSAC,5.0) # 5 pixels margin
mask = mask.ravel().tolist()
print(mask)

good_matches = [m for m,msk in zip(good_matches,mask) if msk == 1]

I = cv2.drawMatches(I1,keypoints1,I2,keypoints2, good_matches, None)

cv2.imshow('sift_keypoints1',I)
cv2.waitKey(0)
