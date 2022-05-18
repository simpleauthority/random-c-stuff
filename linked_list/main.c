#include "linked_list.h"
#include <stdio.h>

void print_list(list_node* root) {
    printf("=== Printing List ===\n");
    if (!root) {
        printf("\tThere are no elements.\n");
        return;
    }

    int idx = 0;
    list_node* cursor = root;
    do {
        printf("\tItem %d (Idx %d): %s\n", idx + 1, idx, (char*) root->value);
        cursor = cursor->next;
        idx++;
    } while (cursor);
}

void print_list_size(list_node* root) {
    printf("The list now has %d elements.\n", ll_size(root));
}

void print(list_node* root) {
    print_list(root);
    print_list_size(root);
}

int main(void) {
    list_node* root = malloc(sizeof(list_node));
    root->value = "Hello";
    print(root);

    bool result = ll_push(root, "World!");
    printf("Push: %s\n", result ? "Success" : "Failed");
    print(root);

    ll_clear(root);
}