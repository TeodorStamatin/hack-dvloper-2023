#include "table.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>


FILE *popen(const char *command, const char *type);
int pclose(FILE *stream);

int main() {
    void** table = init_matrix();
    // starts stockfish
    FILE *fp = popen("../basa/Stockfish/src/stockfish", "w");
    // sends fen to stockfish
    while(!is_king_in_checkmate(table, WHITE) && !is_king_in_checkmate(table, BLACK)) {
        // printf("Your move: ");
        // char move[6];
        // scanf("%s", move);
        char* str = fen(table);
        fprintf(fp, "position fen %s\n", str);
        // asks stockfish to calculate best move
        fprintf(fp, "go depth 1\n");

        // reads best move from stockfish
        char response[1024];
        fgets(response, 1024, fp);
        // Parse best move from response
        // citeste tokenul din fisierul bestmove.txt
        FILE* best = fopen("bestmove.txt", "r");
        char best_move[6];
        fscanf(best, "%s", best_move);
        fclose(best);
        int from_x = (best_move[0] - 'a');
        int from_y = 7 - (best_move[1] - '1');
        int to_x =  (best_move[2] - 'a');
        int to_y = 7 - (best_move[3] - '1');
        // while(!check_valid(table, from_y, from_x, to_y, to_x)) {
        //     printf("Invalid move, try again: ");
        //     scanf("%s", move);
        //     from_x = (move[0] - 'a');
        //     from_y = 7 - (move[1] - '1');
        //     to_x =  (move[2] - 'a');
        //     to_y = 7 - (move[3] - '1');
        // }
        table = move_piece(table, from_y, from_x, to_y, to_x);
        str = fen(table);
        fprintf(fp, "position fen %s\n", str);
        // asks stockfish to calculate best move
        fprintf(fp, "go depth 1\n");

        // reads best move from stockfish
        fgets(response, 1024, fp);
        // Parse best move from response
        // citeste tokenul din fisierul bestmove.txt
        best = fopen("bestmove.txt", "r");
        fscanf(best, "%s", best_move);
        fclose(best);
        // Parse best move
        from_x = (best_move[0] - 'a');
        from_y = (best_move[1] - '1');
        to_x =  (best_move[2] - 'a');
        to_y = (best_move[3] - '1');
        // Move piece
        table = move_piece(table, from_y, from_x, to_y, to_x);
        print_matrix(table);
    }

    pclose(fp);
    free_matrix(table);
    return 0;
}