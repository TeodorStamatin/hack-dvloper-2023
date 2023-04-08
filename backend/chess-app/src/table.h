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
<<<<<<< HEAD
bool check_valid(void** table, int x1, int y1, int x2, int y2);
=======
int check_valid(void** table, int x1, int y1, int x2, int y2);
char* fen(void** table);
void** move_piece(void** table, int x1, int y1, int x2, int y2);
int is_king_in_checkmate(void** table, piece_color_t color);
int is_king_in_check(void** table, piece_color_t color);
>>>>>>> 6cc41c473ca818dcf9766c13e3029e15e0af4142

