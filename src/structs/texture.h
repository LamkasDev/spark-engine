#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

struct SparkTexture {
    GLuint id;
    
    char uuid[32];
    char* name;
    void* options;
};
typedef struct SparkTexture SparkTexture;
SparkTexture sparkCreateTexture(char* name);
void sparkLoadTexture(SparkTexture* texture, char* path);

#endif