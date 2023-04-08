#include "table.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>


FILE *popen(const char *command, const char *type);
int pclose(FILE *stream);

int main() {
    Piece** table;
    table = init_matrix();
    // starts stockfish
    FILE *fp = popen("../basa/Stockfish/src/stockfish", "w");
    FILE *out = fopen("matrix.txt", "w");
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
            printf(" ");
        }
        printf("\n");
    }
    // sends fen to stockfish
    // while(!is_king_in_checkmate(table, WHITE) && !is_king_in_checkmate(table, BLACK)) {
    //     // char* str = fen(table);
    //     // fprintf(fp, "position fen %s\n", str);
    //     // // asks stockfish to calculate best move
    //     // fprintf(fp, "go depth 1\n");

    //     // // reads best move from stockfish
    //     // char response[1024];
    //     // fgets(response, 1024, fp);
    //     // // Parse best move from response
    //     // // citeste tokenul din fisierul bestmove.txt
    //     // FILE* best = fopen("bestmove.txt", "r");
    //     // char best_move[6];
    //     // fscanf(best, "%s", best_move);
    //     // fclose(best);
    //     // int from_x = (best_move[0] - 'a');
    //     // int from_y = 7 - (best_move[1] - '1');
    //     // int to_x =  (best_move[2] - 'a');
    //     // int to_y = 7 - (best_move[3] - '1');
    //     // table = move_piece(table, from_y, from_x, to_y, to_x);
    //     // // print_matrix(table);

    //     // // printf("Your move: ");
    //     // // char move[6];
    //     // // scanf("%s", move);
    //     // // while(!check_valid(table, from_y, from_x, to_y, to_x)) {
    //     // //     printf("Invalid move, try again: ");
    //     // //     scanf("%s", best_move);
    //     // //     from_x = (best_move[0] - 'a');
    //     // //     from_y = (best_move[1] - '1');
    //     // //     to_x =  (best_move[2] - 'a');
    //     // //     to_y = (best_move[3] - '1');
    //     // // }
    //     // // table = move_piece(table, from_y, from_x, to_y, to_x);
    //     // str = fen(table);
    //     // fprintf(fp, "position fen %s\n", str);
    //     // // asks stockfish to calculate best move
    //     // fprintf(fp, "go depth 1\n");

    //     // // reads best move from stockfish
    //     // fgets(response, 1024, fp);
    //     // // Parse best move from response
    //     // // citeste tokenul din fisierul bestmove.txt
    //     // best = fopen("bestmove.txt", "r");
    //     // fscanf(best, "%s", best_move);
    //     // fclose(best);
    //     // // Parse best move
    //     // from_x = (best_move[0] - 'a');
    //     // from_y = (best_move[1] - '1');
    //     // to_x =  (best_move[2] - 'a');
    //     // to_y = (best_move[3] - '1');
    //     // // Move piece
    //     // table = move_piece(table, from_y, from_x, to_y, to_x);
    //     print_matrix(table, out);
    // }
    print_matrix(table, out);
    fclose(out);
    pclose(fp);
    free_matrix(table);
    return 0;
}