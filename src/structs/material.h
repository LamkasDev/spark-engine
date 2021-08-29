#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include "../renderer/shaders/shader.h"

struct SparkMaterial {
    char uuid[32];
    char* name;
    hashmap data;
};
typedef struct SparkMaterial SparkMaterial;
SparkMaterial sparkCreateMaterial(char* name, SparkShader* shader);
void sparkDeleteMaterial(SparkMaterial* material);
bool sparkDeleteMaterialIter(const void *item, void *udata);

#endif