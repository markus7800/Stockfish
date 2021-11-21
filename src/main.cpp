/*
  Stockfish, a UCI chess playing engine derived from Glaurung 2.1
  Copyright (C) 2004-2021 The Stockfish developers (see AUTHORS file)

  Stockfish is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Stockfish is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <cassert>

#include "bitboard.h"
#include "endgame.h"
#include "position.h"
#include "psqt.h"
#include "search.h"
#include "syzygy/tbprobe.h"
#include "thread.h"
#include "tt.h"
#include "uci.h"

using namespace Stockfish;

extern "C" {
  void init() {
    //CommandLine::init(argc, argv);
    UCI::init(Options);
    Tune::init();
    PSQT::init();
    Bitboards::init();
    Position::init();
    Bitbases::init();
    Endgames::init();
    Threads.set(1);//size_t(Options["Threads"]));
    Search::clear(); // After threads are up
    Eval::NNUE::init();
    std::cout << "Stockfish Eval initialised!" << std::endl;
  }

  void test() {
    std::cout << "this is a test" << std::endl;
    StateInfo st;
    Position pos;
    
    pos.set("rnbq1bnr/ppppkppp/8/4p3/4P3/8/PPPPKPPP/RNBQ1BNR w - - 2 3", false, &st, Threads.main());
    std::cout << pos << std::endl;
    std::cout << Eval::NNUE::trace(pos) << std::endl;
    std::cout << Eval::NNUE::evaluate(pos, true) << std::endl;
    std::cout << Eval::NNUE::evaluate(pos, false) << std::endl;
    std::cout << Eval::evaluate(pos) << std::endl;
  }

  void test2(int i) {
    std::cout << "Int: " << i << std::endl;
  }

  void test3(char* s) {
    std::cout << "String: " << s << std::endl;
  }

  int eval_fen_nnue(const char* fenStr, bool adjusted) {
    StateInfo st;
    Position pos;
    pos.set(fenStr, false, &st, Threads.main());
    return Eval::NNUE::evaluate(pos, adjusted);
  }

  int eval_fen_stockfish(const char* fenStr) {
    StateInfo st;
    Position pos;
    pos.set(fenStr, false, &st, Threads.main());
    return Eval::evaluate(pos);
  }

  void make_position(StateInfo &st, Position &pos, int player, int* pieces, int* squares) {
    std::memset(&pos, 0, sizeof(Position));
    std::memset(&st, 0, sizeof(StateInfo));

    for (size_t i = 0; i < 64; i++) {
      // std::cout << "Piece: " << Piece(pieces[i]) << ", Square: " << Square(squares[i]) << std::endl;
      if (pieces[i] == NO_PIECE) { // 0
        break;
      }
      pos.put_piece(Piece(pieces[i]), Square(squares[i]));
    }
    // std::cout << "Side: " << Color(player) << std::endl;
    pos.set_side_to_move(Color(player)); // WHITE == 0

    // std::cout << "State:" << std::endl;
    pos.overwrite_state(&st);
    
    // std::cout << pos.state() << std::endl;

    pos.state()->epSquare = SQ_NONE;
    // std::cout << "en passant: " << pos.state()->epSquare << std::endl;
    pos.set_state(pos.state());

    // std::cout << "Thread:" << std::endl;
    pos.set_thread(Threads.main());
    // std::cout << pos.this_thread() << std::endl;
    

    /*std::cout << "chess960: " << pos.is_chess960() << std::endl;


    std::cout << "en passant: " << pos.state()->castlingRights << std::endl;

    std::cout << "castling W: " << pos.castling_rights(WHITE) << std::endl;
    std::cout << "castling B: " << pos.castling_rights(BLACK) << std::endl;


    std::cout << "Ok:" << std::endl;
    assert(pos.pos_is_ok());*/

    // std::cout << pos << std::endl;
  }

  int eval_nnue(int player, int* pieces, int* squares, bool adjusted) {
    StateInfo st;
    Position pos;
    
    make_position(st, pos, player, pieces, squares);

    return Eval::NNUE::evaluate(pos, adjusted);
  }

  int eval_stockfish(int player, int* pieces, int* squares) {
    StateInfo st;
    Position pos;

    make_position(st, pos, player, pieces, squares);

    return Eval::evaluate(pos);
  }
}

int main(int argc, char* argv[]) {

  std::cout << engine_info() << std::endl;

  CommandLine::init(argc, argv);
  UCI::init(Options);
  Tune::init();
  PSQT::init();
  Bitboards::init();
  Position::init();
  Bitbases::init();
  Endgames::init();
  Threads.set(size_t(Options["Threads"]));
  Search::clear(); // After threads are up
  Eval::NNUE::init();
  
  UCI::loop(argc, argv);

  Threads.set(0);

  /*
  init();
  // test();
  // test2(8);
  // test3("abc");

  // StateInfo st;
  // Position pos;
  // pos.set("rnbq1bnr/ppppkppp/8/4p3/4P3/8/PPPPKPPP/RNBQ1BNR w - - 2 3", false, &st, Threads.main());
  // std::cout << pos << std::endl;

  // std::cout << eval_fen_nnue("rnbq1bnr/ppppkppp/8/4p3/4P3/8/PPPPKPPP/RNBQ1BNR w - - 2 3", true) << std::endl;
  // std::cout << eval_fen_stockfish("rnbq1bnr/ppppkppp/8/4p3/4P3/8/PPPPKPPP/RNBQ1BNR w - - 2 3") << std::endl;

  // int pieces[6] = { W_KING, B_KING, W_PAWN, W_PAWN, B_QUEEN, 0 };
  // int squares[6] = {SQ_A1, SQ_H8, SQ_A2, SQ_B2, SQ_A8, 0};

  int pieces[6] = { 6, 14, 1, 1, 13, 0 };
  int squares[6] = { 0, 63, 8, 9, 56, 0 };

  int player = 1;
  std::cout <<  eval_nnue(player, pieces, squares, true) << std::endl;
  std::cout <<  eval_stockfish(player, pieces, squares) << std::endl;

  std::cout << eval_fen_nnue("q6k/8/8/8/8/8/PP6/K7 b - - 0 1", true) << std::endl;
  std::cout << eval_fen_stockfish("q6k/8/8/8/8/8/PP6/K7 b - - 0 1") << std::endl;
  */
  return 0;
}
