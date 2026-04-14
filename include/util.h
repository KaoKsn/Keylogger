#ifndef UTIL_H
#define UTIL_H

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lkup_table {
    struct lkup_table_node **lkup_table_nodes;
    uint32_t c_entries;
    uint32_t t_entries;
};

struct lkup_table_node {
    uint16_t code;
    char _ascii_char;
};

void free_lkup_table(struct lkup_table *lk_table);
int find(struct lkup_table_node **lkup_table_nodes, int t_entries, uint16_t code, bool caps);
int init_lookup_table(struct lkup_table *lk_table);
int insert(struct lkup_table *lk_table, uint16_t code, char _ascii_char);
void print_lk_table(struct lkup_table *lk_table);

#endif
