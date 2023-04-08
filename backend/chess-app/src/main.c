#include "table.h"

int main() {
    Piece** table = init_matrix();
    print_matrix(table);
    // free_matrix(table);
    return 0;
}