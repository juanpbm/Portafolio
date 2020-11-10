import numpy as np
from matplotlib import pyplot as plt
import math
import cv2
import os
import gc
import scipy.io as sio


def Harris(img, window_size=3, sobel_size=3, k=0.04, step_size=1):
   if len(img.shape) > 2:
       img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

   h, w = img.shape[0], img.shape[1]

   sobelx = cv2.Sobel(img, cv2.CV_64F, 1, 0, ksize=sobel_size)
   sobely = cv2.Sobel(img, cv2.CV_64F, 0, 1, ksize=sobel_size)

   Ixx = sobelx ** 2
   Iyy = sobely ** 2
   Ixy = sobelx * sobely

   R = np.zeros_like(img, dtype=np.float64)

   offset = np.floor(window_size / 2).astype(np.int8)
   for y in range(offset, h - offset, step_size):
       for x in range(offset, w - offset, step_size):
           Sxx = np.sum(Ixx[y - offset:y + 1 + offset, x - offset:x + 1 + offset])
           Syy = np.sum(Iyy[y - offset:y + 1 + offset, x - offset:x + 1 + offset])
           Sxy = np.sum(Ixy[y - offset:y + 1 + offset, x - offset:x + 1 + offset])
           r = (Sxx * Syy) - (Sxy ** 2) - k * (Sxx + Syy) ** 2
           if r < 0:
               r = 0
           R[y][x] = r

   R /= np.max(R)
   R *= 255.0
   # _, R = cv2.threshold(R, 0.01 * np.max(R), 255, 0)
   return R


def non_max_suppression(img, window_size=5, thresh=2.5):
   h, w = img.shape[0], img.shape[1]

   offset = np.floor(window_size / 2).astype(np.int8)

   temp = np.zeros_like(img)
   temp[offset:h - offset, offset:w - offset] = img[offset:h - offset, offset:w - offset]
   img = temp
   del temp

   index = np.zeros((h, w, 3), dtype=np.int16)

   index[:, :, 0] = img

   for y in range(h):
       for x in range(w):
           index[y][x][1] = x
           index[y][x][2] = y

   corners = []

   global NMS_index
   global NMS_corners
   NMS_index = np.zeros((h, w))
   NMS_corners = np.zeros((h, w))

   for y in range(offset, h - offset, offset):
       for x in range(offset, w - offset, offset):
           ret = mean_shift_converge(index, (x, y), window_size, thresh)
           if ret:
               corners.append(ret)

   corners = list(set(corners))
   corners.sort()
   return corners


def mean_shift_converge(index, point, window_size=5, thresh=2.5):
   x, y = point
   offset = np.floor(window_size / 2).astype(np.int8)

   if NMS_index[y][x] == 1:
       return None

   window = index[y - offset:y + 1 + offset, x - offset:x + 1 + offset]

   if np.any(NMS_corners[y - offset:y + 1 + offset, x - offset:x + 1 + offset]):
       return None

   if np.max(window[:, :, 0]) > thresh:
       window = np.reshape(window, (window_size ** 2, 3))
       window[::-1] = window[window[:, 0].argsort()]
       if window[0][1] == x and window[0][2] == y:
           NMS_index[y][x] = 1
           NMS_corners[y][x] = 1
           return x, y
       else:
           ret = mean_shift_converge(index, (window[0][1], window[0][2]), window_size, thresh)
           if ret:
               NMS_index[y][x] = 1
               return ret[0], ret[1]
           else:
               return None
   else:
       return None


def generate_patch(harris_window=5, display=False):
   train_path = "CarTrainImages"

   WINDOW_SIZE = 25
   OFFSET = int(np.floor(WINDOW_SIZE/2))

   patch = []

   i = 0
   for serial_number in os.listdir(train_path + '/'):
       train_image = cv2.cvtColor(cv2.imread(train_path + '/' + serial_number), cv2.COLOR_BGR2GRAY)
       print(serial_number)

       w, h = train_image.shape[1], train_image.shape[0]

       ret = Harris(train_image, harris_window, harris_window, 0.04, step_size=1)
       centroids = non_max_suppression(ret, 9)

       for center in centroids:
           x = int(center[0])
           y = int(center[1])
           if x < OFFSET or x >= (w-OFFSET) or y < OFFSET or y >= (h-OFFSET):
               continue
           window = train_image[y-OFFSET:y+1+OFFSET, x-OFFSET:x+1+OFFSET]

           if i == 0:
               patch = (window.flatten()).copy()
           else:
               patch = np.vstack([patch, window.flatten()])

           i += 1

       output = cv2.cvtColor(train_image.copy(), cv2.COLOR_GRAY2BGR)
       for center in centroids:
           cv2.circle(output, (int(center[0]), int(center[1])), 2, (255, 0, 0), 1)

       if display:
           plt.imshow(output, cmap='gray')
           plt.axis('off')
           plt.show()

   print(patch.shape)
   sio.savemat('patch.mat', {'patch': patch})


