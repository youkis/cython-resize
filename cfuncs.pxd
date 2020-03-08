cdef extern from "cfunc.h":
   void cfunc(unsigned char *tempx, unsigned char *tempy, int ch, int ih, int iw, int oh, int ow)
