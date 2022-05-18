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
        printf("\tItem %d (Idx %d): %s\n", idx + 1, idx, (char*) cursor->value);
        cursor = cursor->next;
        idx++;
    } while (cursor);
}

void print_list_size(list_node* root) {
    printf("The list now has %d elements.\n", ll_size(root));
}

void print(list_node* root) {
    print_list_size(root);
    print_list(root);
}

int main(void) {
    list_node* root = malloc(sizeof(list_node));
    root->value = "Hello";
    print(root);

    ll_push(root, "World!");
    print(root);

    ll_push(root, "My");
    print(root);
    ll_push(root, "name");
    print(root);
    ll_push(root, "is");
    print(root);
    ll_push(root, "Jacob");
    print(root);

    printf("Now replace name...Popping!\n");
    char* popped = ll_pop(root);
    printf("Popped value: %s\n", popped);
    print(root);
    ll_push(root, "Haxor");
    print(root);

    printf("Clearing LinkedList...");
    ll_clear(root);
    print(root);
}