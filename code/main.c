#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "rbt.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

bool valid_int(const char *str) {
    if (*str == '-') {
        str++;
    }

    if (!*str) {
        return false;
    }

    while (*str) {
        if (!isdigit((unsigned char) *str++)) {
            return false;
        }
    }
    return true;
}


int main() {
    printf("=============================================================================\n"
           "This program is designed to give a visual representation how a Red-Black tree\n"
           "balances itself as we insert nodes.\n"
           "- The program will ask you to insert nodes. After each insertion, the tree\n"
           "  will be pretty printed for easier visualization.\n"
           "- Note that it becomes harder to visualize for large input sizes due to the"
           "  algorithm used for pretty printing.\n"
           "- Press 'q' or 'Ctrl-C' to exit the program.\n"
           "=============================================================================\n");
    Tree *tree = rbt_init();
    char data[256];
    while (true) {
        printf("Enter integer input: ");
        scanf("%255s", data);

        if (!strcmp(data, "q")) {
            printf("Goodbye.\n");
            #ifdef _WIN32
            Sleep(1000);
            system("clear");
            #else
            sleep(1);
            system("clear");
            #endif
            break;
        }

        if (!valid_int(data)) {
            printf("Please enter an integer\n");
            continue;
        }

        tree->root = rbt_insert(tree, atoi(data));
        printf("The tree after inputting %d:\n", atoi(data));
        printf("==================================================\n");
        rbt_print_tree(tree->root);
        printf("==================================================\n");
    }

    return 0;
}
