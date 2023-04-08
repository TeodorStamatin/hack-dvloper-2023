#include "table.h"

/* this function creates a matrix that represents the chess table*/

Piece** init_matrix() {
    Piece** table = (Piece**)malloc(8 * sizeof(Piece*));
    for (int i = 0; i < 8; i++) {
        table[i] = (Piece*)malloc(8 * sizeof(Piece));
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            table[i][j] = NULL;
        }
    }
    for (int i = 0; i < 8; i++) {
        table[1][i] = (Piece)malloc(sizeof(struct piece));
        table[1][i]->color = BLACK;
        table[1][i]->type = PAWN;
        table[1][i]->hasMoved = false;
    }
    for (int i = 0; i < 8; i++) {
        table[6][i] = (Piece)malloc(sizeof(struct piece));
        table[6][i]->color = WHITE;
        table[6][i]->type = PAWN;
        table[6][i]->hasMoved = false;
    }
    table[0][0] = (Piece)malloc(sizeof(struct piece));
    table[0][0]->color = BLACK;
    table[0][0]->type = ROOK;
    table[0][0]->hasMoved = false;
    table[0][7] = (Piece)malloc(sizeof(struct piece));
    table[0][7]->color = BLACK;
    table[0][7]->type = ROOK;
    table[0][7]->hasMoved = false;
    table[7][0] = (Piece)malloc(sizeof(struct piece));
    table[7][0]->color = WHITE;
    table[7][0]->type = ROOK;
    table[7][0]->hasMoved = false;
    table[7][7] = (Piece)malloc(sizeof(struct piece));
    table[7][7]->color = WHITE;
    table[7][7]->type = ROOK;
    table[7][7]->hasMoved = false;
    table[0][1] = (Piece)malloc(sizeof(struct piece));
    table[0][1]->color = BLACK;
    table[0][1]->type = KNIGHT;
    table[0][1]->hasMoved = false;
    table[0][6] = (Piece)malloc(sizeof(struct piece));
    table[0][6]->color = BLACK;
    table[0][6]->type = KNIGHT;
    table[0][6]->hasMoved = false;
    table[7][1] = (Piece)malloc(sizeof(struct piece));
    table[7][1]->color = WHITE;
    table[7][1]->type = KNIGHT;
    table[7][1]->hasMoved = false;
    table[7][6] = (Piece)malloc(sizeof(struct piece));
    table[7][6]->color = WHITE;
    table[7][6]->type = KNIGHT;
    table[7][6]->hasMoved = false;
    table[0][2] = (Piece)malloc(sizeof(struct piece));
    table[0][2]->color = BLACK;
    table[0][2]->type = BISHOP;
    table[0][2]->hasMoved = false;
    table[0][5] = (Piece)malloc(sizeof(struct piece));
    table[0][5]->color = BLACK;
    table[0][5]->type = BISHOP;
    table[0][5]->hasMoved = false;
    table[7][2] = (Piece)malloc(sizeof(struct piece));
    table[7][2]->color = WHITE;
    table[7][2]->type = BISHOP;
    table[7][2]->hasMoved = false;
    table[7][5] = (Piece)malloc(sizeof(struct piece));
    table[7][5]->color = WHITE;
    table[7][5]->type = BISHOP;
    table[7][5]->hasMoved = false;
    table[0][3] = (Piece)malloc(sizeof(struct piece));
    table[0][3]->color = BLACK;
    table[0][3]->type = QUEEN;
    table[0][3]->hasMoved = false;
    table[7][3] = (Piece)malloc(sizeof(struct piece));
    table[7][3]->color = WHITE;
    table[7][3]->type = QUEEN;
    table[7][3]->hasMoved = false;
    table[0][4] = (Piece)malloc(sizeof(struct piece));
    table[0][4]->color = BLACK;
    table[0][4]->type = KING;
    table[0][4]->hasMoved = false;
    table[7][4] = (Piece)malloc(sizeof(struct piece));
    table[7][4]->color = WHITE;
    table[7][4]->type = KING;
    table[7][4]->hasMoved = false;
    return table;
}

