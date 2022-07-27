#include "linked_list.h"
#include <stdio.h>

static list_node* make_node() {
    // allocate enough space for a list_node
    return calloc(1, sizeof(list_node));
}

static bool is_valid_root(list_node* root) {
    // a root is valid if it is not a null pointer
    // and it has no previous node
    return root && !root->prev && root->value;
}

bool ll_unshift(list_node** root, void* value) {
    if (!is_valid_root(*root)) return false;

    // create new node and set its next
    // node as the previous root
    list_node* new_root = make_node();
    if (!new_root) {
        // a new node could not be allocated
        return false;
    }

    new_root->value = value;
    new_root->next = *root;

    // set the previous root's previous node
    // as the new root
    (*root)->prev = new_root;
    return true;
}

bool ll_insert(list_node* root, int index, void* value) {
    if (index == 0) {
        return ll_unshift(&root, value);
    }

    if (!is_valid_root(root)) return false;

    // seek the list until arriving one index
    // prior to the target of insertion
    list_node* cursor = root;
    for (int i = 0; i < index - 1; i++) {
        cursor = cursor->next;
        if (!cursor->next) {
            return false;
        }
    }

    // create and set values of the new node
    list_node* new_element = make_node();
    if (!new_element) {
        return false;
    }

    new_element->value = value;

    // store addresses of the preceeding and following nodes
    list_node** before = &cursor;
    list_node** after = &(cursor->next);

    // move pointers around to fix list ordering
    (*before)->next = new_element;
    new_element->prev = *before;
    new_element->next = *after;
    (*after)->prev = new_element;

    return true;
}

bool ll_push(list_node* root, void* value) {
    if (!is_valid_root(root)) return false;

    // seek the list until encountering a node
    // without a valid next value (i.e., the end
    // of the list)
    list_node* cursor = root;
    while (cursor->next) {
        cursor = cursor->next;
    }

    // create the new node and set its value
    list_node* new_element = make_node();
    if (!new_element) {
        return false;
    }

    cursor->next = new_element;
    new_element->value = value;
    new_element->prev = cursor;

    return true;
}

void* ll_shift(list_node** root) {
    if (!is_valid_root(*root)) return false;

    // save the current root and value, and free its memory
    list_node* old_root = *root;
    void* value = old_root->value;
    free(old_root);

    // update the root to the following item
    *root = (*root)->next;
    (*root)->prev = NULL;

    // return the value that was held in the old root
    return old_root->value;
}

void* ll_remove(list_node* root, int index) {
    if (index == 0) {
        return ll_shift(&root);
    }

    if (!is_valid_root(root)) return false;

    list_node* cursor = root;
    for (int i = 0; i < index - 1; i++) {
        cursor = cursor->next;
        if (!cursor->next) {
            return NULL;
        }
    }

    list_node* to_remove = cursor->next;
    void* value = to_remove->value;

    if (to_remove->next) {
        list_node* following = to_remove->next;
        cursor->next = following;
        following->prev = cursor;
    } else {
        cursor->next = NULL;
    }

    free(to_remove);

    return value;
}

void* ll_pop(list_node* root) {
    if (!is_valid_root(root)) return false;

    // seek the list until at the index
    // preceeding the final element
    list_node* cursor = root;
    while (cursor->next->next) {
        cursor = cursor->next;
    }

    // save the last node
    list_node* end = cursor->next;
    void* value = end->value;

    // free the memory and set the next element
    // to null
    free(cursor->next);
    cursor->next = NULL;

    // return the value stored there
    return value;
}

int ll_size(list_node* root) {
    int count = 0;

    if (!is_valid_root(root)) return count;

    count++; // Since it is a valid root, there is at one element (the root).

    list_node* cursor = root;
    while (cursor->next) {
        cursor = cursor->next;
        count++;
    }

    return count;
}

bool ll_clear(list_node* root) {
    if (!is_valid_root(root)) return false;

    list_node* cursor = root;
    while (true) {
        list_node* next = cursor->next;

        cursor->next = NULL;
        if (cursor->prev) {
            cursor->prev = NULL;
        }

        if (cursor->value) {
            free(cursor->value);
        }

        free(cursor);

        cursor = next;
        if (!cursor) {
            break;
        }
    }

    return true;
}
