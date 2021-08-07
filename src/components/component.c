#include "../gameobjects/gameobject.h"
#include "../utils/hashmap_utils.h"

SparkComponent* sparkCreateComponent(void* _gameObject, int type) {
    SparkGameObject* gameObject = (SparkGameObject*)_gameObject;
    SparkComponent component = { 
        .type = type,
        .data = hashmap_new(sizeof(SparkComponentData), 0, 0, 0, sparkHasmapComponentHash, sparkHashmapComponentCompare, NULL)
    };

    vector_add(&gameObject->components, component);
    return &gameObject->components[vector_size(gameObject->components) - 1];
}