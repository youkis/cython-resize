from distutils.core import setup, Extension
from Cython.Build import cythonize
from numpy import get_include

ext = Extension("cfuncs", sources=["cfuncs.pyx", "cfunc.c"], include_dirs=['.', get_include()])
setup(name="cfuncs", ext_modules=cythonize([ext]))

