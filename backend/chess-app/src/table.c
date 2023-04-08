#include "table.h"
#include <string.h>

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

void promote_pawn(void*** table, int x, int y, piece_type_t type) {
    if ((*((Piece***)table))[x][y] != NULL && ((Piece**)table)[x][y]->type == PAWN) {
        (*((Piece***)table))[x][y]->type = type;
    }
    return;
}

/*function that checks if chess move is valid. this means you should check if the position where you move is NULL, and if it is not,
you should check if your chess piece has the right movement to go there, and if a piece is there, check that is doesnt have the same 
color. lastly, you should check that if you move the wanted piece, your king cant be taken by other color chess pieces. NOTE THAT 
ONLY table->type->knight can jump over other piece. other pieces cand go to the wanted position if they have to go through an occupied
position on the table.*/


int check_valid(Piece** table, FILE *in) {
    char buf[100];
    fgets(buf, 100, in);
    char* token = strtok(buf, ",");
    char* color = strtok(token, "_");
    char* type = strtok(NULL, "_");
    int x1 = atoi(strtok(NULL, ","));
    int y1 = atoi(strtok(NULL, ","));
    int x2 = atoi(strtok(NULL, ","));
    int y2 = atoi(strtok(NULL, ","));

    if (x1 < 0 || x1 > 7 || x2 < 0 || x2 > 7 || y1 < 0 || y1 > 7 || y2 < 0 || y2 > 7) {
        return 0;
    }
    if (((Piece**)table)[x1][y1] == NULL) {
        return 0;
    }
    if (strcmp(color, "WHITE") == 0 && ((Piece**)table)[x1][y1]->color == BLACK) {
        return 0;
    }
    if (strcmp(color, "BLACK") == 0 && ((Piece**)table)[x1][y1]->color == WHITE) {
        return 0;
    }
    if (strcmp(type, "PAWN") == 0) {
        if (((Piece**)table)[x1][y1]->color == WHITE) {
            if (x1 == 1 && x2 == 3 && y1 == y2 && ((Piece**)table)[x2][y2] == NULL) {
                return 1;
            }
            if (x1 == 1 && x2 == 2 && y1 == y2 && ((Piece**)table)[x2][y2] == NULL) {
                return 1;
            }
            if (x1 == 6 && x2 == 4 && y1 == y2 && ((Piece**)table)[x2][y2] == NULL) {
                return 1;
            }
            if (x1 == 6 && x2 == 5 && y1 == y2 && ((Piece**)table)[x2][y2] == NULL) {
                return 1;
            }
            if (x1 == x2 && y1 == y2) {
                return 0;
            }
            if (x1 == x2 && y1 != y2) {
                return 0;
            }
            if (x1 != x2 && y1 == y2) {
                if (x2 - x1 == 1 && ((Piece**)table)[x2][y2] == NULL) {
                    return 1;
                }
                return 0;
            }
            if (x1 != x2 && y1 != y2) {
                if (x2 - x1 == 1 && abs(y2 - y1) == 1 && ((Piece**)table)[x2][y2] != NULL) {
                    return 1;
                }
                return 0;
            }
        }
        if (((Piece**)table)[x1][y1]->color == BLACK) {
            if (x1 == 6 && x2 == 4 && y1 == y2 && ((Piece**)table)[x2][y2] == NULL) {
                return 1;
            }
            if (x1 == 6 && x2 == 5 && y1 == y2 && ((Piece**)table)[x2][y2] == NULL) {
                return 1;
            }
            if (x1 == 1 && x2 == 3 && y1 == y2 && ((Piece**)table)[x2][y2] == NULL) {
                return 1;
            }
            if (x1 == 1 && x2 == 2 && y1 == y2 && ((Piece**)table)[x2][y2] == NULL) {
                return 1;
            }
            if (x1 == x2 && y1 == y2) {
                return 0;
            }
            if (x1 == x2 && y1 != y2) {
                return 0;
            }
            if (x1 != x2 && y1 == y2) {
                if (x1 - x2 == 1 && ((Piece**)table)[x2][y2] == NULL) {
                    return 1;
                }
                return 0;
            }
            if (x1 != x2 && y1 != y2) {
                if (x1 - x2 == 1 && abs(y2 - y1) == 1 && ((Piece**)table)[x2][y2] != NULL) {
                    return 1;
                }
                return 0;
            }
        }
    }
    if (strcmp(type, "ROOK") == 0) {
        if (x1 == x2 && y1 == y2) {
            return 0;
        }
        if (x1 == x2 && y1 != y2) {
            if (y1 < y2) {
                for (int i = y1 + 1; i < y2; i++) {
                    if (((Piece**)table)[x1][i] != NULL) {
                        return 0;
                    }
                }
                if (((Piece**)table)[x2][y2] != NULL && ((Piece**)table)[x2][y2]->color == ((Piece**)table)[x1][y1]->color) {
                    return 0;
                }
                return 1;
            }
            if (y1 > y2) {
                for (int i = y1 - 1; i > y2; i--) {
                    if (((Piece**)table)[x1][i] != NULL) {
                        return 0;
                    }
                }
                if (((Piece**)table)[x2][y2] != NULL && ((Piece**)table)[x2][y2]->color == ((Piece**)table)[x1][y1]->color) {
                    return 0;
                }
                return 1;
            }
        }
        if (x1 != x2 && y1 == y2) {
            if (x1 < x2) {
                for (int i = x1 + 1; i < x2; i++) {
                    if (((Piece**)table)[i][y1] != NULL) {
                        return 0;
                    }
                }
                if (((Piece**)table)[x2][y2] != NULL && ((Piece**)table)[x2][y2]->color == ((Piece**)table)[x1][y1]->color) {
                    return 0;
                }
                return 1;
            }
            if (x1 > x2) {
                for (int i = x1 - 1; i > x2; i--) {
                    if (((Piece**)table)[i][y1] != NULL) {
                        return 0;
                    }
                }
                if (((Piece**)table)[x2][y2] != NULL && ((Piece**)table)[x2][y2]->color == ((Piece**)table)[x1][y1]->color) {
                    return 0;
                }
                return 1;
            }
        }
    }
    if (strcmp(type, "KNIGHT") == 0) {
        if (x1 == x2 && y1 == y2) {
            return 0;
        }
        if (x1 == x2 && y1 != y2) {
            return 0;
        }
        if (x1 != x2 && y1 == y2) {
            return 0;
        }
        if (x1 != x2 && y1 != y2) {
            if (abs(x2 - x1) == 2 && abs(y2 - y1) == 1) {
                if (((Piece**)table)[x2][y2] != NULL && ((Piece**)table)[x2][y2]->color == ((Piece**)table)[x1][y1]->color) {
                    return 0;
                }
                return 1;
            }
            if (abs(x2 - x1) == 1 && abs(y2 - y1) == 2) {
                if (((Piece**)table)[x2][y2] != NULL && ((Piece**)table)[x2][y2]->color == ((Piece**)table)[x1][y1]->color) {
                    return 0;
                }
                return 1;
            }
            return 0;
        }
    }
    if (strcmp(type, "BISHOP") == 0) {
        if (x1 == x2 && y1 == y2) {
            return 0;
        }
        if (x1 == x2 && y1 != y2) {
            return 0;
        }
        if (x1 != x2 && y1 == y2) {
            return 0;
        }
        if (x1 != x2 && y1 != y2) {
            if (abs(x2 - x1) == abs(y2 - y1)) {
                if (x1 < x2 && y1 < y2) {
                    for (int i = 1; i < x2 - x1; i++) {
                        if (((Piece**)table)[x1 + i][y1 + i] != NULL) {
                            return 0;
                        }
                    }
                    if (((Piece**)table)[x2][y2] != NULL && ((Piece**)table)[x2][y2]->color == ((Piece**)table)[x1][y1]->color) {
                        return 0;
                    }
                    return 1;
                }
                if (x1 < x2 && y1 > y2) {
                    for (int i = 1; i < x2 - x1; i++) {
                        if (((Piece**)table)[x1 + i][y1 - i] != NULL) {
                            return 0;
                        }
                    }
                    if (((Piece**)table)[x2][y2] != NULL && ((Piece**)table)[x2][y2]->color == ((Piece**)table)[x1][y1]->color) {
                        return 0;
                    }
                    return 1;
                }
                if (x1 > x2 && y1 < y2) {
                    for (int i = 1; i < x1 - x2; i++) {
                        if (((Piece**)table)[x1 - i][y1 + i] != NULL) {
                            return 0;
                        }
                    }
                    if (((Piece**)table)[x2][y2] != NULL && ((Piece**)table)[x2][y2]->color == ((Piece**)table)[x1][y1]->color) {
                        return 0;
                    }
                    return 1;
                }
                if (x1 > x2 && y1 > y2) {
                    for (int i = 1; i < x1 - x2; i++) {
                        if (((Piece**)table)[x1 - i][y1 - i] != NULL) {
                            return 0;
                        }
                    }
                    if (((Piece**)table)[x2][y2] != NULL && ((Piece**)table)[x2][y2]->color == ((Piece**)table)[x1][y1]->color) {
                        return 0;
                    }
                    return 1;
                }
            }
            return 0;
        }
    }
    if (strcmp(type, "QUEEN") == 0) {
        if (x1 == x2 && y1 == y2) {
            return 0;
        }
        if (x1 == x2 && y1 != y2) {
            if (y1 < y2) {
                for (int i = y1 + 1; i < y2; i++) {
                    if (((Piece**)table)[x1][i] != NULL) {
                        return 0;
                    }
                }
                if (((Piece**)table)[x2][y2] != NULL && ((Piece**)table)[x2][y2]->color == ((Piece**)table)[x1][y1]->color) {
                    return 0;
                }
                return 1;
            }
            if (y1 > y2) {
                for (int i = y1 - 1; i > y2; i--) {
                    if (((Piece**)table)[x1][i] != NULL) {
                        return 0;
                    }
                }
                if (((Piece**)table)[x2][y2] != NULL && ((Piece**)table)[x2][y2]->color == ((Piece**)table)[x1][y1]->color) {
                    return 0;
                }
                return 1;
            }
        }
        if (x1 != x2 && y1 == y2) {
            if (x1 < x2) {
                for (int i = x1 + 1; i < x2; i++) {
                    if (((Piece**)table)[i][y1] != NULL) {
                        return 0;
                    }
                }
                if (((Piece**)table)[x2][y2] != NULL && ((Piece**)table)[x2][y2]->color == ((Piece**)table)[x1][y1]->color) {
                    return 0;
                }
                return 1;
            }
            if (x1 > x2) {
                for (int i = x1 - 1; i > x2; i--) {
                    if (((Piece**)table)[i][y1] != NULL) {
                        return 0;
                    }
                }
                if (((Piece**)table)[x2][y2] != NULL && ((Piece**)table)[x2][y2]->color == ((Piece**)table)[x1][y1]->color) {
                    return 0;
                }
                return 1;
            }
        }
        if (x1 != x2 && y1 != y2) {
            if (abs(x2 - x1) == abs(y2 - y1)) {
                if (x1 < x2 && y1 < y2) {
                    for (int i = 1; i < x2 - x1; i++) {
                        if (((Piece**)table)[x1 + i][y1 + i] != NULL) {
                            return 0;
                        }
                    }
                    if (((Piece**)table)[x2][y2] != NULL && ((Piece**)table)[x2][y2]->color == ((Piece**)table)[x1][y1]->color) {
                        return 0;
                    }
                    return 1;
                }
                if (x1 < x2 && y1 > y2) {
                    for (int i = 1; i < x2 - x1; i++) {
                        if (((Piece**)table)[x1 + i][y1 - i] != NULL) {
                            return 0;
                        }
                    }
                    if (((Piece**)table)[x2][y2] != NULL && ((Piece**)table)[x2][y2]->color == ((Piece**)table)[x1][y1]->color) {
                        return 0;
                    }
                    return 1;
                }
                if (x1 > x2 && y1 < y2) {
                    for (int i = 1; i < x1 - x2; i++) {
                        if (((Piece**)table)[x1 - i][y1 + i] != NULL) {
                            return 0;
                        }
                    }
                    if (((Piece**)table)[x2][y2] != NULL && ((Piece**)table)[x2][y2]->color == ((Piece**)table)[x1][y1]->color) {
                        return 0;
                    }
                    return 1;
                }
                if (x1 > x2 && y1 > y2) {
                    for (int i = 1; i < x1 - x2; i++) {
                        if (((Piece**)table)[x1 - i][y1 - i] != NULL) {
                            return 0;
                        }
                    }
                    if (((Piece**)table)[x2][y2] != NULL && ((Piece**)table)[x2][y2]->color ==
                        ((Piece**)table)[x1][y1]->color) {
                        return 0;
                    }
                    return 1;
                }
            }
        }
        return 0;
    }
    if (strcmp(type, "KING") == 0) {
        if (x1 == x2 && y1 == y2) {
            return 0;
        }
        if (abs(x2 - x1) <= 1 && abs(y2 - y1) <= 1) {
            if (((Piece**)table)[x2][y2] != NULL && ((Piece**)table)[x2][y2]->color == ((Piece**)table)[x1][y1]->color) {
                return 0;
            }
            return 1;
        }
        return 0;
    }
    return 0;
}
    


