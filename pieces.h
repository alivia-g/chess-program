#ifndef PIECES_H
#define PIECES_H

const char EMPTY = ' ';

// white pieces
const char WKNIGHT = 'N';
const char WQUEEN = 'Q';
const char WKING = 'K';
const char WBISHOP = 'B';
const char WROOK = 'R';
const char WPAWN = 'P';
// black pieces
const char BKNIGHT = 'n';
const char BQUEEN = 'q';
const char BKING = 'k';
const char BBISHOP = 'b';
const char BROOK = 'r';
const char BPAWN = 'p';

struct Coordinate[] get_valid_moves(struct Coordinate coord, char piece_type);




#endif // PIECES_H
