#include "table.h"

/* this function creates a matrix that represents the chess table in a generic type of date
be aware to dereference the void** */

void** init_matrix() {
    void **table = (void**)malloc(8 * sizeof(void*));
    for (int i = 0; i < 8; i++) {
        table[i] = (void*)malloc(8 * sizeof(void*));
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (i == 1 || i == 6) {
                Piece piece = malloc(sizeof(struct piece));
                piece->color = (i == 1) ? BLACK : WHITE;
                piece->type = PAWN;
                ((Piece**)table)[i][j] = piece;
            } else if (i == 0 || i == 7) {
                Piece piece = (Piece)malloc(sizeof(struct piece));
                piece->color = (i == 0) ? BLACK : WHITE;
                if (j == 0 || j == 7) {
                    piece->type = ROOK;
                } else if (j == 1 || j == 6) {
                    piece->type = KNIGHT;
                } else if (j == 2 || j == 5) {
                    piece->type = BISHOP;
                } else if (j == 3) {
                    piece->type = QUEEN;
                } else {
                    piece->type = KING;
                }
                ((Piece**)table)[i][j] = piece;
            } else {
                ((Piece**)table)[i][j] = NULL;
            }
        }
    }
    return table;
}

/*  this function prints the chess table with the piece and it's color stored in the matrix*/
void print_matrix(void** table) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (((Piece**)table)[i][j] != NULL) {
                printf("%c", (((Piece**)table)[i][j]->color == BLACK) ? 'B' : 'W');
                switch (((Piece**)table)[i][j]->type) {
                    case PAWN:
                        printf("P ");
                        break;
                    case BISHOP:
                        printf("B ");
                        break;
                    case KNIGHT:
                        printf("N ");
                        break;
                    case KING:
                        printf("K ");
                        break;
                    case QUEEN:
                        printf("Q ");
                        break;
                    case ROOK:
                        printf("R ");
                        break;
                }
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
}

void** free_matrix(void** table) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (((Piece**)table)[i][j] != NULL) {
                free(((Piece**)table)[i][j]);
            }
        }
        free(table[i]);
    }
    free(table);
    return NULL;
}

Piece** promote_pawn(Piece** table, int x, int y, piece_type_t type) {
    table[x][y]->type = type;
    return table;
}

Piece** en_passant(Piece** table, int x, int y, int x2, int y2) {
    if (table[x][y]->type == PAWN && table[x2][y2] == NULL) {
        free(table[x2][y2]);
        table[x2][y2] = table[x][y];
        table[x][y] = NULL;
    }
    return table;
}
