/**
 * Generates VAO, VBO and EBO buffers for a renderer object.
 * 
 * @param rendererObject a pointer to a renderer object
 * 
 */
void sparkGenerateBuffersInRendererObject(SparkRendererObject* rendererObject) {
    glGenVertexArrays(1, &rendererObject->VAO);
    glGenBuffers(1, &rendererObject->VBO);
    glGenBuffers(1, &rendererObject->EBO);
}

/**
 * Links renderer object's VAO buffer atrributes.
 * 
 * @param rendererObject a pointer to a renderer object
 * @param layout an index of a layout
 * @param numComponents a size of a layout
 * @param type a type of a layout
 * @param stride total size of all layouts in bytes
 * @param offset offset of a layout in bytes
 * 
 */
void sparkLinkAttributesInRendererObject(SparkRendererObject* rendererObject, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
}

/**
 * Binds a renderer object and all it's buffers.
 * 
 * @param rendererObject a pointer to a renderer object
 * 
 */
void sparkBindRendererObject(SparkRendererObject* rendererObject) {
    glBindVertexArray(rendererObject->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, rendererObject->VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererObject->EBO);

    if(rendererObject->component->type == COMPONENT_TYPE_TEXT_RENDERER) {
        glEnable(GL_BLEND);
    }
}

/**
 * Unbinds a renderer object and all it's buffers.
 * 
 * @param rendererObject a pointer to a renderer object
 * 
 */
void sparkUnbindRendererObject(SparkRendererObject* rendererObject) {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    if(rendererObject->component->type == COMPONENT_TYPE_TEXT_RENDERER) {
        glDisable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
}

/**
 * Buffers new data in a renderer object.
 * 
 * @param rendererObject a pointer to a renderer object
 * 
 */
void sparkBufferDataInRendererObject(SparkRendererObject* rendererObject) {
    glBufferData(GL_ARRAY_BUFFER, vector_size(rendererObject->vertices) * sizeof(GLfloat), rendererObject->vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, vector_size(rendererObject->indices) * sizeof(GLuint), rendererObject->indices, GL_STATIC_DRAW);
}

/**
 * Initializes a renderer object and all essentials with it.
 * 
 * @param rendererObject a pointer to a renderer object
 * 
 */
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

/**
 * Draws a renderer object.
 * 
 * @param rendererObject a pointer to a renderer object
 * 
 */
void sparkDrawRendererObject(SparkRendererObject* rendererObject) {
    glDrawElements(rendererObject->drawType, vector_size(rendererObject->indices), GL_UNSIGNED_INT, 0);
}

/**
 * Deletes a renderer object.
 * 
 * @param rendererObject a pointer to a renderer object
 * 
 */
void sparkDeleteRendererObject(SparkRendererObject* rendererObject) {
    glDeleteVertexArrays(1, &rendererObject->VAO);
    glDeleteBuffers(1, &rendererObject->VBO);
    glDeleteBuffers(1, &rendererObject->EBO);
}