#include "table.h"
#include <stdio.h>
#include <stdbool.h>

int main() {
    void** table = init_matrix();
    print_matrix(table);
    printf("\n%d\n", check_valid((Piece**)table, 0, 1, 2, 0));
    return 0;
}