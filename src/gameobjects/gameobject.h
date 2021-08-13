#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include "../structs/vector_3.h"
#include "../components/component.h"

struct SparkGameObject {
    SparkVector3 pos;
    SparkComponent* components;
};
typedef struct SparkGameObject SparkGameObject;
SparkGameObject sparkCreateGameObject();

#endif