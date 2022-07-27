#include "linked_list.h"
#include <stdio.h>
#include <string.h>

static void print_list(list_node* root) {
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

static void print_list_size(list_node* root) {
    printf("The list now has %d elements.\n", ll_size(root));
}

static void print(list_node* root) {
    print_list_size(root);
    print_list(root);
}

static char* slurp(char* data) {
    data = malloc(sizeof(char));
    data[0] = '\0';

    int c;
    int i = 0;
    while (true) {
        c = getchar();

        if (c == '\n' || c == EOF) {
            break;
        }

        data = realloc(data, (i + 2) * sizeof(char));
        data[i] = (char) c;
        data[i + 1] = '\0';

        i++;
    }

    return data;
}

static list_node* handle_command(list_node* root, char* line) {
    char* command = strtok(line, " ");
    char* input = strtok(NULL, "");

    if (strcmp(command, "open") == 0) {
        if (root) {
            printf("Error: List is already open. Try clearing first...");
            return root;
        } else if (!input) {
            printf("Error: Not enough input provided to open.");
            return root;
        }

        char* inputCopy = malloc((strlen(input) + 1) * sizeof(char));
        strcpy(inputCopy, input);

        root = calloc(1, sizeof(list_node));
        root->value = inputCopy;
    } else if (strcmp(command, "push") == 0) {
        if (!input) {
            printf("Error: Not enough input provided to push.");
            return root;
        }

        char* inputCopy = malloc((strlen(input) + 1) * sizeof(char));
        strcpy(inputCopy, input);

        ll_push(root, inputCopy);
        printf("Pushed. Added %s to the list.\n", input);
    } else if (strcmp(command, "print") == 0) {
        print(root);
    } else if (strcmp(command, "clear") == 0) {
        if (root == NULL) {
            printf("Already clear. Try opening first...\n");
            return root;
        }

        ll_clear(root);
        root = NULL;
    } else {
        printf("Unknown command.\n");
    }

    return root;
}

int main(void) {
    char *input = NULL;
    list_node *root = NULL;

    while (true) {
        printf("Enter a command to perform (q to quit):\n");

        input = slurp(input);

        if (strcmp(input, "q") == 0) {
            free(input);
            printf("Goodbye!\n");
            break;
        }

        root = handle_command(root, input);
        free(input);
        input = NULL;
    }
}
