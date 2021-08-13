#include "../components/component_data.h"
#include "../utils/hashmap_utils.h"

SparkMaterial sparkCreateMaterial(char* name, SparkShader* shader) {
    SparkMaterial material = {
        .name = name,
        .data = hashmap_new(sizeof(SparkComponentData), 0, 0, 0, sparkHasmapComponentHash, sparkHashmapComponentCompare, NULL)
    };
    hashmap_set(material.data, &(SparkComponentData){ .key = "shader", .data = shader });

    return material;
}