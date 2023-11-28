#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liblang.h"

char *getm(char *code) {
    char mess[128] = "";
    if (strcmp(code, "_W_TITLE") == 0) {
        strcat(mess, _W_TITLE);
    }
    else if (strcmp(code, "_M_HELP") == 0) {
        strcat(mess, _M_HELP);
    }
    else if (strcmp(code, "_M_BCREATE") == 0) {
        strcat(mess, _M_BCREATE);
    }
    else if (strcmp(code, "_M_FEXIST") == 0) {
        strcat(mess, _M_FEXIST);
    }
    else if (strcmp(code, "_M_FCREATED") == 0) {
        strcat(mess, _M_FCREATED);
    }
    char* str = malloc(strlen(mess) + 1);
    strcpy(str, mess);
    return str;
}

