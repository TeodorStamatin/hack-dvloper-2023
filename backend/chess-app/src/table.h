#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

typedef enum _piece_color {
    BLACK,
    WHITE
}piece_color_t;

typedef enum _piece_type {
    PAWN,
    BISHOP,
    KNIGHT,
    KING,
    QUEEN,
    ROOK
}piece_type_t;

typedef struct piece {
    piece_color_t color;
    piece_type_t type;
    bool hasMoved;
} *Piece;


Piece** init_matrix();
void print_matrix(Piece** table, FILE* out);
void free_matrix(Piece** table);
int check_valid(Piece** table, int x1, int y1, int x2, int y2);
void print_screen(Piece** table);
char* fen(Piece** table);
Piece** move_piece(Piece** table, int x1, int y1, int x2, int y2);
int is_king_in_checkmate(Piece** table, char* color, char* type);
int is_king_in_check(Piece** table, int x, int y);
int not_good_position(Piece** table, int x, int y);
Piece **castling(Piece **table, int x, int y);


