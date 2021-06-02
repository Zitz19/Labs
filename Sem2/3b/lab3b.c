#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dialog.h"

const char *MSGS[] = {"0. Quit"};

const int MSGS_SIZE = sizeof(MSGS) / sizeof(MSGS[0]);

int main() {
    int c = 0;
    do {
        c = dialog(MSGS, MSGS_SIZE);
        switch (c) {
            case 0:
                break;
            case 1:

                break;
        }
    } while (c != 0);
    return 0;
}