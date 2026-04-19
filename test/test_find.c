#include <assert.h>
#include "../include/util.h"

int main(void) {
    struct lkup_table lk_table;
    memset(&lk_table, 0, sizeof(lk_table));

    init_lookup_table(&lk_table);

    int ch, n = 5, passed = 0;
    ch = find(lk_table.lkup_table_nodes, lk_table.c_entries, 32, false);
    assert(ch == 'd');
    printf("Passed [%d/%d]: test lower-case alphabet\n", ++passed, n);

    ch = find(lk_table.lkup_table_nodes, lk_table.c_entries, 16, true);
    assert(ch == 'Q');
    printf("Passed [%d/%d]: test upper-case alphabet\n", ++passed, n);

    // esc key.
    ch = find(lk_table.lkup_table_nodes, lk_table.c_entries, 1, true);
    assert(ch == -1);
    printf("Passed [%d/%d]: test entries that don't exist.\n", ++passed, n);

    ch = find(lk_table.lkup_table_nodes, lk_table.c_entries, 43, true);
    assert(ch == '\\');
    printf("Passed [%d/%d]: test special characters with caps on.\n", ++passed, n);

    ch = find(lk_table.lkup_table_nodes, lk_table.c_entries, 41, false);
    assert(ch == '`');
    printf("Passed [%d/%d]: test special characters with caps off.\n", ++passed, n);

    free_lkup_table(&lk_table);
    return 0;
}
