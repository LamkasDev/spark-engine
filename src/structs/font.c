#include "character.h"
#include "../components/component_data.h"
#include "../utils/hashmap_utils.h"

/**
 * Creates a new font.
 * 
 * @param name name of the font
 * 
 */
SparkFont sparkCreateFont(char* name) {
    char* uuid = sparkGenerateUUID();
    SparkFont font = {
        .uuid = *uuid,
        .name = name,
        .characters = hashmap_new(sizeof(SparkCharacter), 0, 0, 0, sparkHashmapCharacterHash, sparkHashmapCharacterCompare, NULL)
    };

    return font;
}

/**
 * Loads a font from a file.
 * 
 * @param library a pointer to a font library
 * @param font a pointer to a font
 * @param path path to the font file
 * 
 */
void sparkLoadFont(FT_Library* library, SparkFont* font, char* path) {
    FT_Face face;
    FT_New_Face(*library, path, 0, &face);
    FT_Set_Pixel_Sizes(face, 0, 48);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    for (unsigned char c = 0; c < 128; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            continue;
        }
        
        SparkCharacter character = {
            .c = c,
            .size = { .x = face->glyph->bitmap.width, .y = face->glyph->bitmap.rows },
            .bearing = { .x = face->glyph->bitmap_left, .y = face->glyph->bitmap_top },
            .advance = face->glyph->advance.x
        };
        glActiveTexture(GL_TEXTURE0);
        glGenTextures(1, &character.id);
        glBindTexture(GL_TEXTURE_2D, character.id);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        hashmap_set(font->characters, &character);
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    FT_Done_Face(face);
}