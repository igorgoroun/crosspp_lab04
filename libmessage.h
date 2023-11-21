#define LANG_ENV_VARIABLE "LANGUAGE"
#define LANG_FILE_PREFIX "liblang_"
#define LANG_FILE_ENDING ".so"

char *get_message_lib();
char *get_message(void *lib, char *code);
