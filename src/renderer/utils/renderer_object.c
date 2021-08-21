void sparkGenerateBuffersInRendererObject(SparkRendererObject* rendererObject) {
    glGenVertexArrays(1, &rendererObject->VAO);
    glGenBuffers(1, &rendererObject->VBO);
    glGenBuffers(1, &rendererObject->EBO);
}

void sparkLinkAttributesInRendererObject(SparkRendererObject* rendererObject, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
}

void sparkBindRendererObject(SparkRendererObject* rendererObject) {
    glBindVertexArray(rendererObject->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, rendererObject->VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererObject->EBO);
}

void sparkUnbindRendererObject(SparkRendererObject* rendererObject) {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void sparkBufferDataInRendererObject(SparkRendererObject* rendererObject) {
    glBufferData(GL_ARRAY_BUFFER, vector_size(rendererObject->vertices) * sizeof(GLfloat), rendererObject->vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, vector_size(rendererObject->indices) * sizeof(GLuint), rendererObject->indices, GL_STATIC_DRAW);
}

void sparkInitializeRendererObject(SparkRendererObject* rendererObject) {
    sparkGenerateBuffersInRendererObject(rendererObject);
    sparkBindRendererObject(rendererObject);

    switch(rendererObject->component->type) {
        case COMPONENT_TYPE_2D_RENDERER:
        case COMPONENT_TYPE_3D_RENDERER: {
            sparkLinkAttributesInRendererObject(rendererObject, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
            sparkLinkAttributesInRendererObject(rendererObject, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
            break;
        }

        case COMPONENT_TYPE_2D_TEXTURE_RENDERER:
        case COMPONENT_TYPE_3D_TEXTURE_RENDERER:
        case COMPONENT_TYPE_TEXT_RENDERER: {
            sparkLinkAttributesInRendererObject(rendererObject, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
            sparkLinkAttributesInRendererObject(rendererObject, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
            break;
        }
    }

    sparkUnbindRendererObject(rendererObject);
}

void sparkDrawRendererObject(SparkRendererObject* rendererObject) {
    glDrawElements(rendererObject->drawType, vector_size(rendererObject->indices), GL_UNSIGNED_INT, 0);
}

void sparkDeleteRendererObject(SparkRendererObject* rendererObject) {
    glDeleteVertexArrays(1, &rendererObject->VAO);
    glDeleteBuffers(1, &rendererObject->VBO);
    glDeleteBuffers(1, &rendererObject->EBO);
}