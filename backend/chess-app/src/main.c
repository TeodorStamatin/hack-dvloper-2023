#include "table.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

FILE *popen(const char *command, const char *type);
int pclose(FILE *stream);

int main() {
    void** table = init_matrix();
    print_matrix(table);
    char* str = fen(table);
    printf("COAIE EL E:%s\n", str);
    // starts stockfish
    FILE *fp = popen("../basa/Stockfish/src/stockfish", "w");
    // sends fen to stockfish
    fprintf(fp, "position fen %s", str);
    // asks stockfish to calculate best move
    fprintf(fp, "go\n");
    // reads best move from stockfish
    char buffer[512];
    fgets(buffer, 512, fp);
    printf("COAIE EL E:%s\n", buffer);
    // closes stockfish
    pclose(fp);
    // // parses best move
    // char* token = strtok(buffer, " ");
    // while (token != NULL) {
    //     if (strcmp(token, "bestmove") == 0) {
    //         token = strtok(NULL, " ");
    //         break;
    //     }
    //     token = strtok(NULL, " ");
    // }
    // // moves piece
    // int from_x = token[0] - 'a';
    // int from_y = token[1] - '1';
    // int to_x = token[2] - 'a';
    // int to_y = token[3] - '1';
    // move_piece(table, from_x, from_y, to_x, to_y);
    // // prints new table
    // print_matrix(table);
    // frees table
    free_matrix(table);
    return 0;
}