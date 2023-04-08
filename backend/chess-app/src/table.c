#include "table.h"

Piece** init_matrix() {
    Piece** table = calloc(8, sizeof(Piece**));
    for (int i = 0; i < 8; i++) {
        table[i] = calloc(8, sizeof(Piece*));
        for(int j = 0; j < 8; j++) {
            table[i][j] = malloc(sizeof(struct piece));
            if (i < 2) {
                (table[i][j])->color = BLACK;

            } else if (i > 5) {
               (table[i][j])->color = WHITE;
            } else {
                (table[i][j]) = NULL;
            }
            if (i == 1 || i == 6) {
               (table[i][j])->type = PAWN;
            } else if (j == 0 || j == 7) {
                (table[i][j])->type = ROOK;
            } else if (j == 1 || j == 6) {
                (table[i][j])->type = KNIGHT;
            } else if (j == 2 || j == 5) {
                (table[i][j])->type = BISHOP;
            } else if (j == 3) {
                (table[i][j])->type = QUEEN;
            } else {
                (table[i][j])->type = KING;
            }
        }
    }
    return table;
}
/*  this function prints the chess table stored in the matrix*/
void print_matrix(Piece** table) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (table[i][j] == NULL) {
                printf("  ");
            } else {
                if ((table[i][j])->color == BLACK) {
                    printf("B");
                } else {
                    printf("W");
                }
                if ((table[i][j])->type == PAWN) {
                    printf("P");
                } else if ((table[i][j])->type == ROOK) {
                    printf("R");
                } else if ((table[i][j])->type == KNIGHT) {
                    printf("N");
                } else if ((table[i][j])->type == BISHOP) {
                    printf("B");
                } else if ((table[i][j])->type == QUEEN) {
                    printf("Q");
                } else {
                    printf("K");
                }
            }
            printf(" ");
        }
        printf("\n");
    }
}

Piece** free_matrix(Piece** table) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            free(table[i][j]);
        }
        free(table[i]);
    }
    free(table);
    table = NULL;
    return table;
}

