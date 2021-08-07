#ifndef COMPONENT_DATA_H_INCLUDED
#define COMPONENT_DATA_H_INCLUDED

struct SparkComponentData {
    char* key;
    void* data;
};
typedef struct SparkComponentData SparkComponentData;

#endif