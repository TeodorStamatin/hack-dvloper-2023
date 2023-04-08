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
<<<<<<< HEAD
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

/* the following function should check if the game is ended or not; the chess game is ended if the king can be taken from the oppsite team, even if it moves one position around him*/
bool isGameEnded(void* table) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (((Piece**)table)[i][j] != NULL) {
                if (((Piece**)table)[i][j]->type == KING) {
                    for (int k = 0; k < 8; k++) {
                        for (int l = 0; l < 8; l++) {
                            if (((Piece**)table)[k][l] != NULL) {
                                if (((Piece**)table)[k][l]->color != ((Piece**)table)[i][j]->color) {
                                    if (check_valid(table, k, l, i, j)) {
                                        return true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}
=======
int check_valid(void** table, int x1, int y1, int x2, int y2) {
    if (x1 < 0 || x1 > 7 || x2 < 0 || x2 > 7 || y1 < 0 || y1 > 7 || y2 < 0 || y2 > 7) {
        return 0;
    }
    if (((Piece**)table)[x1][y1] == NULL) {
        return 0;
    }
    if (((Piece**)table)[x2][y2] != NULL && ((Piece**)table)[x2][y2]->color == ((Piece**)table)[x1][y1]->color) {
        return 0;
    }
    if (x1 == x2 && y1 == y2) {
        return 0;
    }
    switch (((Piece**)table)[x1][y1]->type) {
        case PAWN:
            if (((Piece**)table)[x1][y1]->color == BLACK) {
                if (x2 == x1 + 1 && y2 == y1 && ((Piece**)table)[x2][y2] == NULL) {
                    return 1;
                } else if (x2 == x1 + 1 && (y2 == y1 + 1 || y2 == y1 - 1) && ((Piece**)table)[x2][y2] != NULL) {
                    return 1;
                } else if (x1 == 1 && x2 == x1 + 2 && y2 == y1 && ((Piece**)table)[x2][y2] == NULL) {
                    return 1;
                }
            } else {
                if (x2 == x1 - 1 && y2 == y1 && ((Piece**)table)[x2][y2] == NULL) {
                    return 1;
                } else if (x2 == x1 - 1 && (y2 == y1 + 1 || y2 == y1 - 1) && ((Piece**)table)[x2][y2] != NULL) {
                    return 1;
                } else if (x1 == 6 && x2 == x1 - 2 && y2 == y1 && ((Piece**)table)[x2][y2] == NULL) {
                    return 1;
                }
            }
            // case for promoting a pawn that reaches the other side of the table and uses the function promote_pawn
            if (x2 == 0 || x2 == 7) {
                return 1;
            }
            break;
        case BISHOP:
            if (abs(x2 - x1) == abs(y2 - y1)) {
                if (x2 > x1 && y2 > y1) {
                    for (int i = 1; i < abs(x2 - x1); i++) {
                        if (((Piece**)table)[x1 + i][y1 + i] != NULL) {
                            return 0;
                        }
                    }
                } else if (x2 > x1 && y2 < y1) {
                    for (int i = 1; i < abs(x2 - x1); i++) {
                        if (((Piece**)table)[x1 + i][y1 - i] != NULL) {
                            return 0;
                        }
                    }
                } else if (x2 < x1 && y2 > y1) {
                    for (int i = 1; i < abs(x2 - x1); i++) {
                        if (((Piece**)table)[x1 - i][y1 + i] != NULL) {
                            return 0;
                        }
                    }
                } else {
                    for (int i = 1; i < abs(x2 - x1); i++) {
                        if (((Piece**)table)[x1 - i][y1 - i] != NULL) {
                            return 0;
                        }
                    }
                }
                return 1;
            }
            break;
        case KNIGHT:
            if ((abs(x2 - x1) == 2 && abs(y2 - y1) == 1) || (abs(x2 - x1) == 1 && abs(y2 - y1) == 2)) {
                return 1;
            }
            break;
        case KING:
            if (abs(x2 - x1) <= 1 && abs(y2 - y1) <= 1) {
                return 1;
            }
            // check if the king can't be taken by other color chess pieces if he moves to the wanted position
            if (x2 == x1 && y2 == y1 + 1) {
                if (((Piece**)table)[x2][y2 + 1] != NULL && ((Piece**)table)[x2][y2 + 1]->type == ROOK && ((Piece**)table)[x2][y2 + 1]->color != ((Piece**)table)[x1][y1]->color) {
                    return 0;
                }
            } else if (x2 == x1 && y2 == y1 - 1) {
                if (((Piece**)table)[x2][y2 - 2] != NULL && ((Piece**)table)[x2][y2 - 2]->type == ROOK && ((Piece**)table)[x2][y2 - 2]->color != ((Piece**)table)[x1][y1]->color) {
                    return 0;
                }
            }
            break;
        case QUEEN:
            if (abs(x2 - x1) == abs(y2 - y1)) {
                if (x2 > x1 && y2 > y1) {
                    for (int i = 1; i < abs(x2 - x1); i++) {
                        if (((Piece**)table)[x1 + i][y1 + i] != NULL) {
                            return 0;
                        }
                    }
                } else if (x2 > x1 && y2 < y1) {
                    for (int i = 1; i < abs(x2 - x1); i++) {
                        if (((Piece**)table)[x1 + i][y1 - i] != NULL) {
                            return 0;
                        }
                    }
                } else if (x2 < x1 && y2 > y1) {
                    for (int i = 1; i < abs(x2 - x1); i++) {
                        if (((Piece**)table)[x1 - i][y1 + i] != NULL) {
                            return 0;
                        }
                    }
                } else {
                    for (int i = 1; i < abs(x2 - x1); i++) {
                        if (((Piece**)table)[x1 - i][y1 - i] != NULL) {
                            return 0;
                        }
                    }
                }
                return 1;
            } else if (x2 == x1 || y2 == y1) {
                if (x2 > x1 && y2 == y1) {
                    for (int i = 1; i < abs(x2 - x1); i++) {
                        if (((Piece**)table)[x1 + i][y1] != NULL) {
                            return 0;
                        }
                    }
                } else if (x2 < x1 && y2 == y1) {
                    for (int i = 1; i < abs(x2 - x1); i++) {
                        if (((Piece**)table)[x1 - i][y1] != NULL) {
                            return 0;
                        }
                    }
                } else if (x2 == x1 && y2 > y1) {
                    for (int i = 1; i < abs(y2 - y1); i++) {
                        if (((Piece**)table)[x1][y1 + i] != NULL) {
                            return 0;
                        }
                    }
                } else {
                    for (int i = 1; i < abs(y2 - y1); i++) {
                        if (((Piece**)table)[x1][y1 - i] != NULL) {
                            return 0;
                        }
                    }
                }
                return 1;
            }
            break;
        case ROOK:
            if (x2 == x1 || y2 == y1) {
                if (x2 > x1 && y2 == y1) {
                    for (int i = 1; i < abs(x2 - x1); i++) {
                        if (((Piece**)table)[x1 + i][y1] != NULL) {
                            return 0;
                        }
                    }
                } else if (x2 < x1 && y2 == y1) {
                    for (int i = 1; i < abs(x2 - x1); i++) {
                        if (((Piece**)table)[x1 - i][y1] != NULL) {
                            return 0;
                        }
                    }
                } else if (x2 == x1 && y2 > y1) {
                    for (int i = 1; i < abs(y2 - y1); i++) {
                        if (((Piece**)table)[x1][y1 + i] != NULL) {
                            return 0;
                        }
                    }
                } else {
                    for (int i = 1; i < abs(y2 - y1); i++) {
                        if (((Piece**)table)[x1][y1 - i] != NULL) {
                            return 0;
                        }
                    }
                }
                return 1;
            }
        break;
    }
    return 0;
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

void** move_piece(void** table, int from_x, int from_y, int to_x, int to_y) {
    if (check_valid(table, from_x, from_y, to_x, to_y)) {
        // daca piesa oponentului este capturata se elibereaza memoria
        if (((Piece**)table)[to_x][to_y] != NULL) {
            free(((Piece**)table)[to_x][to_y]);
        }
        ((Piece**)table)[to_x][to_y] = ((Piece**)table)[from_x][from_y];
        ((Piece**)table)[from_x][from_y] = NULL;
    }
    return table;
}

// check that king can't move anymore, check all the cases around the king and if there is a piece that can kill the king, return 1, else return 0
int is_king_in_checkmate(void** board, int king_x, int king_y) {
    // Verificăm dacă regele este deja în șah
    if (is_king_in_check(board, king_x, king_y)) {
        // Dacă regele este deja în șah, încercăm să găsim o mutare care să scoată regele din șah
        for (int from_x = 0; from_x < 8; from_x++) {
            for (int from_y = 0; from_y < 8; from_y++) {
                if (((Piece**)board)[from_x][from_y] == NULL) {
                    continue; // Nu există piesă pe poziția (from_x, from_y)
                }
                if (((Piece**)board)[from_x][from_y]->color == ((Piece**)board)[king_x][king_y]->color) {
                    // Dacă piesa de pe poziția (from_x, from_y) este de aceeași culoare ca regele, încercăm să găsim o mutare validă pentru acea piesă
                    for (int to_x = 0; to_x < 8; to_x++) {
                        for (int to_y = 0; to_y < 8; to_y++) {
                            if (check_valid(board, from_x, from_y, to_x, to_y)) {
                                // Dacă mutarea este validă, încercăm să o efectuăm și verificăm dacă regele mai este în șah
                                void** new_board = move_piece(board, from_x, from_y, to_x, to_y);
                                bool king_in_check = is_king_in_check(new_board, king_x, king_y);
                                free_matrix(new_board);
                                if (!king_in_check) {
                                    return 0; // Am găsit o mutare care scoate regele din șah
                                }
                            }
                        }
                    }
                }
            }
        }
        // Dacă nu am găsit nicio mutare validă care să scoată regele din șah, atunci regele este în șah mat
        return 1;
    }
    // Dacă regele nu este în șah, atunci nu este nici în șah mat
    return 0;
}

// check if the king is in check, if it is, return 1, else return 0
int is_king_in_check(void** board, int king_x, int king_y) {
    // Verificăm dacă regele este în șah de către o piesă de tip pion
    if (king_x > 0 && king_y > 0 && ((Piece**)board)[king_x - 1][king_y - 1] != NULL && ((Piece**)board)[king_x - 1][king_y - 1]->type == PAWN && !((Piece**)board)[king_x - 1][king_y - 1]->color) {
        return 1;
    }
    if (king_x > 0 && king_y < 8 - 1 && ((Piece**)board)[king_x - 1][king_y + 1] != NULL && ((Piece**)board)[king_x - 1][king_y + 1]->type == PAWN && !((Piece**)board)[king_x - 1][king_y + 1]->color) {
        return 1;
    }
    // Verificăm dacă regele este în șah de către o piesă de tip cal
    for (int i = -2; i <= 2; i++) {
        for (int j = -2; j <= 2; j++) {
            if (abs(i) + abs(j) == 3 && king_x + i >= 0 && king_x + i < 8 && king_y + j >= 0 && king_y + j < 8 && ((Piece**)board)[king_x + i][king_y + j] != NULL && ((Piece**)board)[king_x + i][king_y + j]->type == KNIGHT && ((Piece**)board)[king_x + i][king_y + j]->color != ((Piece**)board)[king_x][king_y]->color) {
                return 1;
            }
        }
    }
    // Verificăm dacă regele este în șah de către o piesă de tip nebun sau regină
    for (int i = -1; i <= 1; i += 2) {
        for (int j = -1; j <= 1; j += 2) {
            for (int k = 1; k < 8; k++) {
                if (king_x + i * k >= 0 && king_x + i * k < 8 && king_y + j * k >= 0 && king_y + j * k < 8 && ((Piece**)board)[king_x + i * k][king_y + j * k] != NULL) {
                    if (((Piece**)board)[king_x + i * k][king_y + j * k]->type == BISHOP && ((Piece**)board)[king_x + i * k][king_y + j * k]->color != ((Piece**)board)[king_x][king_y]->color) {
                        return 1;
                    }
                    if (((Piece**)board)[king_x + i * k][king_y + j * k]->type == QUEEN && ((Piece**)board)[king_x + i * k][king_y + j * k]->color != ((Piece**)board)[king_x][king_y]->color) {
                        return 1;
                    }
                    break;
                }
            }
        }
    }
    // Verificăm dacă regele este în șah de către o piesă de tip tura sau regină
    for (int i = -1; i <= 1; i += 2) {
        for (int k = 1; k < 8; k++) {
            if (king_x + i * k >= 0 && king_x + i * k < 8 && ((Piece**)board)[king_x + i * k][king_y] != NULL) {
                if (((Piece**)board)[king_x + i * k][king_y]->type == ROOK && ((Piece**)board)[king_x + i * k][king_y]->color != ((Piece**)board)[king_x][king_y]->color) {
                    return 1;
                }
                if (((Piece**)board)[king_x + i * k][king_y]->type == QUEEN && ((Piece**)board)[king_x + i * k][king_y]->color != ((Piece**)board)[king_x][king_y]->color) {
                    return 1;
                }
                break;
            }
        }
        for (int k = 1; k < 8; k++) {
            if (king_y + i * k >= 0 && king_y + i * k < 8 && ((Piece**)board)[king_x][king_y + i * k] != NULL) {
                if (((Piece**)board)[king_x][king_y + i * k]->type == ROOK && ((Piece**)board)[king_x][king_y + i * k]->color != ((Piece**)board)[king_x][king_y]->color) {
                    return 1;
                }
                if (((Piece**)board)[king_x][king_y + i * k]->type == QUEEN && ((Piece**)board)[king_x][king_y + i * k]->color != ((Piece**)board)[king_x][king_y]->color) {
                    return 1;
                }
                break;
            }
        }
    }
    // Verificăm dacă regele este în șah de către o piesă de tip rege
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i != 0 || j != 0) {
                if (king_x + i >= 0 && king_x + i < 8 && king_y + j >= 0 && king_y + j < 8 && ((Piece**)board)[king_x + i][king_y + j] != NULL && ((Piece**)board)[king_x + i][king_y + j]->type == KING && ((Piece**)board)[king_x + i][king_y + j]->color != ((Piece**)board)[king_x][king_y]->color) {
                    return 1;
                }
            }
        }
    }
    return 0;
}
>>>>>>> 6cc41c473ca818dcf9766c13e3029e15e0af4142
