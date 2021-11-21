from ctypes import *

sf = cdll.LoadLibrary("libstockfish.so")
#sf.nnue.load_eval("nn-13406b1dcbe0.nnue")

#print(dir(sf))
print(type(sf))

sf.init()
sf.test()
sf.test2(1)
sf.test3("abc")
sf.eval_stockfish("rnbq1bnr/ppppkppp/8/4p3/4P3/8/PPPPKPPP/RNBQ1BNR w - - 2 3")
#print(sf["Stockfish::Eval::NNUE::load_eval"])