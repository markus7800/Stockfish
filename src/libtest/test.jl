
using Libdl

lib = dlopen("libmain.so")

ccall(dlsym(lib, :main), Cvoid, ())


ccall(dlsym(lib, :foo), Cvoid, ())
