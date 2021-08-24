/**
 * Generates a "random" UUID.
 */
char* sparkGenerateUUID() {
    int length = 32;
    char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-";
    char* randomString = malloc((sizeof(char) * length) + sizeof(char));

    int l = (sizeof(charset) / sizeof(char)) - 1;
    int key;
    for (int n = 0; n < length; n++) {
        key = rand() % l;
        randomString[n] = charset[key];
    }
    randomString[length] = '\0';

    return randomString;
}