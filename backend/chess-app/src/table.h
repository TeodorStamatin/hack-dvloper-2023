#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
} *Piece;


Piece** init_matrix();
void print_matrix(Piece** table);
Piece** free_matrix(Piece** table);

