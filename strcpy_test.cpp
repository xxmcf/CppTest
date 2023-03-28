
char* my_strcpy(char* dst, char* src) {
    if (!dst || !src || dst == src) {
        return dst;
    }
    char * temp = dst;
    while(*src != '\0') {
        *(temp++) = *(src++);
    }
    *temp = '\0';
    return dst;
}