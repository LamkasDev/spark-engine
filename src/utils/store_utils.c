/**
 * Stores an integer and returns it's index in a store vector.
 * 
 * @param store a pointer to a store
 * @param value value to store
 * 
 */
void* sparkCreateStoreInteger(SparkStore* store, int value) {
    vector_add(&store->integers, value);
    return (void*)(vector_size(store->integers) - 1);
}

/**
 * Stores a float and returns it's index in a store vector.
 * 
 * @param store a pointer to a store
 * @param value value to store
 * 
 */
void* sparkCreateStoreFloat(SparkStore* store, float value) {
    vector_add(&store->floats, value);
    return (void*)(vector_size(store->floats) - 1);
}

/**
 * Stores a string and returns it's index in a store vector.
 * 
 * @param store a pointer to a store
 * @param value value to store
 * 
 */
void* sparkCreateStoreString(SparkStore* store, char* value) {
    vector_add(&store->strings, value);
    return (void*)(vector_size(store->strings) - 1);
}

/**
 * Stores a color and returns it's index in a store vector.
 * 
 * @param store a pointer to a store
 * @param value value to store
 * 
 */
void* sparkCreateStoreColor(SparkStore* store, SparkColor value) {
    vector_add(&store->colors, value);
    return (void*)(vector_size(store->colors) - 1);
}