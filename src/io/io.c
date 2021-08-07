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