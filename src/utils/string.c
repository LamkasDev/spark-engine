char* sparkStringReplace(char* orig, char* rep, char* with) {
    char* result;
    char* ins;
    char* tmp;
    int count;

    if (!with) {
        with = "";
    }
    int len_front;
    int len_rep = strlen(rep);
    int len_with = strlen(with);

    ins = orig;
    for (count = 0; tmp = strstr(ins, rep); ++count) {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);
    if (!result) {
        return NULL;
    }

    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep;
    }
    
    strcpy(tmp, orig);
    return result;
}