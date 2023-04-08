#include "table.h"
#include <string.h>

/* this function creates a matrix that represents the chess table*/

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

void** promote_pawn(void** table, int x, int y, piece_type_t type) {
    if (((Piece**)table)[x][y] != NULL && ((Piece**)table)[x][y]->type == PAWN) {
        ((Piece**)table)[x][y]->type = type;
    }
    return table;
}

/*function that checks if chess move is valid. this means you should check if the position where you move is NULL, and if it is not,
you should check if your chess piece has the right movement to go there, and if a piece is there, check that is doesnt have the same 
color. lastly, you should check that if you move the wanted piece, your king cant be taken by other color chess pieces. NOTE THAT 
ONLY table->type->knight can jump over other piece. other pieces cand go to the wanted position if they have to go through an occupied
position on the table.*/
bool check_valid(void** table, int x1, int y1, int x2, int y2) {
    if (x1 < 0 || x1 > 7 || x2 < 0 || x2 > 7 || y1 < 0 || y1 > 7 || y2 < 0 || y2 > 7) {
        return false;
    }
    if (((Piece**)table)[x1][y1] == NULL) {
        return false;
    }
    if (((Piece**)table)[x2][y2] != NULL && ((Piece**)table)[x2][y2]->color == ((Piece**)table)[x1][y1]->color) {
        return false;
    }
    switch (((Piece**)table)[x1][y1]->type) {
        case PAWN:
            if (((Piece**)table)[x1][y1]->color == BLACK) {
                if (x2 == x1 + 1 && y2 == y1 && ((Piece**)table)[x2][y2] == NULL) {
                    return true;
                } else if (x2 == x1 + 1 && (y2 == y1 + 1 || y2 == y1 - 1) && ((Piece**)table)[x2][y2] != NULL) {
                    return true;
                } else if (x1 == 1 && x2 == x1 + 2 && y2 == y1 && ((Piece**)table)[x2][y2] == NULL) {
                    return true;
                }
            } else {
                if (x2 == x1 - 1 && y2 == y1 && ((Piece**)table)[x2][y2] == NULL) {
                    return true;
                } else if (x2 == x1 - 1 && (y2 == y1 + 1 || y2 == y1 - 1) && ((Piece**)table)[x2][y2] != NULL) {
                    return true;
                } else if (x1 == 6 && x2 == x1 - 2 && y2 == y1 && ((Piece**)table)[x2][y2] == NULL) {
                    return true;
                }
            }
            // case for promoting a pawn that reaches the other side of the table and uses the function promote_pawn
            if (x2 == 0 || x2 == 7) {
                promote_pawn(table, x2, y2, QUEEN);
                return true;
            }
            break;
        case BISHOP:
            if (abs(x2 - x1) == abs(y2 - y1)) {
                if (x2 > x1 && y2 > y1) {
                    for (int i = 1; i < abs(x2 - x1); i++) {
                        if (((Piece**)table)[x1 + i][y1 + i] != NULL) {
                            return false;
                        }
                    }
                } else if (x2 > x1 && y2 < y1) {
                    for (int i = 1; i < abs(x2 - x1); i++) {
                        if (((Piece**)table)[x1 + i][y1 - i] != NULL) {
                            return false;
                        }
                    }
                } else if (x2 < x1 && y2 > y1) {
                    for (int i = 1; i < abs(x2 - x1); i++) {
                        if (((Piece**)table)[x1 - i][y1 + i] != NULL) {
                            return false;
                        }
                    }
                } else {
                    for (int i = 1; i < abs(x2 - x1); i++) {
                        if (((Piece**)table)[x1 - i][y1 - i] != NULL) {
                            return false;
                        }
                    }
                }
                return true;
            }
            break;
        case KNIGHT:
            if ((abs(x2 - x1) == 2 && abs(y2 - y1) == 1) || (abs(x2 - x1) == 1 && abs(y2 - y1) == 2)) {
                return true;
            }
            break;
        case KING:
            if (abs(x2 - x1) <= 1 && abs(y2 - y1) <= 1) {
                return true;
            }
            break;
        case QUEEN:
            if (abs(x2 - x1) == abs(y2 - y1)) {
                if (x2 > x1 && y2 > y1) {
                    for (int i = 1; i < abs(x2 - x1); i++) {
                        if (((Piece**)table)[x1 + i][y1 + i] != NULL) {
                            return false;
                        }
                    }
                } else if (x2 > x1 && y2 < y1) {
                    for (int i = 1; i < abs(x2 - x1); i++) {
                        if (((Piece**)table)[x1 + i][y1 - i] != NULL) {
                            return false;
                        }
                    }
                } else if (x2 < x1 && y2 > y1) {
                    for (int i = 1; i < abs(x2 - x1); i++) {
                        if (((Piece**)table)[x1 - i][y1 + i] != NULL) {
                            return false;
                        }
                    }
                } else {
                    for (int i = 1; i < abs(x2 - x1); i++) {
                        if (((Piece**)table)[x1 - i][y1 - i] != NULL) {
                            return false;
                        }
                    }
                }
                return true;
            } else if (x2 == x1 || y2 == y1) {
                if (x2 > x1 && y2 == y1) {
                    for (int i = 1; i < abs(x2 - x1); i++) {
                        if (((Piece**)table)[x1 + i][y1] != NULL) {
                            return false;
                        }
                    }
                } else if (x2 < x1 && y2 == y1) {
                    for (int i = 1; i < abs(x2 - x1); i++) {
                        if (((Piece**)table)[x1 - i][y1] != NULL) {
                            return false;
                        }
                    }
                } else if (x2 == x1 && y2 > y1) {
                    for (int i = 1; i < abs(y2 - y1); i++) {
                        if (((Piece**)table)[x1][y1 + i] != NULL) {
                            return false;
                        }
                    }
                } else {
                    for (int i = 1; i < abs(y2 - y1); i++) {
                        if (((Piece**)table)[x1][y1 - i] != NULL) {
                            return false;
                        }
                    }
                }
                return true;
            }
            break;
        case ROOK:
            if (x2 == x1 || y2 == y1) {
                if (x2 > x1 && y2 == y1) {
                    for (int i = 1; i < abs(x2 - x1); i++) {
                        if (((Piece**)table)[x1 + i][y1] != NULL) {
                            return false;
                        }
                    }
                } else if (x2 < x1 && y2 == y1) {
                    for (int i = 1; i < abs(x2 - x1); i++) {
                        if (((Piece**)table)[x1 - i][y1] != NULL) {
                            return false;
                        }
                    }
                } else if (x2 == x1 && y2 > y1) {
                    for (int i = 1; i < abs(y2 - y1); i++) {
                        if (((Piece**)table)[x1][y1 + i] != NULL) {
                            return false;
                        }
                    }
                } else {
                    for (int i = 1; i < abs(y2 - y1); i++) {
                        if (((Piece**)table)[x1][y1 - i] != NULL) {
                            return false;
                        }
                    }
                }
                return true;
            }
            break;
        }
    return false;
}

