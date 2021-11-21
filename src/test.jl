
using Libdl
using BenchmarkTools
using Chess

lib = dlopen("libstockfish.so")

ccall(dlsym(lib, :init), Cvoid, ())


ccall(dlsym(lib, :test2), Cvoid, (Cint,), 1)
ccall(dlsym(lib, :test3), Cvoid, (Cstring,), "abc")

f = "q6k/8/8/8/8/8/PP6/K7 b - - 0 1" # "rnbq1bnr/ppppkppp/8/4p3/4P3/8/PPPPKPPP/RNBQ1BNR w - - 2 3"
println(ccall(dlsym(lib, :eval_fen_nnue), Cint, (Cstring,Bool), f, true))
println(ccall(dlsym(lib, :eval_fen_stockfish), Cint, (Cstring,), f))



#int pieces[6] = { 6, 14, 1, 1, 13, 0 };
#int squares[6] = { 0, 63, 8, 9, 56, 0 };
pieces = Cint[6, 14, 1, 1, 13, 0];
squares = Cint[0, 63, 8, 9, 56, 0];
player = 1;
println(ccall(dlsym(lib, :eval_nnue), Cint, (Cint, Ptr{Cint}, Ptr{Cint}, Bool), player, pieces, squares, true))
println(ccall(dlsym(lib, :eval_stockfish), Cint, (Cint, Ptr{Cint}, Ptr{Cint}), player, pieces, squares))

b = fromfen(f)
@btime ccall(dlsym(lib, :eval_fen_nnue), Cint, (Cstring ,Bool), fen(b), true)
@btime ccall(dlsym(lib, :eval_fen_stockfish), Cint, (Cstring,), fen(b))

@btime ccall(dlsym(lib, :eval_nnue), Cint, (Cint, Ptr{Cint}, Ptr{Cint}, Bool), player, pieces, squares, true)
@btime ccall(dlsym(lib, :eval_stockfish), Cint, (Cint, Ptr{Cint}, Ptr{Cint}), player, pieces, squares)
