int sparkHashmapComponentCompare(const void *a, const void *b, void *udata) {
    const SparkComponentData *ia = a;
    const SparkComponentData *ib = b;
    return strcmp(ia->key, ib->key);
}

uint64_t sparkHasmapComponentHash(const void *item, uint64_t seed0, uint64_t seed1) {
    const SparkComponentData *comp = item;
    return hashmap_sip(comp->key, strlen(comp->key), seed0, seed1);
}

int sparkHashmapShaderCompare(const void *a, const void *b, void *udata) {
    const SparkShader *ia = a;
    const SparkShader *ib = b;
    return strcmp(ia->name, ib->name);
}

uint64_t sparkHasmapShaderHash(const void *item, uint64_t seed0, uint64_t seed1) {
    const SparkShader *shader = item;
    return hashmap_sip(shader->name, strlen(shader->name), seed0, seed1);
}

int sparkHashmapTextureCompare(const void *a, const void *b, void *udata) {
    const SparkTexture *ia = a;
    const SparkTexture *ib = b;
    return strcmp(ia->name, ib->name);
}

uint64_t sparkHashmapTextureHash(const void *item, uint64_t seed0, uint64_t seed1) {
    const SparkTexture *tex = item;
    return hashmap_sip(tex->name, strlen(tex->name), seed0, seed1);
}

int sparkHashmapMaterialCompare(const void *a, const void *b, void *udata) {
    const SparkMaterial *ia = a;
    const SparkMaterial *ib = b;
    return strcmp(ia->name, ib->name);
}

uint64_t sparkHashmapMaterialHash(const void *item, uint64_t seed0, uint64_t seed1) {
    const SparkMaterial *mat = item;
    return hashmap_sip(mat->name, strlen(mat->name), seed0, seed1);
}

int sparkHashmapFontCompare(const void *a, const void *b, void *udata) {
    const SparkFont *ia = a;
    const SparkFont *ib = b;
    return strcmp(ia->name, ib->name);
}

uint64_t sparkHashmapFontHash(const void *item, uint64_t seed0, uint64_t seed1) {
    const SparkFont *font = item;
    return hashmap_sip(font->name, strlen(font->name), seed0, seed1);
}

int sparkHashmapCharacterCompare(const void *a, const void *b, void *udata) {
    const SparkCharacter *ia = a;
    const SparkCharacter *ib = b;
    return strcmp(&ia->c, &ib->c);
}

uint64_t sparkHashmapCharacterHash(const void *item, uint64_t seed0, uint64_t seed1) {
    const SparkCharacter *character = item;
    return hashmap_sip(&character->c, 1, seed0, seed1);
}