def generate_vocabulary():
   M = sio.loadmat('kmeans.mat')
   idx = M['idx']
   C = M['C']

   K = []

   window_size = int(np.sqrt(len(C[0])))

   for frame in C:
       K.append(np.reshape(frame, (window_size, window_size)))
   K = np.array(K)

   train_path = "CarTrainImages"

   OFFSET = int(np.floor(window_size / 2))

   displacements = [list()] * len(K)

   for serial_number in os.listdir(train_path + '/'):
       train_image = cv2.cvtColor(cv2.imread(train_path + '/' + serial_number), cv2.COLOR_BGR2GRAY)
       print(serial_number)

       w, h = train_image.shape[1], train_image.shape[0]

       ret = Harris(train_image, 5, 5, 0.04, step_size=1)
       centroids = non_max_suppression(ret, 9)

       for center in centroids:
           x = int(center[0])
           y = int(center[1])
           if x < OFFSET or x >= (w-OFFSET) or y < OFFSET or y >= (h-OFFSET):
               continue
           SSD = []
           for f in range(len(K)):
               window = train_image[y-OFFSET:y+1+OFFSET, x-OFFSET:x+1+OFFSET]
               ssd = np.mean((window-K[f]) ** 2)
               SSD.append([ssd, f, (x-w/2, y-h/2)])
           SSD.sort(key=lambda z: z[0])

           if len(displacements[SSD[0][1]]) == 0:
               displacements[SSD[0][1]] = [SSD[0][2]]
           else:
               displacements[SSD[0][1]].append(SSD[0][2])

   sio.savemat('displacement.mat', {'d': displacements})


def match_template():
   M = sio.loadmat('displacement.mat')
   displacement = np.squeeze(M['d'])

   M = sio.loadmat('kmeans.mat')
   idx = M['idx']
   C = M['C']
   K = []
   window_size = int(np.sqrt(len(C[0])))
   OFFSET = int(np.floor(window_size / 2))
   for frame in C:
       K.append(np.reshape(frame, (window_size, window_size)))
   K = np.array(K)

   test_path = "CarTestImages"

   kernel = np.array( [[0.023528, 0.033969,  0.038393,  0.033969,  0.023528],
                       [0.033969, 0.049045,  0.055432,  0.049045,  0.033969],
                       [0.038393, 0.055432,  0.062651,  0.055432,  0.038393],
                       [0.033969, 0.049045,  0.055432,  0.049045,  0.033969],
                       [0.023528, 0.033969,  0.038393,  0.033969,  0.023528]])
   kernel_offset = 2

   c = 0
   for serial_number in os.listdir(test_path + '/'):
       c += 1
       if c < 18:
           continue

       test_image = cv2.cvtColor(cv2.imread(test_path + '/' + serial_number), cv2.COLOR_BGR2GRAY)
       print(serial_number)

       w, h = test_image.shape[1], test_image.shape[0]

       ret = Harris(test_image, 3, 3, 0.04, step_size=1)
       centroids = non_max_suppression(ret, 15)

       output = cv2.cvtColor(test_image.copy(), cv2.COLOR_GRAY2BGR)
       for center in centroids:
           cv2.circle(output, (int(center[0]), int(center[1])), 2, (255, 0, 0), 1)

       # plt.imshow(output, cmap='gray')
       # plt.axis('off')
       # plt.show()

       GHT_image = np.zeros_like(test_image, dtype=np.float64)
       for center in centroids:
           x = int(center[0])
           y = int(center[1])
           if x < OFFSET or x >= (w-OFFSET) or y < OFFSET or y >= (h-OFFSET):
               continue
           SSD = []
           for f in range(len(K)):
               window = test_image[y-OFFSET:y+1+OFFSET, x-OFFSET:x+1+OFFSET]
               ssd = np.mean((window-K[f]) ** 2)
               SSD.append([ssd, f, (x-w/2, y-h/2)])
           SSD.sort(key=lambda l: l[0])

           vote_scale = 1000 / len(displacement[SSD[0][1]])
           for d in displacement[SSD[0][1]]:
               x_new = int(x - d[0])
               y_new = int(y - d[1])
               if x_new < 2 or x_new >= w-2 or y_new < 2 or y_new >= h-2:
                   continue

               GHT_image[y_new-kernel_offset: y_new+kernel_offset+1, x_new-kernel_offset: x_new+kernel_offset+1] += kernel * vote_scale

       GHT_image = cv2.GaussianBlur(GHT_image, (5, 5), 1.5)

       offset = 25
       temp = np.zeros_like(GHT_image)
       temp[offset:h - offset, offset:w - offset] = GHT_image[offset:h - offset, offset:w - offset]

       GHT_centroids = non_max_suppression(GHT_image, window_size=93, thresh=0.8*temp.max())

       max_index = np.where(GHT_image == np.amax(GHT_image))
       if len(GHT_centroids) == 0:
           GHT_centroids.append((max_index[1][0], max_index[0][0]))

       # output = cv2.cvtColor(test_image.copy(), cv2.COLOR_GRAY2BGR)
       # cv2.circle(output, (int(max_index[1]), int(max_index[0])), 2, (0, 255, 0), 1)
       # for center in centroids:
       #     cv2.circle(output, (int(center[0]), int(center[1])), 2, (0, 0, 255), 1)
       # for center in GHT_centroids:
       #     cv2.circle(output, (int(center[0]), int(center[1])), 2, (255, 0, 0), 1)

       output = cv2.cvtColor(test_image.copy(), cv2.COLOR_GRAY2BGR)
       for center in GHT_centroids:
           window = GHT_image[center[1]-20:center[1]+21, center[0]-50:center[0]+51]
           top_left = (int(center[0]) - 50, int(center[1]) - 20)
           cv2.rectangle(output, (top_left[0], top_left[1]), (top_left[0]+100, top_left[1]+40), (255, 0, 0), 1)

       fig, (ax1, ax2) = plt.subplots(2, 1)
       ax1.imshow(GHT_image, cmap='gray')
       ax1.axis('off')
       ax2.imshow(output, cmap='gray')
       ax2.axis('off')

       plt.show()


if __name__ == "__main__":
   generate_patch(display=False)
   generate_vocabulary()
   match_template()
