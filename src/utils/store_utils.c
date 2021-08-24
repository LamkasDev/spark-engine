void* sparkCreateStoreInteger(SparkStore* store, int value) {
    vector_add(&store->integers, value);
    return (void*)(vector_size(store->integers) - 1);
}

void* sparkCreateStoreFloat(SparkStore* store, float value) {
    vector_add(&store->floats, value);
    return (void*)(vector_size(store->floats) - 1);
}

void* sparkCreateStoreString(SparkStore* store, char* value) {
    vector_add(&store->strings, value);
    return (void*)(vector_size(store->strings) - 1);
}

void* sparkCreateStoreColor(SparkStore* store, SparkColor value) {
    vector_add(&store->colors, value);
    return (void*)(vector_size(store->colors) - 1);
}