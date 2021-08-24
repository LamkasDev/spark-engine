/**
 * Creates a new shader consisting from a vertex and a fragment shader.
 * 
 * @param name name of the shader
 * @param vertexSource vertex source of the shader
 * @param fragmentSource fragment source of the shader
 * 
 */
SparkShader sparkCreateShader(char* name, const char* vertexSource, const char* fragmentSource) {
    char* uuid = sparkGenerateUUID();
    SparkShader shader = {
        .id = glCreateProgram(),
        .uuid = *uuid,
        .name = name
    };

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    sparkVerifyShader(&shader, vertexShader, "VERTEX");

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    sparkVerifyShader(&shader, fragmentShader, "FRAGMENT");

    glAttachShader(shader.id, vertexShader);
    glAttachShader(shader.id, fragmentShader);
    glLinkProgram(shader.id);
    sparkVerifyShader(&shader, shader.id, "PROGRAM");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shader;
}

/**
 * Activates a shader.
 * 
 * @param shader a pointer to a shader
 * 
 */
void sparkActivateShader(SparkShader* shader) {
    glUseProgram(shader->id);
}

/**
 * Deletes a shader.
 * 
 * @param shader a pointer to a shader
 * 
 */
void sparkDeleteShader(SparkShader* shader) {
    glDeleteProgram(shader->id);
}

/**
 * An iterator to delete all shaders in a hashmap.
 */
bool sparkDeleteShaderIter(const void *item, void *udata) {
    SparkShader* shader = (SparkShader*)item;
    sparkDeleteShader(shader);
    return true;
}

/**
 * Verifies a shader for errors.
 * 
 * @param shader a pointer to a shader
 * @param shader a shader ID
 * @param type type of the shader
 * 
 */
void sparkVerifyShader(SparkShader* shader, unsigned int id, char* type) {
    GLint status;
    char infoLog[1024];
    if(type != "PROGRAM") {
        glGetShaderiv(id, GL_COMPILE_STATUS, &status);
        if(status == GL_FALSE) {
            glGetShaderInfoLog(id, 1024, NULL, infoLog);
            printf("Shader \"%s\" failed to compile:\n%s", shader->name, infoLog);
        }
    } else {
        glGetProgramiv(id, GL_COMPILE_STATUS, &status);
        if(status == GL_FALSE) {
            glGetProgramInfoLog(id, 1024, NULL, infoLog);
            printf("Shader \"%s\" failed to link for %s:\n%s", shader->name, type, infoLog);
        }
    }
}