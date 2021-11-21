
make -j build ARCH=x86-64
g++ -shared -fpic -o libstockfish.so benchmark.o bitbase.o bitboard.o endgame.o evaluate.o main.o material.o misc.o movegen.o movepick.o pawns.o position.o psqt.o search.o thread.o timeman.o tt.o uci.o ucioption.o tune.o tbprobe.o evaluate_nnue.o half_ka_v2_hm.o  -m64 -mmacosx-version-min=10.14 -arch x86_64 -lpthread -Wall -Wcast-qual -fno-exceptions -std=c++17  -pedantic -Wextra -Wshadow -m64 -mmacosx-version-min=10.14 -arch x86_64 -DUSE_PTHREADS -DNDEBUG -O3 -mdynamic-no-pic -DIS_64BIT -msse -DUSE_SSE2 -msse2 -flto
