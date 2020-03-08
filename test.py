import numpy as np
from PIL import Image
import cfuncs
from matplotlib import pylab as plt

x=np.array(Image.open("./imgs/img.jpg"))
plt.imshow(x)
plt.show()
inh, inw = x.shape[0], x.shape[1]

x=x.astype(np.uint8).transpose((2,0,1))
x=np.tile(x,(6,1,1))
x=x.copy(order='C')

import time
N=1000
start = time.time()
for i in range(N):
    y=np.zeros((18,208,208), dtype=np.uint8).copy(order='C')
    cfuncs.resize_images(x, y)
extime = time.time() - start
print ("%f [fps]" % (N/extime))

y=np.clip(y.transpose((1,2,0)),0,255).astype(np.int)
plt.imshow(y[...,:3])
plt.show()


