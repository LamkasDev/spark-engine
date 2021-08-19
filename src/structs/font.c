#include "../components/component_data.h"
#include "../utils/hashmap_utils.h"

SparkFont sparkCreateFont(char* name) {
    char* uuid = sparkGenerateUUID();
    SparkFont font = {
        .uuid = *uuid,
        .name = name
    };

    return font;
}

void sparkLoadFont(SparkRenderer* renderer, SparkFont* font, char* path) {
    FT_New_Face(renderer->ft, path, 0, &font->face);
}