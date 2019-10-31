from keras.applications.resnet50 import preprocess_input, ResNet50 # Best estimator
# from keras.applications.vgg19 import preprocess_input, VGG19 # So So
# from keras.applications.inception_v3 import preprocess_input, InceptionV3 # Worst estimator
# from keras.applications.inception_resnet_v2 import preprocess_input, InceptionResNetV2 # Almost worst
from keras.preprocessing.image import load_img, img_to_array
import cv2
import numpy as np
import glob
from PIL import Image
from scipy import spatial

model = ResNet50(include_top = False,
                 weights = "imagenet")

image_size = (300, 300)
stride = 20

map_features = []
img_patches  = []
k = -1

Map = cv2.imread("/home/alireza/Documents/Geo-Localization/GS/orthomosaic_preview.png")

window = np.zeros(Map.shape,dtype=np.uint8)
for i in range(0, (Map.shape[0] - image_size[0]) // stride):
    for j in range(0, (Map.shape[1] - image_size[1]) // stride):

        window = Map[i * stride:i * stride + image_size[0]
                    ,j * stride:j * stride + image_size[1] ]
        img_patches.append(window)

        window = cv2.cvtColor(window, cv2.COLOR_BGR2RGB)
        img = Image.fromarray(window)
        window = img_to_array(window)
        window = np.expand_dims(window, axis = 0)
        window = preprocess_input(window)
        feature = model.predict(window)
        feature = np.reshape(feature, -1)
        map_features.append(feature)

current_observation = load_img("/home/alireza/Documents/Geo-Localization/GS/101MEDIA/Y0210928.jpg"
                               , target_size = image_size)
img = img_to_array(current_observation)
img = np.expand_dims(img , axis = 0)
img = preprocess_input(img)
current_feature = model.predict(img)
current_feature = np.reshape(current_feature, -1)

dist = []

for i in range(len(map_features)):
    dist.append(1 - spatial.distance.cosine(current_feature, map_features[i]))

dist_array = np.array(dist, dtype=np.float64)

index = np.argmax(dist_array)
print(f"index is: {index}")

cv2.imshow("predicted location", img_patches[index])
cv2.waitKey(0)
x = input()