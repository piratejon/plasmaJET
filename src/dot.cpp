#include <sstream>
#include <fstream>
#include <string>

#include "AchiGame.h"

void play_game(std::ostream &, AchiGame &);
void dumb_loop(std::ostream &, AchiGame &);

std::string board_to_gvhtml(TttBoard & b) {
  std::stringstream s;

  s << "<<TABLE BORDER='0' CELLBORDER='1'>"
  << "<TR>"
    << "<TD SIDES='RB'>" << b.getSpace(0) << "</TD>"
    << "<TD SIDES='B'>" << b.getSpace(1) << "</TD>"
    << "<TD SIDES='LB'>" << b.getSpace(2) << "</TD>"
  << "</TR>"
  << "<TR>"
    << "<TD SIDES='R'>" << b.getSpace(3) << "</TD>"
    << "<TD BORDER='0'>" << b.getSpace(4) << "</TD>"
    << "<TD SIDES='L'>" << b.getSpace(5) << "</TD>"
  << "</TR>"
  << "<TR>"
    << "<TD SIDES='TR'>" << b.getSpace(6) << "</TD>"
    << "<TD SIDES='T'>" << b.getSpace(7) << "</TD>"
    << "<TD SIDES='LT'>" << b.getSpace(8) << "</TD>"
  << "</TR>"

  << "</TABLE>>";

  return s.str();
}

void print_board_label(std::ostream & o, TttBoard & b, const char * fill_color) {
  if (fill_color) {
    o << "  \"" << b.toString() <<"\"[style=\"filled\",fillcolor=\"" << fill_color << "\",label=" << board_to_gvhtml(b) << "]\n";
  } else {
    o << "  \"" << b.toString() <<"\"[label=" << board_to_gvhtml(b) << "]\n";
  }
}

void print_dot_thing(std::ostream & o, TttBoard & pre, TttBoard & post, int move, int turn, bool winner) {
  o << "\"" << pre.toString() << "\" -> \"" << post.toString()
    << "\"[label=\""<< (turn & 1 ? 'o' : 'x') << "→" << move << "\"];\n";

  if (winner) {
    print_board_label(o, post, turn & 1 ? "pink" : "lightblue");
  } else {
    print_board_label(o, post, "gray");
  }
}

void play_move(std::ostream & o, AchiGame & a, int move) {
  TttBoard preboard = a.board;
  a.playMove(move);
  TttBoard postboard = a.board;
  print_dot_thing(o, preboard, postboard, move, a.getTurnNumber() - 1, a.checkWinner());
}

void
dumb_loop(std::ostream & o, AchiGame & a) {
  int i;
  if (!a.checkWinner()) {
    for (i = 0; i < 9; i += 1) {
      if (a.isValidMove(i)) {
        AchiGame b(a);
        play_move(o, b, i);
        play_game(o, b);
      }
    }
  }
}

void
play_game(std::ostream & o, AchiGame & a) {
  if (!a.checkWinner()) {
    play_move(o, a, a.computeNextMove());
  }

  dumb_loop(o, a);
}

void
print_dot_header(std::ostream & o) {
  o << "strict digraph {\n  node[fontname=\"Consolas\"]\n  edge[fontname=\"Consolas\"]\n";
}

void
print_dot_footer(std::ostream & o) {
  o << "}\n";
}

int
main(int arfc, char **arfv) {

  AchiGame a;

  std::ofstream x("smart_x.dot");
  print_dot_header(x);
  print_board_label(x, a.board, "white");
  play_game(x, a);
  print_dot_footer(x);

  AchiGame b;
  std::ofstream o("smart_o.dot");
  print_dot_header(o);
  print_board_label(o, a.board, "white");
  dumb_loop(o, b);
  print_dot_footer(o);

  return 0;
}

