#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
} *Piece;


void** init_matrix();
void print_matrix(void** table);
void** free_matrix(void** table);
bool check_valid(Piece** table, int x1, int y1, int x2, int y2);

