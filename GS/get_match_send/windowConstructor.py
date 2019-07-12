import numpy as np
import cv2

I1 = cv2.imread('/home/alireza/Documents/geo Localization/map2.jpeg')

window = np.zeros(I1.shape,dtype=np.uint8)
for i in range(0,6):
    for j in range(0,6):
        window = I1[j*32:j*32+32,i*43:i*43+43]
        cv2.imwrite("/home/alireza/Documents/geo Localization/slidingWindows2"+str(i)+str(j)+".jpg",window)