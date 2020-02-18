import cython
from libc.stdlib cimport malloc, free
cimport cfuncs
cimport numpy as cnp

def resize_images(cnp.ndarray[float, ndim=1, mode="c"] tempx, cnp.ndarray[float, ndim=1, mode="c"] tempy):
    cdef:
        int N
        float *ctempx
        float *ctempy
        
    ctempx = <float*> tempx.data
    ctempy = <float*> tempy.data
    # C function in cfunc.c
    cfunc(ctempx, ctempy)


