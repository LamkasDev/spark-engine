#include "../components/component_data.h"
#include "../utils/hashmap_utils.h"

/**
 * Creates a new textures.
 * 
 * @param name name of the texture
 * 
 */
SparkTexture sparkCreateTexture(char* name) {
    char* uuid = sparkGenerateUUID();
    int filter = GL_NEAREST;
    int wrap = GL_REPEAT;

    SparkTexture texture = {
        .uuid = *uuid,
        .name = name,
        .options = hashmap_new(sizeof(SparkComponentData), 0, 0, 0, sparkHasmapComponentHash, sparkHashmapComponentCompare, NULL)
    };
    hashmap_set(texture.options, &(SparkComponentData){ .key = "filter", .data = &filter });
    hashmap_set(texture.options, &(SparkComponentData){ .key = "wrap", .data = &wrap });
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &texture.id);

    return texture;
}

/**
 * Loads a textures from a file.
 * 
 * @param texture a pointer to a texture
 * @param path path to the texture file
 * 
 */
void sparkLoadTexture(SparkTexture* texture, char* path) {
    SparkComponentData* filterData = hashmap_get(texture->options, &(SparkComponentData){ .key = "filter" });
    int* filter = filterData->data;
    SparkComponentData* wrapData = hashmap_get(texture->options, &(SparkComponentData){ .key = "wrap" });
    int* wrap = wrapData->data;

    int size;
    int imgW, imgH, imgC;
    const unsigned char* textureRaw = sparkReadFile(path, false, &size);
    char* textureData = stbi_load_from_memory(textureRaw, size, &imgW, &imgH, &imgC, 0);
    
    int colorType;
    switch(imgC) {
        case 3: {
            colorType = GL_RGB;
            break;
        }

        case 4: {
            colorType = GL_RGBA;
            break;
        }
    }
    
    glBindTexture(GL_TEXTURE_2D, texture->id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, *filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, *filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, *wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, *wrap);
    glTexImage2D(GL_TEXTURE_2D, 0, colorType, imgW, imgH, 0, colorType, GL_UNSIGNED_BYTE, textureData);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(textureData);
    glBindTexture(GL_TEXTURE_2D, 0);
}