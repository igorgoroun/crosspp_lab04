#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include "libtouch.h"


// Implementation for unix systems
unsigned char dir_exists(char *dir_path) {
    struct stat dirStat;
    if (stat(dir_path, &dirStat) == 0 && S_ISDIR(dirStat.st_mode)) return 1;
    else return 0;
}
void dir_create(char *dir_path) {
    mkdir(dir_path, 0755);
}
unsigned char file_exists(char *file_path){
    struct stat fileStat;
    if (stat(file_path, &fileStat) == 0 && S_ISREG(fileStat.st_mode)) return 1;
    else return 0;
}
void file_create(char *file_path){
    FILE *f = fopen(file_path, "w");
    fclose(f);
}
signed char touch(const char *file_path) {
    // 1 - all good
    // 0 - file exists
    char dirs[MAX_DIRS][MAX_DIR_LEN];
    for (int i = 0; i < MAX_DIRS; i++) strcpy(dirs[i], "");
    int dir_count = 0;
    char *filename;

    char *token = strtok((char*)file_path, LNS); 
    while (token != NULL && dir_count < MAX_DIRS) {
        filename = token;
        strcpy(dirs[dir_count], token);
        dir_count++;
        token = strtok(NULL, LNS);
    }
    
    char dir_path[MAX_DIRS*MAX_DIR_LEN] = "";
    if (FIRST_SLASH == 1) strcat(dir_path, LNS);
    strcat(dir_path, dirs[0]);
    for (int i = 1; i < dir_count - 1; i++) {
        strcat(dir_path, LNS);
        strcat(dir_path, dirs[i]);
        unsigned char res = dir_exists(dir_path);
        if (res == 0) {
            dir_create(dir_path);
        }
    }

    strcat(dir_path, LNS);
    strcat(dir_path, filename);
    unsigned char file_res = file_exists(dir_path);
    if (file_res == 0) {
        file_create(dir_path);
    } else {
        return ERR_CODE_FEXISTS;
    }

    return ERR_CODE_DONE;
}