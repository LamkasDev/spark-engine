#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include "../renderer/shaders/shader.h"

struct SparkMaterial {
    GLuint id;
    char* name;
    hashmap data;
};
typedef struct SparkMaterial SparkMaterial;
SparkMaterial sparkCreateMaterial(char* name, SparkShader* shader);

#endif