/**
 * Setups a SparkApp.
 * 
 * @param app a pointer to an app
 * 
 */
void sparkSetupApp(SparkApp* app) {
    app->executablePath = sparkGetExecutablePath();
    app->assetsPath = sparkCombinePaths(app->executablePath, sparkCreatePathFromString("/../data"));
}

/**
 * Setups a SparkApp's renderer, window and window icon.
 * 
 * @param app a pointer to an app
 * 
 */
void sparkSetupAppRenderer(SparkApp* app) {
    sparkSetupWindow(&app->renderer);

    stbi_set_flip_vertically_on_load(true);
    glEnable(GL_MULTISAMPLE);

    int iconC;
    GLFWimage icons[1];
    icons[0].pixels = stbi_load(sparkCombinePaths(app->assetsPath, sparkCreatePathFromString("/app/textures/icon.png")), &icons[0].width, &icons[0].height, &iconC, 0);
    glfwSetWindowIcon(app->renderer.window, 1, icons);
}

/**
 * Creates default shaders needed by the engine.
 * 
 * @param app a pointer to an app
 * 
 */
void sparkCreateDefaultShaders(SparkApp* app) {
    int size;
    const unsigned char* shadersRaw = sparkReadFile(sparkCombinePaths(app->assetsPath, sparkCreatePathFromString("/app/spark_objects/app_shaders.sobj")), false, &size);
    sparkCreateShadersFromJSON(&app->renderer, shadersRaw);
}

/**
 * Creates default fonts needed by the engine.
 * 
 * @param app a pointer to an app
 * 
 */
void sparkCreateDefaultFonts(SparkApp* app) {
    int size;
    const unsigned char* fontsRaw = sparkReadFile(sparkCombinePaths(app->assetsPath, sparkCreatePathFromString("/app/spark_objects/app_fonts.sobj")), false, &size);
    sparkCreateFontsFromJSON(&app->renderer, fontsRaw);
}

/**
 * Creates default textures needed by the engine.
 * 
 * @param app a pointer to an app
 * 
 */
void sparkCreateDefaultTextures(SparkApp* app) {
    int size;
    const unsigned char* texturesRaw = sparkReadFile(sparkCombinePaths(app->assetsPath, sparkCreatePathFromString("/app/spark_objects/app_textures.sobj")), false, &size);
    sparkCreateTexturesFromJSON(&app->renderer, texturesRaw);
}

/**
 * Creates default materials needed by the engine.
 * 
 * @param app a pointer to an app
 * 
 */
void sparkCreateDefaultMaterials(SparkApp* app) {
    int size;
    const unsigned char* materialsRaw = sparkReadFile(sparkCombinePaths(app->assetsPath, sparkCreatePathFromString("/app/spark_objects/app_materials.sobj")), false, &size);
    sparkCreateMaterialsFromJSON(&app->renderer, materialsRaw);
}