#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

/**
 * @brief a node of the linked list which tracks the
 * node that comes both before and after it
 */
typedef struct list_node {
    void* value;
    struct list_node* prev;
    struct list_node* next;
} list_node;

/**
 * @brief add an item to the front of the linked list
 * 
 * @param root the root of the linked list
 * @param item the item to add to the linked list
 * @return bool whether the unshift operation succeeded
 */
bool ll_unshift(list_node** root, void* item);

/**
 * @brief add an item to the linked list at a specific index
 * 
 * @param root the root of the linked list
 * @param index the index at which to insert the item
 * @param item the item to add to the linked list
 * @return bool whether the insert operation succeeded
 */
bool ll_insert(list_node* root, int index, void* item);

/**
 * @brief add an item to the end of the linked list
 * 
 * @param root the root of the linked list
 * @param item the item to add to the linked list
 * @return bool whether the push operation succeeded
 */
bool ll_push(list_node* root, void* item);

/**
 * @brief remove an item from the front of the linked list;
 * caller must free the data when finished
 * 
 * @param root the root of the linked list
 * @return void* the item removed from the linked list
 */
void* ll_shift(list_node** root);


/**
 * @brief remove an item from the list at a specific index;
 * caller must free the data when finished
 * 
 * @param root the root of the linked list
 * @return void* the item removed from the linked list or NULL
 * if the index was not reachable
 */
void* ll_remove(list_node* root, int index);

/**
 * @brief remove an item from the end of the linked list;
 * caller must free the data when finished
 * 
 * @param root the root of the linked list
 * @return void* the item removed from the linked list
 */
void* ll_pop(list_node* root);


/**
 * @brief get the size of the linked list
 * 
 * @param root the root of the linked list
 * @return int integer representing the count of items in the linked list
 */
int ll_size(list_node* root);

/**
 * @brief clears the linked list and frees all associated data
 * 
 * @param root the root of the linked list
 * @return bool whether the clear operation succeeded
 */
bool ll_clear(list_node* root);
#endif