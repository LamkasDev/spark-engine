void sparkInitializeShader(SparkShader* shader, char* name, const char* vertexSource, const char* fragmentSource) {
    shader->id = glCreateProgram();
    shader->name = name;

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    sparkVerifyShader(shader, vertexShader, "VERTEX");

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    sparkVerifyShader(shader, fragmentShader, "FRAGMENT");

    glAttachShader(shader->id, vertexShader);
    glAttachShader(shader->id, fragmentShader);
    glLinkProgram(shader->id);
    sparkVerifyShader(shader, shader->id, "PROGRAM");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void sparkActivateShader(SparkShader* shader) {
    glUseProgram(shader->id);
}

void sparkDeleteShader(SparkShader* shader) {
    glDeleteProgram(shader->id);
}

bool sparkDeleteShaderIter(const void *item, void *udata) {
    SparkShader* shader = (SparkShader*)item;
    sparkDeleteShader(shader);
    return true;
}

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