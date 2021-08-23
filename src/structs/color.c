SparkColor sparkCreateColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
    SparkColor color = {
        .r = r,
        .g = g,
        .b = b,
        .a = a
    };

    return color;
}

SparkColor sparkCreateColorFromHex(int hex, GLfloat a) {
    SparkColor color = {
        .r = ((hex >> 16) & 0xFF) / 255.0f,
        .g = ((hex >> 8) & 0xFF) / 255.0f,
        .b = (hex & 0xFF) / 255.0f,
        .a = a
    };

    return color;
}