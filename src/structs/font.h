#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED

#include "character.h"

struct SparkFont {
    char uuid[32];
    char* name;

    hashmap characters;
};
typedef struct SparkFont SparkFont;
SparkFont sparkCreateFont(char* name);
void sparkLoadFont(FT_Library* library, SparkFont* font, char* path);
void sparkDeleteFont(SparkFont* font);
bool sparkDeleteFontIter(const void *item, void *udata);

#endif