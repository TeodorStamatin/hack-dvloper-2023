#include "table.h"

/* this function creates a matrix that represents the chess table*/

Piece** init_matrix() {
    Piece** table = (Piece**)malloc(8 * sizeof(Piece*));
    for (int i = 0; i < 8; i++) {
        table[i] = (Piece*)malloc(8 * sizeof(Piece));
        for (int j = 0; j < 8; j++) {
            table[i][j] = NULL;
        }
    }
    for (int i = 0; i < 8; i++) {
        table[1][i] = (Piece)malloc(sizeof(struct piece));
        table[1][i]->color = BLACK;
        table[1][i]->type = PAWN;
        table[6][i] = (Piece)malloc(sizeof(struct piece));
        table[6][i]->color = WHITE;
        table[6][i]->type = PAWN;
    }
    for (int i = 0; i < 8; i++) {
        table[0][i] = (Piece)malloc(sizeof(struct piece));
        table[0][i]->color = BLACK;
        if(i == 0 || i == 7) {
            table[0][i]->type = ROOK;
        } else if(i == 1 || i == 6) {
            table[0][i]->type = KNIGHT;
        } else if(i == 2 || i == 5) {
            table[0][i]->type = BISHOP;
        } else if(i == 3) {
            table[0][i]->type = QUEEN;
        } else if(i == 4) {
            table[0][i]->type = KING;
        }
    }
    for (int i = 0; i < 8; i++) {
        table[7][i] = (Piece)malloc(sizeof(struct piece));
        table[7][i]->color = WHITE;
        if(i == 0 || i == 7) {
            table[7][i]->type = ROOK;
        } else if(i == 1 || i == 6) {
            table[7][i]->type = KNIGHT;
        } else if(i == 2 || i == 5) {
            table[7][i]->type = BISHOP;
        } else if(i == 3) {
            table[7][i]->type = QUEEN;
        } else if(i == 4) {
            table[7][i]->type = KING;
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

/* function that moves a pawn*/ 

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

