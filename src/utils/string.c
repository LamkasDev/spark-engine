/**
 * Replaces all occurances of a substring in a string with a new substring.
 * 
 * @param orig source string
 * @param rep substring to be replaced
 * @param with replacement string
 * 
 */
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

/**
 * Returns true, if the original string starts with the given substring.
 * 
 * @param orig source string
 * @param mat substring to match
 * 
 */
bool sparkStringStartsWith(const char *orig, const char *mat) {
    size_t lenorig = strlen(orig),
           lenmat = strlen(mat);
    return lenorig < lenmat ? false : memcmp(mat, orig, lenmat) == 0;
}