// Implement a function to convert your chess matrix to FEN (Forsyth–Edwards Notation) format and returns the value into a string
// respecting that patter: rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1 where the lower case are the white peaces and the upper case are the black peaces

char* fen(void** table) {
    char* fen = (char*)malloc(100 * sizeof(char));
    int count = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (((Piece**)table)[i][j] == NULL) {
                count++;
            } else {
                if (count != 0) {
                    fen[strlen(fen)] = count + '0';
                    count = 0;
                }
                switch (((Piece**)table)[i][j]->type) {
                case PAWN:
                    if (((Piece**)table)[i][j]->color == WHITE) {
                        fen[strlen(fen)] = 'P';
                    } else {
                        fen[strlen(fen)] = 'p';
                    }
                    break;
                case BISHOP:
                    if (((Piece**)table)[i][j]->color == WHITE) {
                        fen[strlen(fen)] = 'B';
                    } else {
                        fen[strlen(fen)] = 'b';
                    }
                    break;
                case KNIGHT:
                    if (((Piece**)table)[i][j]->color == WHITE) {
                        fen[strlen(fen)] = 'N';
                    } else {
                        fen[strlen(fen)] = 'n';
                    }
                    break;
                case KING:
                    if (((Piece**)table)[i][j]->color == WHITE) {
                        fen[strlen(fen)] = 'K';
                    } else {
                        fen[strlen(fen)] = 'k';
                    }
                    break;
                case QUEEN:
                    if (((Piece**)table)[i][j]->color == WHITE) {
                        fen[strlen(fen)] = 'Q';
                    } else {
                        fen[strlen(fen)] = 'q';
                    }
                    break;
                case ROOK:
                    if (((Piece**)table)[i][j]->color == WHITE) {
                        fen[strlen(fen)] = 'R';
                    } else {
                        fen[strlen(fen)] = 'r';
                    }
                    break;
                }
            }
        }
        if (count != 0) {
            fen[strlen(fen)] = count + '0';
            count = 0;
        }
        if (i != 7) {
            fen[strlen(fen)] = '/';
        }
    }
    fen[strlen(fen)] = ' ';
    fen[strlen(fen)] = 'w';
    fen[strlen(fen)] = ' ';
    fen[strlen(fen)] = 'K';
    fen[strlen(fen)] = 'Q';
    fen[strlen(fen)] = 'k';
    fen[strlen(fen)] = 'q';
    fen[strlen(fen)] = ' ';
    fen[strlen(fen)] = '-';
    fen[strlen(fen)] = ' ';
    fen[strlen(fen)] = '0';
    fen[strlen(fen)] = ' ';
    fen[strlen(fen)] = '1';
    return fen;
}

// Implement a function that moves a piece from a position to another position. the position are represented by a string like "a1" or "h8". the positions are given as arguments. it checks if the move is valid

void move_piece(void** table, int from_x, int from_y, int to_x, int to_y) {
    if (check_valid(table, from_x, from_y, to_x, to_y)) {
        ((Piece**)table)[to_x][to_y] = ((Piece**)table)[from_x][from_y];
        ((Piece**)table)[from_x][from_y] = NULL;
    }
}
