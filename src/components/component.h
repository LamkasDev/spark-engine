#ifndef COMPONENT_H_INCLUDED
#define COMPONENT_H_INCLUDED

#define COMPONENT_TYPE_UNKNOWN -1
#define COMPONENT_TYPE_RENDERER 0
#define COMPONENT_TYPE_TEXTURE_RENDERER 1

#define COMPONENT_TYPE_TEXTURE_RENDERER 1

struct SparkComponent {
    int type;
    hashmap data;
};
typedef struct SparkComponent SparkComponent;
SparkComponent* sparkCreateComponent(void* gameObject, int type);

#endif