//functia print matrix va afisa fiecare pe pozitia sa din matricea table sub forma <culoare><tip>,linie,coloana
void print_matrix(Piece** table, FILE* out) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (table[i][j] != NULL) {
                char buf1[100];
                strcpy(buf1, table[i][j]->color == WHITE ? "WHITE" : "BLACK");
                char buf2[100];
                strcpy(buf2, table[i][j]->type == PAWN ? "PAWN" : table[i][j]->type == ROOK ? "ROOK" : table[i][j]->type == KNIGHT ? "KNIGHT" : table[i][j]->type == BISHOP ? "BISHOP" : table[i][j]->type == QUEEN ? "QUEEN" : "KING");
                fprintf(out, "%s_%s,%u,%u", buf1, buf2, i, j);
                fprintf(out, "\n");
            }
        }
    }
    return;
}


void free_matrix(Piece** table) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (table[i][j] != NULL) {
                free(table[i][j]);
            }
        }
        free(table[i]);
    }
    free(table);
    return;
}

/*function that checks if chess move is valid. this means you should check if the position where you move is NULL, and if it is not,
you should check if your chess piece has the right movement to go there, and if a piece is there, check that is doesnt have the same 
color. lastly, you should check that if you move the wanted piece, your king cant be taken by other color chess pieces. NOTE THAT 
ONLY table->type->knight can jump over other piece. other pieces cand go to the wanted position if they have to go through an occupied
position on the table.*/