// Implement a function to convert your chess matrix to FEN (Forsyth–Edwards Notation) format and returns the value into a string
// respecting that patter: rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1 where the lower case are the white peaces and the upper case are the black peaces

char* fen(Piece** table) {
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
// if the move is valid it returns the new table with the pieces moved
Piece** move_piece(Piece** table, int from_x, int from_y, int to_x, int to_y, FILE *in) {
    if (check_valid(table, in)) {
        table[to_x][to_y] = table[from_x][from_y];
        table[from_x][from_y] = NULL;
    }
    return table;
}

// check that king can't move anymore, check all the cases around the king and if there is a piece that can kill the king, return 1, else return 0
int is_king_in_checkmate(Piece** table, piece_color_t color, FILE *in) {
    int king_x = -1, king_y = -1;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (((Piece**)table)[x][y] != NULL && ((Piece**)table)[x][y]->type == KING && ((Piece**)table)[x][y]->color == color) {
                king_x = x;
                king_y = y;
                break;
            }
        }
    }
    // Verificăm dacă regele este deja în șah
    if (is_king_in_check(table, color)) {
        // Dacă regele este deja în șah, încercăm să găsim o mutare care să scoată regele din șah
        for (int from_x = 0; from_x < 8; from_x++) {
            for (int from_y = 0; from_y < 8; from_y++) {
                if (((Piece**)table)[from_x][from_y] == NULL) {
                    continue; // Nu există piesă pe poziția (from_x, from_y)
                }
                if (((Piece**)table)[from_x][from_y]->color == ((Piece**)table)[king_x][king_y]->color) {
                    // Dacă piesa de pe poziția (from_x, from_y) este de aceeași culoare ca regele, încercăm să găsim o mutare validă pentru acea piesă
                    for (int to_x = 0; to_x < 8; to_x++) {
                        for (int to_y = 0; to_y < 8; to_y++) {
                            if (check_valid(table, in)) {
                                // Dacă mutarea este validă, încercăm să o efectuăm și verificăm dacă regele mai este în șah
                                Piece** new_table = move_piece(table, from_x, from_y, to_x, to_y, in);
                                bool king_in_check = is_king_in_check(new_table, color);
                                free_matrix(new_table);
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
int is_king_in_check(Piece** table, piece_color_t color) {
    int king_x = -1, king_y = -1;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (((Piece**)table)[i][j] != NULL && ((Piece**)table)[i][j]->type == KING && ((Piece**)table)[i][j]->color == color) {
                king_x = i;
                king_y = j;
                break;
            }
        }
    }
    // Verificăm dacă regele este în șah de către o piesă de tip pion
    if (king_x > 0 && king_y > 0 && ((Piece**)table)[king_x - 1][king_y - 1] != NULL && ((Piece**)table)[king_x - 1][king_y - 1]->type == PAWN && !((Piece**)table)[king_x - 1][king_y - 1]->color) {
        return 1;
    }
    if (king_x > 0 && king_y < 8 - 1 && ((Piece**)table)[king_x - 1][king_y + 1] != NULL && ((Piece**)table)[king_x - 1][king_y + 1]->type == PAWN && !((Piece**)table)[king_x - 1][king_y + 1]->color) {
        return 1;
    }
    // Verificăm dacă regele este în șah de către o piesă de tip cal
    for (int i = -2; i <= 2; i++) {
        for (int j = -2; j <= 2; j++) {
            if (abs(i) + abs(j) == 3 && king_x + i >= 0 && king_x + i < 8 && king_y + j >= 0 && king_y + j < 8 && ((Piece**)table)[king_x + i][king_y + j] != NULL && ((Piece**)table)[king_x + i][king_y + j]->type == KNIGHT && ((Piece**)table)[king_x + i][king_y + j]->color != ((Piece**)table)[king_x][king_y]->color) {
                return 1;
            }
        }
    }
    // Verificăm dacă regele este în șah de către o piesă de tip nebun sau regină
    for (int i = -1; i <= 1; i += 2) {
        for (int j = -1; j <= 1; j += 2) {
            for (int k = 1; k < 8; k++) {
                if (king_x + i * k >= 0 && king_x + i * k < 8 && king_y + j * k >= 0 && king_y + j * k < 8 && ((Piece**)table)[king_x + i * k][king_y + j * k] != NULL) {
                    if (((Piece**)table)[king_x + i * k][king_y + j * k]->type == BISHOP && ((Piece**)table)[king_x + i * k][king_y + j * k]->color != ((Piece**)table)[king_x][king_y]->color) {
                        return 1;
                    }
                    if (((Piece**)table)[king_x + i * k][king_y + j * k]->type == QUEEN && ((Piece**)table)[king_x + i * k][king_y + j * k]->color != ((Piece**)table)[king_x][king_y]->color) {
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
            if (king_x + i * k >= 0 && king_x + i * k < 8 && ((Piece**)table)[king_x + i * k][king_y] != NULL) {
                if (((Piece**)table)[king_x + i * k][king_y]->type == ROOK && ((Piece**)table)[king_x + i * k][king_y]->color != ((Piece**)table)[king_x][king_y]->color) {
                    return 1;
                }
                if (((Piece**)table)[king_x + i * k][king_y]->type == QUEEN && ((Piece**)table)[king_x + i * k][king_y]->color != ((Piece**)table)[king_x][king_y]->color) {
                    return 1;
                }
                break;
            }
        }
        for (int k = 1; k < 8; k++) {
            if (king_y + i * k >= 0 && king_y + i * k < 8 && ((Piece**)table)[king_x][king_y + i * k] != NULL) {
                if (((Piece**)table)[king_x][king_y + i * k]->type == ROOK && ((Piece**)table)[king_x][king_y + i * k]->color != ((Piece**)table)[king_x][king_y]->color) {
                    return 1;
                }
                if (((Piece**)table)[king_x][king_y + i * k]->type == QUEEN && ((Piece**)table)[king_x][king_y + i * k]->color != ((Piece**)table)[king_x][king_y]->color) {
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
                if (king_x + i >= 0 && king_x + i < 8 && king_y + j >= 0 && king_y + j < 8 && ((Piece**)table)[king_x + i][king_y + j] != NULL && ((Piece**)table)[king_x + i][king_y + j]->type == KING && ((Piece**)table)[king_x + i][king_y + j]->color != ((Piece**)table)[king_x][king_y]->color) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

// function that check if the specified position is a check
int not_good_position(Piece** table, int x, int y) {
    // Verificăm dacă regele este în șah de către o piesă de tip pion
    for (int i = -1; i <= 1; i += 2) {
        if (x + 1 < 8 && y + i >= 0 && y + i < 8 && ((Piece**)table)[x + 1][y + i] != NULL && ((Piece**)table)[x + 1][y + i]->type == PAWN && ((Piece**)table)[x + 1][y + i]->color != ((Piece**)table)[x][y]->color) {
            return 1;
        }
    }
    // Verificăm dacă regele este în șah de către o piesă de tip cal
    for (int i = -1; i <= 1; i += 2) {
        for (int j = -1; j <= 1; j += 2) {
            if (x + i * 2 >= 0 && x + i * 2 < 8 && y + j >= 0 && y + j < 8 && ((Piece**)table)[x + i * 2][y + j] != NULL && ((Piece**)table)[x + i * 2][y + j]->type == KNIGHT && ((Piece**)table)[x + i * 2][y + j]->color != ((Piece**)table)[x][y]->color) {
                return 1;
            }
            if (x + i >= 0 && x + i < 8 && y + j * 2 >= 0 && y + j * 2 < 8 && ((Piece**)table)[x + i][y + j * 2] != NULL && ((Piece**)table)[x + i][y + j * 2]->type == KNIGHT && ((Piece**)table)[x + i][y + j * 2]->color != ((Piece**)table)[x][y]->color) {
                return 1;
            }
        }
    }
    // Verificăm dacă regele este în șah de către o piesă de tip nebun sau regină
    for (int i = -1; i <= 1; i += 2) {
        for (int j = -1; j <= 1; j += 2) {
            for (int k = 1; k < 8; k++) {
                if (x + i * k >= 0 && x + i * k < 8 && y + j * k >= 0 && y + j * k < 8 && ((Piece**)table)[x + i * k][y + j * k] != NULL) {
                    if (((Piece**)table)[x + i * k][y + j * k]->type == BISHOP && ((Piece**)table)[x + i * k][y + j * k]->color != ((Piece**)table)[x][y]->color) {
                        return 1;
                    }
                    if (((Piece**)table)[x + i * k][y + j * k]->type == QUEEN && ((Piece**)table)[x + i * k][y + j * k]->color != ((Piece**)table)[x][y]->color) {
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
            if (x + i * k >= 0 && x + i * k < 8 && ((Piece**)table)[x + i * k][y] != NULL) {
                if (((Piece**)table)[x + i * k][y]->type == ROOK && ((Piece**)table)[x + i * k][y]->color != ((Piece**)table)[x][y]->color) {
                    return 1;
                }
                if (((Piece**)table)[x + i * k][y]->type == QUEEN && ((Piece**)table)[x + i * k][y]->color != ((Piece**)table)[x][y]->color) {
                    return 1;
                }
                break;
            }
        }
        for (int k = 1; k < 8; k++) {
            if (y + i * k >= 0 && y + i * k < 8 && ((Piece**)table)[x][y + i * k] != NULL) {
                if (((Piece**)table)[x][y + i * k]->type == ROOK && ((Piece**)table)[x][y + i * k]->color != ((Piece**)table)[x][y]->color) {
                    return 1;
                }
                if (((Piece**)table)[x][y + i * k]->type == QUEEN && ((Piece**)table)[x][y + i * k]->color != ((Piece**)table)[x][y]->color) {
                    return 1;
                }
                break;
            }
        }
    }
    // Verificăm dacă regele este în șah de către o piesă de tip regină
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (x + i >= 0 && x + i < 8 && y + j >= 0 && y + j < 8 && ((Piece**)table)[x + i][y + j] != NULL && ((Piece**)table)[x + i][y + j]->type == KING && ((Piece**)table)[x + i][y + j]->color != ((Piece**)table)[x][y]->color) {
                return 1;
            }
        }
    }
    // Dacă regele nu este în șah, returnăm 0
    return 0;
}
// function that castel the king if the way is open and the king is not in check

Piece** castle(Piece** table, int x1, int y1, int x2, int y2) {
    // Verificăm dacă regele este în șah
    if (is_king_in_check(table, ((Piece**)table)[x1][y1]->color)) {
        return table;
    }
    // Verificăm dacă regele se mută pe aceeași linie sau coloană
    if (x1 != x2 && y1 != y2) {
        return table;
    }
    // Verificăm dacă regele se mută pe o linie
    if (x1 == x2) {
        // Verificăm dacă regele se mută spre stânga
        if (y1 > y2) {
            // Verificăm dacă între rege și tura nu se află nicio piesă
            for (int i = y2 + 1; i < y1; i++) {
                if (((Piece**)table)[x1][i] != NULL) {
                    return table;
                }
            }
            // Verificăm dacă regele este în șah dacă se mută pe poziția de la care se va face roșadă
            if (not_good_position(table, x1, y2)) {
                return table;
            }
            // Verificăm dacă regele este în șah dacă se mută pe poziția de la care se va face roșadă
            if (not_good_position(table, x1, y2 + 1)) {
                return table;
            }
            // Verificăm dacă tura se află pe poziția inițială
            if (((Piece**)table)[x1][0] != NULL && ((Piece**)table)[x1][0]->type == ROOK && ((Piece**)table)[x1][0]->color == ((Piece**)table)[x1][y1]->color && ((Piece**)table)[x1][0]->hasMoved == 0) {
                // Mutăm regele
                ((Piece**)table)[x1][y2] = ((Piece**)table)[x1][y1];
                ((Piece**)table)[x1][y1] = NULL;
                // Mutăm tura
                ((Piece**)table)[x1][y2 + 1] = ((Piece**)table)[x1][y1 - 4];
                ((Piece**)table)[x1][y1 - 4] = NULL;
                // Marcam că regele și tura au fost mutate
                ((Piece**)table)[x1][y2]->hasMoved = 1;
                ((Piece**)table)[x1][y2 + 1]->hasMoved = 1;
                return table;
            }
        }
        // Verificăm dacă regele se mută spre dreapta
        else {
            // Verificăm dacă între rege și tura nu se află nicio piesă
            for (int i = y1 + 1; i < y2; i++) {
                if (((Piece**)table)[x1][i] != NULL) {
                    return table;
                }
            }
            // Verificăm dacă regele este în șah dacă se mută pe poziția de la care se va face roșadă
            if (not_good_position(table, x1, y2)) {
                return table;
            }
            // Verificăm dacă tura se află pe poziția inițială
            if (((Piece**)table)[x1][7] != NULL && ((Piece**)table)[x1][7]->type == ROOK && ((Piece**)table)[x1][7]->color == ((Piece**)table)[x1][y1]->color && ((Piece**)table)[x1][7]->hasMoved == 0) {
                // Mutăm regele
                ((Piece**)table)[x1][y2] = ((Piece**)table)[x1][y1];
                ((Piece**)table)[x1][y1] = NULL;
                // Mutăm tura
                ((Piece**)table)[x1][y2 - 1] = ((Piece**)table)[x1][y1 + 3];
                ((Piece**)table)[x1][y1 + 3] = NULL;
                // Marcam că regele și tura au fost mutate
                ((Piece**)table)[x1][y2]->hasMoved = 1;
                ((Piece**)table)[x1][y2 - 1]->hasMoved = 1;
                return table;
            }
        }
    }
    // Verificăm dacă regele se mută pe o coloană
    else {
        // Verificăm dacă regele se mută spre sus
        if (x1 > x2) {
            // Verificăm dacă între rege și tura nu se află nicio piesă
            for (int i = x2 + 1; i < x1; i++) {
                if (((Piece**)table)[i][y1] != NULL) {
                    return table;
                }
            }
            // Verificăm dacă regele este în șah dacă se mută pe poziția de la care se va face roșadă
            if (not_good_position(table, x2, y1)) {
                return table;
            }
            // Verificăm dacă regele este în șah dacă se mută pe poziția de la care se va face roșadă
            if (not_good_position(table, x2 + 1, y1)) {
                return table;
            }
            // Verificăm dacă tura se află pe poziția inițială
            if (((Piece**)table)[0][y1] != NULL && ((Piece**)table)[0][y1]->type == ROOK && ((Piece**)table)[0][y1]->color == ((Piece**)table)[x1][y1]->color && ((Piece**)table)[0][y1]->hasMoved == 0) {
                // Mutăm regele
                ((Piece**)table)[x2][y1] = ((Piece**)table)[x1][y1];
                ((Piece**)table)[x1][y1] = NULL;
                // Mutăm tura
                ((Piece**)table)[x2 + 1][y1] = ((Piece**)table)[x1 - 4][y1];
                ((Piece**)table)[x1 - 4][y1] = NULL;
                // Marcam că regele și tura au fost mutate
                ((Piece**)table)[x2][y1]->hasMoved = 1;
                ((Piece**)table)[x2 + 1][y1]->hasMoved = 1;
                return table;
            }
        }
        // Verificăm daca  regele se mută spre jos
        else {
            // Verificăm dacă între rege și tura nu se află nicio piesă
            for (int i = x1 + 1; i < x2; i++) {
                if (((Piece**)table)[i][y1] != NULL) {
                    return table;
                }
            }
            // Verificăm dacă regele este în șah dacă se mută pe poziția de la care se va face roșadă
            if (not_good_position(table, x2, y1)) {
                return table;
            }
            // Verificăm dacă tura se află pe poziția inițială
            if (((Piece**)table)[7][y1] != NULL && ((Piece**)table)[7][y1]->type == ROOK && ((Piece**)table)[7][y1]->color == ((Piece**)table)[x1][y1]->color && ((Piece**)table)[7][y1]->hasMoved == 0) {
                // Mutăm regele
                ((Piece**)table)[x2][y1] = ((Piece**)table)[x1][y1];
                ((Piece**)table)[x1][y1] = NULL;
                // Mutăm tura
                ((Piece**)table)[x2 - 1][y1] = ((Piece**)table)[x1 + 3][y1];
                ((Piece**)table)[x1 + 3][y1] = NULL;
                // Marcam că regele și tura au fost mutate
                ((Piece**)table)[x2][y1]->hasMoved = 1;
                ((Piece**)table)[x2 - 1][y1]->hasMoved = 1;
                return table;
            }
        }
    }
    return table;
}

// function that checks if the king can castle either to the left or to the right based on the fact that the king is in check or the king way to the is blocked by other pieces
int can_castle(Piece **table, int x, int y) {
    // check if the king is in check
    if (not_good_position(table, x, y)) {
        return 0;
    }
    // check if the king is in check if he moves to the left
    if (not_good_position(table, x, y - 2)) {
        return 0;
    }
    // check if the king is in check if he moves to the right
    if (not_good_position(table, x, y + 2)) {
        return 0;
    }
    // check if the king way to the left is blocked by other pieces
    for (int i = y - 1; i > y - 3; i--) {
        if (((Piece**)table)[x][i] != NULL) {
            return 0;
        }
    }
    // check if the king way to the right is blocked by other pieces
    for (int i = y + 1; i < y + 3; i++) {
        if (((Piece**)table)[x][i] != NULL) {
            return 0;
        }
    }
    // check if the king has moved
    if (((Piece**)table)[x][y]->hasMoved == 1) {
        return 0;
    }
    // check if the rook on the left has moved
    if (((Piece**)table)[x][0] != NULL && ((Piece**)table)[x][0]->type == ROOK && ((Piece**)table)[x][0]->hasMoved == 1) {
        return 0;
    }
    // check if the rook on the right has moved
    if (((Piece**)table)[x][7] != NULL && ((Piece**)table)[x][7]->type == ROOK && ((Piece**)table)[x][7]->hasMoved == 1) {
        return 0;
    }
    return 1;
}

// we know that the king can castles, so we do a function that does the castling 
Piece **castling(Piece **table, int x, int y) {
    // check if the king can castles to the left
    if (can_castle(table, x, y) && y == 4 && x == 0) {
        // move the king to the left
        table[x][y - 2] = ((Piece**)table)[x][y];
        table[x][y] = NULL;
        // move the rook to the left
        table[x][y - 1] = ((Piece**)table)[x][y - 4];
        table[x][y - 4] = NULL;
        // mark that the king and the rook have moved
        table[x][y - 2]->hasMoved = 1;
        table[x][y - 1]->hasMoved = 1;
        return table;
    }
    // check if the king can castles to the right
    if (can_castle(table, x, y) && y == 4 && x == 7) {
        // move the king to the right
        ((Piece**)table)[x][y + 2] = ((Piece**)table)[x][y];
        ((Piece**)table)[x][y] = NULL;
        // move the rook to the right
        ((Piece**)table)[x][y + 1] = ((Piece**)table)[x][y + 3];
        ((Piece**)table)[x][y + 3] = NULL;
        // mark that the king and the rook have moved
        ((Piece**)table)[x][y + 2]->hasMoved = 1;
        ((Piece**)table)[x][y + 1]->hasMoved = 1;
        return table;
    }
    return table;
}
