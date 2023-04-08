#include "table.h"

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
bool check_valid(Piece** table, int x1, int y1, int x2, int y2) {
    if(table[x1][y1] == NULL) {
        return false;
    }
    if(table[x2][y2] != NULL) {
        if(table[x1][y1]->color == table[x2][y2]->color) {
            return false;
        }
    }
    if(table[x1][y1]->type == PAWN) {
        if(table[x1][y1]->color == WHITE) {
            if(x1 == 6) {
                if(x2 == 4 && y2 == y1) {
                    if(table[x2][y2] == NULL) {
                        return true;
                    }
                }
            }
            if(x2 == x1 - 1 && y2 == y1) {
                if(table[x2][y2] == NULL) {
                    return true;
                }
            }
            if(x2 == x1 - 1 && (y2 == y1 + 1 || y2 == y1 - 1)) {
                if(table[x2][y2] != NULL) {
                    return true;
                }
            }
        } else {
            if(x1 == 1) {
                if(x2 == 3 && y2 == y1) {
                    if(table[x2][y2] == NULL) {
                        return true;
                    }
                }
            }
            if(x2 == x1 + 1 && y2 == y1) {
                if(table[x2][y2] == NULL) {
                    return true;
                }
            }
            if(x2 == x1 + 1 && (y2 == y1 + 1 || y2 == y1 - 1)) {
                if(table[x2][y2] != NULL) {
                    return true;
                }
            }
        }
    } else if(table[x1][y1]->type == ROOK) {
        if(x2 == x1) {
            if(y2 > y1) {
                for (int i = y1 + 1; i < y2; i++) {
                    if(table[x2][i] != NULL) {
                        return false;
                    }
                }
                return true;
            } else {
                for (int i = y1 - 1; i > y2; i--) {
                    if(table[x2][i] != NULL) {
                        return false;
                    }
                }
                return true;
            }
        } else if(y2 == y1) {
            if(x2 > x1) {
                for (int i = x1 + 1; i < x2; i++) {
                    if(table[i][y2] != NULL) {
                        return false;
                    }
                }
            } else {
                for (int i = x1 - 1; i > x2; i--) {
                    if(table[i][y2] != NULL) {
                        return false;
                    }
                }
            }
        }
    
    } else if(table[x1][y1]->type == KNIGHT) {
        if((x2 == x1 + 2 && y2 == y1 + 1) || (x2 == x1 + 2 && y2 == y1 - 1) || (x2 == x1 - 2 && y2 == y1 + 1) || (x2 == x1 - 2 && y2 == y1 - 1) || (x2 == x1 + 1 && y2 == y1 + 2) || (x2 == x1 + 1 && y2 == y1 - 2) || (x2 == x1 - 1 && y2 == y1 + 2) || (x2 == x1 - 1 && y2 == y1 - 2)) {
            return true;
        }
    } else if(table[x1][y1]->type == BISHOP) {
        if(x2 > x1 && y2 > y1) {
            for (int i = 1; i < x2 - x1; i++) {
                if(table[x1 + i][y1 + i] != NULL) {
                    return false;
                }
            }
            return true;
        } else if(x2 > x1 && y2 < y1) {
            for (int i = 1; i < x2 - x1; i++) {
                if(table[x1 + i][y1 - i] != NULL) {
                    return false;
                }
            }
            return true;
        } else if(x2 < x1 && y2 > y1) {
            for (int i = 1; i < x1 - x2; i++) {
                if(table[x1 - i][y1 + i] != NULL) {
                    return false;
                }
            }
            return true;
        } else if(x2 < x1 && y2 < y1) {
            for (int i = 1; i < x1 - x2; i++) {
                if(table[x1 - i][y1 - i] != NULL) {
                    return false;
                }
            }
            return true;
        }
    } else if(table[x1][y1]->type == QUEEN) {
        if(x2 == x1) {
            if(y2 > y1) {
                for (int i = y1 + 1; i < y2; i++) {
                    if(table[x2][i] != NULL) {
                        return false;
                    }
                }
                return true;
            } else {
                for (int i = y1 - 1; i > y2; i--) {
                    if(table[x2][i] != NULL) {
                        return false;
                    }
                }
                return true;
            }
        } else if(y2 == y1) {
            if(x2 > x1) {
                for (int i = x1 + 1; i < x2; i++) {
                    if(table[i][y2] != NULL) {
                        return false;
                    }
                }
            } else {
                for (int i = x1 - 1; i > x2; i--) {
                    if(table[i][y2] != NULL) {
                        return false;
                    }
                }
            }
        } else if(x2 > x1 && y2 > y1) {
            for (int i = 1; i < x2 - x1; i++) {
                if(table[x1 + i][y1 + i] != NULL) {
                    return false;
                }
            }
            return true;
        } else if(x2 > x1 && y2 < y1) {
            for (int i = 1; i < x2 - x1; i++) {
                if(table[x1 + i][y1 - i] != NULL) {
                    return false;
                }
            }
            return true;
        } else if(x2 < x1 && y2 > y1) {
            for (int i = 1; i < x1 - x2; i++) {
                if(table[x1 - i][y1 + i] != NULL) {
                    return false;
                }
            }
            return true;
        } else if(x2 < x1 && y2 < y1) {
            for (int i = 1; i < x1 - x2; i++) {
                if(table[x1 - i][y1 - i] != NULL) {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}
