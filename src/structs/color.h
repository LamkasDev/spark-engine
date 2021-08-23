#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

struct SparkColor {
    GLfloat r;
    GLfloat g;
    GLfloat b;
    GLfloat a;
};
typedef struct SparkColor SparkColor;
SparkColor sparkCreateColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
SparkColor sparkCreateColorFromHex(int hex, GLfloat a);

#endif