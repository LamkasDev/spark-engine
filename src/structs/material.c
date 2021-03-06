#include "../components/component_data.h"
#include "../utils/hashmap_utils.h"

/**
 * Creates a new material.
 * 
 * @param name name of the material
 * @param shader a pointer to the material shader
 * 
 */
SparkMaterial sparkCreateMaterial(char* name, SparkShader* shader) {
    char* uuid = sparkGenerateUUID();
    SparkMaterial material = {
        .uuid = *uuid,
        .name = name,
        .data = hashmap_new(sizeof(SparkComponentData), 0, 0, 0, sparkHasmapComponentHash, sparkHashmapComponentCompare, NULL)
    };
    hashmap_set(material.data, &(SparkComponentData){ .key = "shader", .data = shader });

    return material;
}

/**
 * Deletes a material.
 * 
 * @param texture a pointer to a texture
 * 
 */
void sparkDeleteMaterial(SparkMaterial* material) {

}

/**
 * An iterator to delete all materials in a hashmap.
 */
bool sparkDeleteMaterialIter(const void *item, void *udata) {
    SparkMaterial* material = (SparkMaterial*)item;
    sparkDeleteMaterial(material);
    return true;
}