#include <stdio.h>
#include <assert.h>

#include "../include/util.h"

int main(void)
{
    struct lkup_table lk_table;
    init_lookup_table(&lk_table);

    int passed = 0, n = 2;

    // Check if c_entries and t_entries are the same.
    assert(lk_table.t_entries == lk_table.c_entries);
    printf("Passed [%d/%d]: t_entries equals c_entries.\n", ++passed, n);

    // Check if the contents are sorted.
    for (unsigned int i = 0; i < lk_table.c_entries - 1; i++) {
        assert (lk_table.lkup_table_nodes[i]->code < lk_table.lkup_table_nodes[i+1]->code);
    }
    printf("Passed [%d/%d]: Lookup table is sorted in the ascending order of code.\n", ++passed, n);

    free_lkup_table(&lk_table);
}


