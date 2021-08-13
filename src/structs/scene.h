#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include "../gameobjects/gameobject.h"

struct SparkScene {
    char* name;
    SparkGameObject* gameObjects;
};
typedef struct SparkScene SparkScene;
SparkScene sparkCreateScene(char* name);

#endif