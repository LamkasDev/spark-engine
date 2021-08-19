#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED

struct SparkFont {
    char uuid[32];
    char* name;
    FT_Face face;
};
typedef struct SparkFont SparkFont;
SparkFont sparkCreateFont(char* name);
void sparkLoadFont(SparkRenderer* renderer, SparkFont* font, char* path);

#endif