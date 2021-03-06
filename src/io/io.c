/**
 * Reads a file and returns the content.
 * 
 * @param path a path to a file
 * @param terminate wherever to terminate the string
 * @param size a pointer to a size of the file (used to return the size)
 * 
 */
unsigned char* sparkReadFile(char path[255], bool terminate, int* size) {
    unsigned char* buffer = NULL;
    int file_size, read_size;

    FILE *handler = fopen(path, "rb");
    if(handler) {
        fseek(handler, 0, SEEK_END);
        file_size = ftell(handler);
        rewind(handler);

        buffer = (unsigned char*) malloc(sizeof(unsigned char) * (file_size + terminate));
        read_size = fread(buffer, sizeof(unsigned char), file_size, handler);
        if(terminate) {
            buffer[file_size] = '\0';
        }
        if (file_size != read_size) {
            free(buffer);
            buffer = NULL;
        }

        fclose(handler);
    }
    
    *size = file_size;
    return buffer;
}

/**
 * Returns the path to the executable.
 */
char* sparkGetExecutablePath() {
    char* path;
    #if(SPARK_OS == 0)
        path = _pgmptr;
    #endif
    #if(SPARK_OS == 1)
        char pathLink[FILENAME_MAX];
        readlink("/proc/self/exe", pathLink, FILENAME_MAX - 1);
        path = &pathLink;
    #endif

    return path;
}

/**
 * Combines 2 paths.
 * 
 * @param path1 first path
 * @param path2 second path
 * 
 */
char* sparkCombinePaths(char* path1, char* path2) {
    char* path = malloc((strlen(path1) + strlen(path2)) * sizeof(char));
    strcpy(path, path1);
    strcat(path, path2);
    return path;
}

/**
 * Creates a path from a string.
 * 
 * @param path path string
 * 
 */
char* sparkCreatePathFromString(char* path) {
    char* new_path = malloc(strlen(path) * sizeof(char));
    #if(SPARK_OS == 0)
        strcpy(new_path, sparkStringReplace(path, "/", "\\"));
    #endif
    #if(SPARK_OS == 1)
        strcpy(new_path, sparkStringReplace(path, "\\", "/"));
    #endif

    return new_path;
}