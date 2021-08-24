/**
 * Creates a new component of a type on a game object.
 * 
 * @param _gameObject a pointer to a gameobject
 * @param type component type
 * 
 */
SparkComponent* sparkCreateComponent(void* _gameObject, int type) {
    SparkGameObject* gameObject = (SparkGameObject*)_gameObject;
    SparkComponent component = { 
        .type = type,
        .data = hashmap_new(sizeof(SparkComponentData), 0, 0, 0, sparkHasmapComponentHash, sparkHashmapComponentCompare, NULL)
    };

    vector_add(&gameObject->components, component);
    return &gameObject->components[vector_size(gameObject->components) - 1];
}