int check_valid(Piece** table, int x1, int y1, int x2, int y2) {
    if (x1 == x2 && y1 == y2) {
        return 0;
    }
    if (table[x1][y1] == NULL) {
        return 0;
    }
    if (table[x2][y2] != NULL && table[x2][y2]->color == table[x1][y1]->color) {
        return 0;
    }
    if (is_king_in_check(table, x1, y1)) {
        goto check;
    }
    if (table[x1][y1]->type == PAWN) {
        if (table[x1][y1]->color == WHITE) {
            if (x2 == x1 + 1 && y2 == y1 && table[x2][y2] == NULL) {
                return 1;
            }
            if (x2 == x1 + 1 && y2 == y1 + 1 && table[x2][y2] != NULL && table[x2][y2]->color == BLACK) {
                return 1;
            }
            if (x2 == x1 + 1 && y2 == y1 - 1 && table[x2][y2] != NULL && table[x2][y2]->color == BLACK) {
                return 1;
            }
            if (x2 == x1 + 2 && y2 == y1 && table[x2][y2] == NULL && table[x1 + 1][y1] == NULL && table[x1][y1]->hasMoved == false) {
                return 1;
            }
        }
        else {
            if (x2 == x1 - 1 && y2 == y1 && table[x2][y2] == NULL) {
                return 1;
            }
            if (x2 == x1 - 1 && y2 == y1 + 1 && table[x2][y2] != NULL && table[x2][y2]->color == WHITE) {
                return 1;
            }
            if (x2 == x1 - 1 && y2 == y1 - 1 && table[x2][y2] != NULL && table[x2][y2]->color == WHITE) {
                return 1;
            }
            if (x2 == x1 - 2 && y2 == y1 && table[x2][y2] == NULL && table[x1 - 1][y1] == NULL && table[x1][y1]->hasMoved == false) {
                return 1;
            }
        }
    }
    if (table[x1][y1]->type == ROOK) {
        if (x2 == x1 && y2 > y1) {
            for (int i = y1 + 1; i < y2; i++) {
                if (table[x1][i] != NULL) {
                    return 0;
                }
            }
            return 1;
        }
        if (x2 == x1 && y2 < y1) {
            for (int i = y1 - 1; i > y2; i--) {
                if (table[x1][i] != NULL) {
                    return 0;
                }
            }
            return 1;
        }
        if (y2 == y1 && x2 > x1) {
            for (int i = x1 + 1; i < x2; i++) {
                if (table[i][y1] != NULL) {
                    return 0;
                }
            }
            return 1;
        }
        if (y2 == y1 && x2 < x1) {
            for (int i = x1 - 1; i > x2; i--) {
                if (table[i][y1] != NULL) {
                    return 0;
                }
            }
            return 1;
        }
    }
    if (table[x1][y1]->type == KNIGHT) {
        if (x2 == x1 + 2 && y2 == y1 + 1) {
            return 1;
        }
        if (x2 == x1 + 2 && y2 == y1 - 1) {
            return 1;
        }
        if (x2 == x1 - 2 && y2 == y1 + 1) {
            return 1;
        }
        if (x2 == x1 - 2 && y2 == y1 - 1) {
            return 1;
        }
        if (x2 == x1 + 1 && y2 == y1 + 2) {
            return 1;
        }
        if (x2 == x1 + 1 && y2 == y1 - 2) {
            return 1;
        }
        if (x2 == x1 - 1 && y2 == y1 + 2) {
            return 1;
        }
        if (x2 == x1 - 1 && y2 == y1 - 2) {
            return 1;
        }
    }
    if (table[x1][y1]->type == BISHOP) {
        if (x2 > x1 && y2 > y1) {
            for (int i = x1 + 1, j = y1 + 1; i < x2 && j < y2; i++, j++) {
                if (table[i][j] != NULL) {
                    return 0;
                }
            }
            return 1;
        }
        if (x2 > x1 && y2 < y1) {
            for (int i = x1 + 1, j = y1 - 1; i < x2 && j > y2; i++, j--) {
                if (table[i][j] != NULL) {
                    return 0;
                }
            }
            return 1;
        }
        if (x2 < x1 && y2 > y1) {
            for (int i = x1 - 1, j = y1 + 1; i > x2 && j < y2; i--, j++) {
                if (table[i][j] != NULL) {
                    return 0;
                }
            }
            return 1;
        }
        if (x2 < x1 && y2 < y1) {
            for (int i = x1 - 1, j = y1 - 1; i > x2 && j > y2; i--, j--) {
                if (table[i][j] != NULL) {
                    return 0;
                }
            }
            return 1;
        }
    }
    if (table[x1][y1]->type == QUEEN) {
        if (x2 == x1 && y2 > y1) {
            for (int i = y1 + 1; i < y2; i++) {
                if (table[x1][i] != NULL) {
                    return 0;
                }
            }
            return 1;
        }
        if (x2 == x1 && y2 < y1) {
            for (int i = y1 - 1; i > y2; i--) {
                if (table[x1][i] != NULL) {
                    return 0;
                }
            }
            return 1;
        }
        if (y2 == y1 && x2 > x1) {
            for (int i = x1 + 1; i < x2; i++) {
                if (table[i][y1] != NULL) {
                    return 0;
                }
            }
            return 1;
        }
        if (y2 == y1 && x2 < x1) {
            for (int i = x1 - 1; i > x2; i--) {
                if (table[i][y1] != NULL) {
                    return 0;
                }
            }
            return 1;
        }
        if (x2 > x1 && y2 > y1) {
            for (int i = x1 + 1, j = y1 + 1; i < x2 && j < y2; i++, j++) {
                if (table[i][j] != NULL) {
                    return 0;
                }
            }
            return 1;
        }
        if (x2 > x1 && y2 < y1) {
            for (int i = x1 + 1, j = y1 - 1; i < x2 && j > y2; i++, j--) {
                if (table[i][j] != NULL) {
                    return 0;
                }
            }
            return 1;
        }
        if (x2 < x1 && y2 > y1) {
            for (int i = x1 - 1, j = y1 + 1; i > x2 && j < y2; i--, j++) {
                if (table[i][j] != NULL) {
                    return 0;
                }
            }
            return 1;
        }
        if (x2 < x1 && y2 < y1) {
            for (int i = x1 - 1, j = y1 - 1; i > x2 && j > y2; i--, j--) {
                if (table[i][j] != NULL) {
                    return 0;
                }
            }
            return 1;
        }
    }
    if (table[x1][y1]->type == KING) {
        check:
        if (x2 == x1 + 1 && y2 == y1 + 1) {
            return 1;
        }
        if (x2 == x1 + 1 && y2 == y1 - 1) {
            return 1;
        }
        if (x2 == x1 - 1 && y2 == y1 + 1) {
            return 1;
        }
        if (x2 == x1 - 1 && y2 == y1 - 1) {
            return 1;
        }
        if (x2 == x1 + 1 && y2 == y1) {
            return 1;
        }
        if (x2 == x1 - 1 && y2 == y1) {
            return 1;
        }
        if (x2 == x1 && y2 == y1 + 1) {
            return 1;
        }
        if (x2 == x1 && y2 == y1 - 1) {
            return 1;
        }
    }
    return 0;
}

