#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

struct SparkTexture {
    GLuint id;
    char* name;
    void* options;
};
typedef struct SparkTexture SparkTexture;
SparkTexture sparkCreateTexture(char* name);
void sparkLoadTexture(SparkTexture* texture, char* path);

#endif