#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

struct SparkCharacter {
    GLuint id;
    
    unsigned char c;
    SparkVector2 size;
    SparkVector2 bearing;
    unsigned int advance;
};
typedef struct SparkCharacter SparkCharacter;

#endif