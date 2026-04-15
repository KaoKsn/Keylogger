#include "../include/util.h"

int sortfun(const void *a, const void *b)
{
    struct lkup_table_node *f = *(struct lkup_table_node **)a;
    struct lkup_table_node *s = *(struct lkup_table_node **)b;
    if (f->code > s->code)
        return 1;
    else if (f->code < s->code)
        return -1;
    else
        return 0;
}
int init_lookup_table(struct lkup_table *lk_table)
{
    if (lk_table == NULL)
        return 1;
    lk_table->c_entries = 0;
    lk_table->t_entries = 8;
    lk_table->lkup_table_nodes = calloc(lk_table->t_entries, sizeof(struct lkup_table_node *));

    if (lk_table->lkup_table_nodes == NULL) {
        fprintf(stderr, "Lookup table init failed!\n");
        return 1;
    }
    // Populate alphabets in the lookup table.
    FILE *keyfile = fopen("keys/keyfile.txt", "r");
    if (keyfile == NULL) {
        perror("open");
        free(lk_table->lkup_table_nodes);
        // Avoid dangling points. (free can be called anytime on the list).
        lk_table->lkup_table_nodes = NULL;
        return 1;
    }
    char key[8] = {'\0'};
    uint16_t code;
    while (fscanf(keyfile, "%s %hu", key, &code) != EOF) {
        insert(lk_table, code, key[strlen(key) - 1]);
        memset(key, 0, sizeof(key));
    }

    // Sort the lookup table for binary search.
    qsort(lk_table->lkup_table_nodes, lk_table->c_entries, sizeof(lk_table->lkup_table_nodes[0]), sortfun);
    fclose(keyfile);
    return 0;
}

// Insert a key into the lookup table.
int insert(struct lkup_table *lk_table, uint16_t code, char _ascii_char)
{
    if (lk_table == NULL) {
        fprintf(stderr, "Lookup table unitialized! Aborting immediately!\n");
        exit(EXIT_FAILURE);
    }
    struct lkup_table_node *lk_table_node = calloc(1, sizeof(struct lkup_table_node));
    if (lk_table_node == NULL)
        return EXIT_FAILURE;
    lk_table_node->code = code;
    lk_table_node->_ascii_char = _ascii_char;

    // Double the lookup table size.
    if (lk_table->c_entries == lk_table->t_entries) {
        struct lkup_table_node **tmp = realloc(lk_table->lkup_table_nodes, lk_table->t_entries * 2 * sizeof(struct lkup_table_node *));
        if (tmp == NULL) {
            free(lk_table_node);
            // Don't free the lookup table, its alright to have a partial table.
            return EXIT_FAILURE;
        }
        lk_table->t_entries *= 2;
        lk_table->lkup_table_nodes = tmp;
        // Avoid conditional jump on unitialized values!!
        for (uint32_t i = lk_table->c_entries; i < lk_table->t_entries; i++)
            lk_table->lkup_table_nodes[i] = NULL;
    }
    lk_table->lkup_table_nodes[lk_table->c_entries++] = lk_table_node;
    return EXIT_SUCCESS;
}

// Find a character in the lookup table.
int find(struct lkup_table_node **lkup_table_nodes, int t_entries, uint16_t code, bool caps)
{
    if (t_entries == 0 || lkup_table_nodes == NULL || *lkup_table_nodes == NULL)
        return -1;
    int b = 0, e = t_entries - 1;
    while (b <= e) {
        int mid = (b + e) / 2;
        if (lkup_table_nodes[mid]->code == code) {
            if (caps)
                return lkup_table_nodes[mid]->_ascii_char;
            else
                return tolower(lkup_table_nodes[mid]->_ascii_char);
        }
        else if (lkup_table_nodes[mid]->code < code)
            b = mid + 1;
        else
            e = mid - 1;
    }
    return -1;
}

// Free the lookup table.
void free_lkup_table(struct lkup_table *lk_table)
{
    if (lk_table) {
        if (lk_table->lkup_table_nodes) {
            for (uint32_t i = 0; i < lk_table->t_entries; i++) {
                if (lk_table->lkup_table_nodes[i])
                    free(lk_table->lkup_table_nodes[i]);
            }
        }
        free(lk_table->lkup_table_nodes);
    }
}

// Print the popluated lookup table.
void print_lk_table(struct lkup_table *lk_table)
{
    if (lk_table) {
        for (uint32_t i = 0; i < lk_table->c_entries; i++) {
            struct lkup_table_node *node = lk_table->lkup_table_nodes[i];
            printf("char: %c, code: %d\n", node->_ascii_char, node->code);
        }
    }
}
