#ifndef HASHMAP_UTILS_H_INCLUDED
#define HASHMAP_UTILS_H_INCLUDED

int sparkHashmapComponentCompare(const void *a, const void *b, void *udata);
uint64_t sparkHasmapComponentHash(const void *item, uint64_t seed0, uint64_t seed1);

int sparkHashmapShaderCompare(const void *a, const void *b, void *udata);
uint64_t sparkHasmapShaderHash(const void *item, uint64_t seed0, uint64_t seed1);

int sparkHashmapTextureCompare(const void *a, const void *b, void *udata);
uint64_t sparkHashmapTextureHash(const void *item, uint64_t seed0, uint64_t seed1);

int sparkHashmapMaterialCompare(const void *a, const void *b, void *udata);
uint64_t sparkHashmapMaterialHash(const void *item, uint64_t seed0, uint64_t seed1);

int sparkHashmapFontCompare(const void *a, const void *b, void *udata);
uint64_t sparkHashmapFontHash(const void *item, uint64_t seed0, uint64_t seed1);

#endif