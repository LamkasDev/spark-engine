#ifndef STORE_H_INCLUDED
#define STORE_H_INCLUDED

struct SparkStore {
    int* integers;
    float* floats;
    char** strings;
    SparkColor* colors;
};
typedef struct SparkStore SparkStore;
SparkStore sparkCreateStore();

#endif