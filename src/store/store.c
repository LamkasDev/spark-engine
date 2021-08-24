/**
 * Creates a new store.
 */
SparkStore sparkCreateStore() {
    SparkStore store = {
        .integers = vector_create(),
        .floats = vector_create(),
        .strings = vector_create(),
        .colors = vector_create()
    };

    return store;
}