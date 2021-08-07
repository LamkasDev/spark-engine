#ifndef HASHMAP_UTILS_H_INCLUDED
#define HASHMAP_UTILS_H_INCLUDED

int sparkHashmapComponentCompare(const void *a, const void *b, void *udata);
uint64_t sparkHasmapComponentHash(const void *item, uint64_t seed0, uint64_t seed1);

#endif