#include "linked_list.h"
#include <stdio.h>

void print_list(list_node* root) {
    printf("=== Printing List ===\n");
    if (ll_size(root) == 0) {
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
    list_node* root = calloc(1, sizeof(list_node));
    root->value = "Hello";
    print(root);

    ll_push(root, "World!");
    ll_push(root, "My");
    ll_push(root, "name");
    ll_push(root, "is");
    ll_push(root, "Jacob");
    print(root);

    printf("Now replace name...Popping!\n");
    char* popped = ll_pop(root);
    printf("Popped value: %s\n", popped);
    printf("Pushing value...\n");
    ll_push(root, "Haxor");
    print(root);

    printf("Clearing LinkedList...\n");
    ll_clear(root);
    root = NULL;
    
    printf("LinkedList is cleared. Now trying to print...\n");
    print(root);
}