// function that moves the piece and allocate the new position and free the old one
Piece** move_piece(Piece** table, int x1, int y1, int x2, int y2) {
    if (check_valid(table, x1, y1, x2, y2) == 0) {
        return table;
    }
    if (table[x1][y1]->type == PAWN) {
        if (table[x1][y1]->color == WHITE) {
            if (y2 == 7) {
                table[x2][y2] = (Piece*) malloc(sizeof(Piece));
                table[x2][y2]->type = QUEEN;
                table[x2][y2]->color = WHITE;
                table[x1][y1] = NULL;
                return table;
            }
        }
        if (table[x1][y1]->color == BLACK) {
            if (y2 == 0) {
                table[x2][y2] = (Piece*) malloc(sizeof(Piece));
                table[x2][y2]->type = QUEEN;
                table[x2][y2]->color = BLACK;
                table[x1][y1] = NULL;
                return table;
            }
        }
    }
    table[x2][y2] = (Piece*) malloc(sizeof(Piece));
    table[x2][y2]->type = table[x1][y1]->type;
    table[x2][y2]->color = table[x1][y1]->color;
    table[x1][y1] = NULL;
    return table;
}

int return_check() {
    FILE *move = fopen("move.txt", "r");
    int x1, y1, x2, y2;
    fscanf(move, "%d %d %d %d", &x1, &y1, &x2, &y2);
    fclose(move);
    FILE *in = fopen("matrix.txt", "r");
    // in fisier se afla fiecare piesa sub forma <culoare>_<tip>,<x>,<y>
    // unde x si y sunt coordonatele pe tabla
    char line[100];
    Piece** table = (Piece**) malloc(8 * sizeof(Piece*));
    for (int i = 0; i < 8; i++) {
        table[i] = (Piece*) malloc(8 * sizeof(Piece));
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            table[i][j] = NULL;
        }
    }
    while (fgets(line, 100, in)) {
        char *token = strtok(line, ",");
        char *color = strtok(token, "_");
        char *type = strtok(NULL, "_");
        int x = atoi(strtok(NULL, ","));
        int y = atoi(strtok(NULL, ","));
        table[x][y] = (Piece) malloc(sizeof(struct piece));
        if (strcmp(color, "white") == 0) {
            table[x][y]->color = WHITE;
        }
        if (strcmp(color, "black") == 0) {
            table[x][y]->color = BLACK;
        }
        if (strcmp(type, "king") == 0) {
            table[x][y]->type = KING;
        }
        if (strcmp(type, "queen") == 0) {
            table[x][y]->type = QUEEN;
        }
        if (strcmp(type, "rook") == 0) {
            table[x][y]->type = ROOK;
        }
        if (strcmp(type, "bishop") == 0) {
            table[x][y]->type = BISHOP;
        }
        if (strcmp(type, "knight") == 0) {
            table[x][y]->type = KNIGHT;
        }
        if (strcmp(type, "pawn") == 0) {
            table[x][y]->type = PAWN;
        }
    }
    fclose(in);
    if (table[x1][y1]->color == WHITE) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (table[i][j] != NULL) {
                    if (table[i][j]->color == BLACK) {
                        if (check_valid(table, i, j, x1, y1)) {
                            return 1;
                        }
                    }
                }
            }
        }
    }
    if (table[x1][y1]->color == BLACK) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (table[i][j] != NULL) {
                    if (table[i][j]->color == WHITE) {
                        if (check_valid(table, i, j, x1, y1)) {
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

//function that prints the table on the screen like a chess board and the pieces on it
void print_screen(Piece** table) {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if (table[i][j] == NULL) {
                printf("0 ");
            }
            else {
                if (table[i][j]->color == WHITE) {
                    if (table[i][j]->type == KING) {
                        printf("WK ");
                    }
                    if (table[i][j]->type == QUEEN) {
                        printf("WQ ");
                    }
                    if (table[i][j]->type == ROOK) {
                        printf("WR ");
                    }
                    if (table[i][j]->type == BISHOP) {
                        printf("WB ");
                    }
                    if (table[i][j]->type == KNIGHT) {
                        printf("WN ");
                    }
                    if (table[i][j]->type == PAWN) {
                        printf("WP ");
                    }
                }
                if (table[i][j]->color == BLACK) {
                    if (table[i][j]->type == KING) {
                        printf("BK ");
                    }
                    if (table[i][j]->type == QUEEN) {
                        printf("BQ ");
                    }
                    if (table[i][j]->type == ROOK) {
                        printf("BR ");
                    }
                    if (table[i][j]->type == BISHOP) {
                        printf("BB ");
                    }
                    if (table[i][j]->type == KNIGHT) {
                        printf("BN ");
                    }
                    if (table[i][j]->type == PAWN) {
                        printf("BP ");
                    }
                }
            }
        }
        printf("\n"); 
    }
}

// function to check if the king can castle and is no piece between the king and the rook
int can_castle(Piece** table, int x1, int y1, int x2, int y2) {
    if (table[x1][y1]->type == KING) {
        if (x2 == x1 + 2 && y2 == y1) {
            if (table[x1 + 1][y1] == NULL && table[x1 + 2][y1] == NULL) {
                if (table[x1 + 3][y1]->type == ROOK) {
                    return 1;
                }
            }
        }
        if (x2 == x1 - 2 && y2 == y1) {
            if (table[x1 - 1][y1] == NULL && table[x1 - 2][y1] == NULL && table[x1 - 3][y1] == NULL) {
                if (table[x1 - 4][y1]->type == ROOK) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

// function to check if the king is in check

int is_king_in_check(Piece** table, int x, int y) {
    // check if the king is in check by a pawn
    if (x + 1 < 8 && y + 1 < 8) {
        if (table[x + 1][y + 1] != NULL) {
            if (table[x + 1][y + 1]->type == PAWN && table[x + 1][y + 1]->color == BLACK) {
                return 1;
            }
        }
    }
    if (x + 1 < 8 && y - 1 >= 0) {
        if (table[x + 1][y - 1] != NULL) {
            if (table[x + 1][y - 1]->type == PAWN && table[x + 1][y - 1]->color == BLACK) {
                return 1;
            }
        }
    }
    // check if the king is in check by a rook
    for (int i = x + 1; i < 8; i++) {
        if (table[i][y] != NULL) {
            if (table[i][y]->type == ROOK && table[i][y]->color == BLACK) {
                return 1;
            }
            break;
        }
    }
    for (int i = x - 1; i >= 0; i--) {
        if (table[i][y] != NULL) {
            if (table[i][y]->type == ROOK && table[i][y]->color == BLACK) {
                return 1;
            }
            break;
        }
    }
    for (int i = y + 1; i < 8; i++) {
        if (table[x][i] != NULL) {
            if (table[x][i]->type == ROOK && table[x][i]->color == BLACK) {
                return 1;
            }
            break;
        }
    }
    for (int i = y - 1; i >= 0; i--) {
        if (table[x][i] != NULL) {
            if (table[x][i]->type == ROOK && table[x][i]->color == BLACK) {
                return 1;
            }
            break;
        }
    }
    // check if the king is in check by a knight
    if (x + 2 < 8 && y + 1 < 8) {
        if (table[x + 2][y + 1] != NULL) {
            if (table[x + 2][y + 1]->type == KNIGHT && table[x + 2][y + 1]->color == BLACK) {
                return 1;
            }
        }
    }
    if (x + 2 < 8 && y - 1 >= 0) {
        if (table[x + 2][y - 1] != NULL) {
            if (table[x + 2][y - 1]->type == KNIGHT && table[x + 2][y - 1]->color == BLACK) {
                return 1;
            }
        }
    }
    if (x - 2 >= 0 && y + 1 < 8) {
        if (table[x - 2][y + 1] != NULL) {
            if (table[x - 2][y + 1]->type == KNIGHT && table[x - 2][y + 1]->color == BLACK) {
                return 1;
            }
        }
    }
    if (x - 2 >= 0 && y - 1 >= 0) {
        if (table[x - 2][y - 1] != NULL) {
            if (table[x - 2][y - 1]->type == KNIGHT && table[x - 2][y - 1]->color == BLACK) {
                return 1;
            }
        }
    }
    if (x + 1 < 8 && y + 2 < 8) {
        if (table[x + 1][y + 2] != NULL) {
            if (table[x + 1][y + 2]->type == KNIGHT && table[x + 1][y + 2]->color == BLACK) {
                return 1;
            }
        }
    }
    if (x + 1 < 8 && y - 2 >= 0) {
        if (table[x + 1][y - 2] != NULL) {
            if (table[x + 1][y - 2]->type == KNIGHT && table[x + 1][y - 2]->color == BLACK) {
                return 1;
            }
        }
    }
    if (x - 1 >= 0 && y + 2 < 8) {
        if (table[x - 1][y + 2] != NULL) {
            if (table[x - 1][y + 2]->type == KNIGHT && table[x - 1][y + 2]->color == BLACK) {
                return 1;
            }
        }
    }
    if (x - 1 >= 0 && y - 2 >= 0) {
        if (table[x - 1][y - 2] != NULL) {
            if (table[x - 1][y - 2]->type == KNIGHT && table[x - 1][y - 2]->color == BLACK) {
                return 1;
            }
        }
    }
    // check if the king is in check by a bishop
    for (int i = x + 1, j = y + 1; i < 8 && j < 8; i++, j++) {
        if (table[i][j] != NULL) {
            if (table[i][j]->type == BISHOP && table[i][j]->color == BLACK) {
                return 1;
            }
            break;
        }
    }
    for (int i = x - 1, j = y + 1; i >= 0 && j < 8; i--, j++) {
        if (table[i][j] != NULL) {
            if (table[i][j]->type == BISHOP && table[i][j]->color == BLACK) {
                return 1;
            }
            break;
        }
    }
    for (int i = x + 1, j = y - 1; i < 8 && j >= 0; i++, j--) {
        if (table[i][j] != NULL) {
            if (table[i][j]->type == BISHOP && table[i][j]->color == BLACK) {
                return 1;
            }
            break;
        }
    }
    for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--) {
        if (table[i][j] != NULL) {
            if (table[i][j]->type == BISHOP && table[i][j]->color == BLACK) {
                return 1;
            }
            break;
        }
    }
    // check if the king is in check by a queen
    for (int i = x + 1; i < 8; i++) {
        if (table[i][y] != NULL) {
            if (table[i][y]->type == QUEEN && table[i][y]->color == BLACK) {
                return 1;
            }
            break;
        }
    }
    for (int i = x - 1; i >= 0; i--) {
        if (table[i][y] != NULL) {
            if (table[i][y]->type == QUEEN && table[i][y]->color == BLACK) {
                return 1;
            }
            break;
        }
    }
    for (int i = y + 1; i < 8; i++) {
        if (table[x][i] != NULL) {
            if (table[x][i]->type == QUEEN && table[x][i]->color == BLACK) {
                return 1;
            }
            break;
        }
    }
    for (int i = y - 1; i >= 0; i--) {
        if (table[x][i] != NULL) {
            if (table[x][i]->type == QUEEN && table[x][i]->color == BLACK) {
                return 1;
            }
            break;
        }
    }
    for (int i = x + 1, j = y + 1; i < 8 && j < 8; i++, j++) {
        if (table[i][j] != NULL) {
            if (table[i][j]->type == QUEEN && table[i][j]->color == BLACK) {
                return 1;
            }
            break;
        }
    }
    for (int i = x - 1, j = y + 1; i >= 0 && j < 8; i--, j++) {
        if (table[i][j] != NULL) {
            if (table[i][j]->type == QUEEN && table[i][j]->color == BLACK) {
                return 1;
            }
            break;
        }
    }
    for (int i = x + 1, j = y - 1; i < 8 && j >= 0; i++, j--) {
        if (table[i][j] != NULL) {
            if (table[i][j]->type == QUEEN && table[i][j]->color == BLACK) {
                return 1;
            }
            break;
        }
    }
    for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--) {
        if (table[i][j] != NULL) {
            if (table[i][j]->type == QUEEN && table[i][j]->color == BLACK) {
                return 1;
            }
            break;
        }
    }
    return 0;
}