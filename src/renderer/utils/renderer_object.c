void sparkGenerateBuffersInRendererObject(SparkRendererObject* rendererObject) {
    glGenVertexArrays(1, &rendererObject->VAO);
    glGenBuffers(1, &rendererObject->VBO);
    glGenBuffers(1, &rendererObject->EBO);
}

void sparkBufferDataInRendererObject(SparkRendererObject* rendererObject) {
    glBufferData(GL_ARRAY_BUFFER, vector_size(rendererObject->vertices) * sizeof(GLfloat), rendererObject->vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, vector_size(rendererObject->indices) * sizeof(GLuint), rendererObject->indices, GL_STATIC_DRAW);
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

void sparkDrawRendererObject(SparkRendererObject* rendererObject) {
    glDrawElements(rendererObject->drawType, vector_size(rendererObject->indices), GL_UNSIGNED_INT, 0);
}

void sparkUnbindRendererObject() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void sparkDeleteRendererObject(SparkRendererObject* rendererObject) {
    glDeleteVertexArrays(1, &rendererObject->VAO);
    glDeleteBuffers(1, &rendererObject->VBO);
    glDeleteBuffers(1, &rendererObject->EBO);
}