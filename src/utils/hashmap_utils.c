int sparkHashmapComponentCompare(const void *a, const void *b, void *udata) {
    const SparkComponentData *ua = a;
    const SparkComponentData *ub = b;
    return strcmp(ua->key, ub->key);
}

uint64_t sparkHasmapComponentHash(const void *item, uint64_t seed0, uint64_t seed1) {
    const SparkComponentData *user = item;
    return hashmap_sip(user->key, strlen(user->key), seed0, seed1);
}