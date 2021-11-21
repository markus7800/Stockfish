from ctypes import *

lib = cdll.LoadLibrary("libmain.so")

lib.main()

lib.foo()