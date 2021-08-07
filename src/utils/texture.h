#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

struct SparkTexture {
    GLuint id;
    void* options;
};
typedef struct SparkTexture SparkTexture;
SparkTexture sparkCreateTexture();
void sparkLoadTexture(SparkTexture* texture, char* path);

#endif