#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include "../gameobjects/gameobject.h"

struct SparkScene {
    char uuid[32];
    char* name;
    SparkGameObject* gameObjects;
};
typedef struct SparkScene SparkScene;
SparkScene sparkCreateScene(char* name);
void sparkLoadSceneFromFile(void* _renderer, SparkScene* scene, char* path);

#endif