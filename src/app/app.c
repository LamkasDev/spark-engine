void sparkSetupApp(SparkApp* app) {
    app->executablePath = sparkGetExecutablePath();
    app->assetsPath = sparkCombinePaths(app->executablePath, sparkCreatePathFromString("/../../../build_src"));
}

void sparkSetupAppRenderer(SparkApp* app) {
    sparkSetupWindow(&app->renderer);

    stbi_set_flip_vertically_on_load(true);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    int iconC;
    GLFWimage icons[1];
    icons[0].pixels = stbi_load(sparkCombinePaths(app->assetsPath, sparkCreatePathFromString("/textures/icon.png")), &icons[0].width, &icons[0].height, &iconC, 0);
    glfwSetWindowIcon(app->renderer.window, 1, icons);
}

void sparkCompileDefaultShaders(SparkApp* app) {
    sparkCompileShader(&app->renderer, "2DColor", sparkCombinePaths(app->assetsPath, sparkCreatePathFromString("/shaders/2D_color_vertex.shader")), sparkCombinePaths(app->assetsPath, sparkCreatePathFromString("/shaders/2D_color_fragment.shader")));
    sparkCompileShader(&app->renderer, "2DTexture", sparkCombinePaths(app->assetsPath, sparkCreatePathFromString("/shaders/2D_tex_vertex.shader")), sparkCombinePaths(app->assetsPath, sparkCreatePathFromString("/shaders/2D_tex_fragment.shader")));
    sparkCompileShader(&app->renderer, "3DColor", sparkCombinePaths(app->assetsPath, sparkCreatePathFromString("/shaders/3D_color_vertex.shader")), sparkCombinePaths(app->assetsPath, sparkCreatePathFromString("/shaders/3D_color_fragment.shader")));
    sparkCompileShader(&app->renderer, "3DTexture", sparkCombinePaths(app->assetsPath, sparkCreatePathFromString("/shaders/3D_tex_vertex.shader")), sparkCombinePaths(app->assetsPath, sparkCreatePathFromString("/shaders/3D_tex_fragment.shader")));
    sparkCompileShader(&app->renderer, "Text", sparkCombinePaths(app->assetsPath, sparkCreatePathFromString("/shaders/text_vertex.shader")), sparkCombinePaths(app->assetsPath, sparkCreatePathFromString("/shaders/text_fragment.shader")));
}

void sparkLoadDefaultFonts(SparkApp* app) {
    SparkFont font_0 = sparkCreateFont("Arial");
    sparkLoadFont(&app->renderer.ft, &font_0, sparkCombinePaths(app->assetsPath, sparkCreatePathFromString("/fonts/Arial.ttf")));
    hashmap_set(app->renderer.fonts, &font_0);
}

void sparkLoadDefaultTextures(SparkApp* app) {

}

void sparkCreateDefaultMaterials(SparkApp* app) {
    int shape = RENDERER_SHAPE_QUAD;
    SparkShader* shader_1 = hashmap_get(app->renderer.shaders, &(SparkShader){ .name = "Text" });

    SparkMaterial material_0 = sparkCreateMaterial("Text", shader_1);
    hashmap_set(app->renderer.materials, &material_0);
}