#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include "libmessage.h"

char *get_message_lib() {
    // library pointer
    void *message_lib;
    // library file name
    char *mfile_prefix = (char *)LANG_FILE_PREFIX;
    char *mfile_ending =(char *)LANG_FILE_ENDING;
    // check for env variable
    char *mfile_lang = getenv(LANG_ENV_VARIABLE);
    if (mfile_lang == NULL) {
        mfile_lang = (char *)"en";
    }
    // prepare library file name
    int mfile_name_len = strlen(mfile_prefix) + strlen(mfile_lang) + strlen(mfile_ending) + 1;
    char *mfile_name = (char *)malloc(mfile_name_len);
    snprintf(mfile_name, mfile_name_len, "%s%s%s", mfile_prefix, mfile_lang, mfile_ending);
    // load language lib
    message_lib = dlopen(mfile_name, RTLD_LAZY);
    if (!message_lib) {
        printf("Cannot open message library %s", mfile_name);
        exit(EXIT_FAILURE);
    }
    return (char *)message_lib;
}

char *get_message(void *lib, char *code) {
    char *(*fptr)(char *);
    // make a pointer to method in lib
    *(void **)(&fptr) = dlsym(lib, "getm");
    char *dl_error = dlerror();
    if (dl_error) {
        printf("Cannot find or open %s function", code);
        return NULL;
    }
    char *r = fptr(code);
    return r;
}

