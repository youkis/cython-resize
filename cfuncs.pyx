import cython
from libc.stdlib cimport malloc, free
cimport cfuncs
cimport numpy as cnp

def resize_images(cnp.ndarray[unsigned char, ndim=3, mode="c"] tempx, cnp.ndarray[unsigned char, ndim=3, mode="c"] tempy):
    cdef:
        int ih, iw, oh, ow
    ch, ih, iw = tempx.shape[0], tempx.shape[1], tempx.shape[2]
    ch, oh, ow = tempy.shape[0], tempy.shape[1], tempy.shape[2]

    # C function in cfunc.c
    cfunc(&tempx[0,0,0], &tempy[0,0,0], ch, ih, iw, oh, ow)


