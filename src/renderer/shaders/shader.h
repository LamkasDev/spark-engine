#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED

struct SparkShader {
    GLuint id;
    char* name;
};
typedef struct SparkShader SparkShader;
void sparkInitializeShader(SparkShader* shader, char* name, const char* vertexSource, const char* fragmentSource);
void sparkActivateShader(SparkShader* shader);
void sparkDeleteShader(SparkShader* shader);
bool sparkDeleteShaderIter(const void *item, void *udata);
void sparkVerifyShader(SparkShader* shader, unsigned int id, char* type);

#endif