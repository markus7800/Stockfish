from ctypes import *

lib = cdll.LoadLibrary("libmain2.so")

lib.main()

lib.foo()

lib.bar()