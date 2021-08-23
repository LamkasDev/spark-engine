#ifndef STORE_UTILS_H_INCLUDED
#define STORE_UTILS_H_INCLUDED

void* sparkCreateStoreInteger(SparkStore* store, int value);
void* sparkCreateStoreFloat(SparkStore* store, float value);
void* sparkCreateStoreString(SparkStore* store, char* value);
void* sparkCreateStoreColor(SparkStore* store, SparkColor value);

#endif