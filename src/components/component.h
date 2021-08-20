#ifndef COMPONENT_H_INCLUDED
#define COMPONENT_H_INCLUDED

#define COMPONENT_TYPE_UNKNOWN -1
#define COMPONENT_TYPE_2D_RENDERER 0
#define COMPONENT_TYPE_2D_TEXTURE_RENDERER 1
#define COMPONENT_TYPE_3D_RENDERER 2
#define COMPONENT_TYPE_3D_TEXTURE_RENDERER 3
#define COMPONENT_TYPE_TEXT_RENDERER 4

struct SparkComponent {
    int type;
    hashmap data;
};
typedef struct SparkComponent SparkComponent;
SparkComponent* sparkCreateComponent(void* gameObject, int type);

#endif