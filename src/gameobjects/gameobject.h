#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

struct SparkGameObject {
    SparkVector3 pos;
    SparkVector3 scale;
    SparkComponent* components;
};
typedef struct SparkGameObject SparkGameObject;
SparkGameObject sparkCreateGameObject();

#endif