#include "macros/language.h"
#include "io/io.h"

#include "structs/color.h"
#include "structs/material.h"
#include "structs/vector_2.h"
#include "structs/texture.h"
#include "structs/scene.h"

#include "gameobjects/gameobject.h"
#include "components/component.h"
#include "components/component_data.h"

#include "renderer/renderer.h"
#include "structs/font.h"

void run() {
    char* executablePath = sparkGetExecutablePath();
    char* assetsPath = sparkCombinePaths(executablePath, sparkCreatePathFromString("/../../../build_src"));

    printf("Started Spark Engine (%s)...\n", SPARK_VERSION);
    printf("=========\n");
    printf("Executable path: %s\n", executablePath);
    printf("Assets path: %s\n", assetsPath);
    printf("=========\n");
    printf("Initializing...\n");
    clock_t begin_0 = clock();

    /* Initialize stupid stuff */
    SparkRenderer renderer;
    sparkSetupWindow(&renderer);

    stbi_set_flip_vertically_on_load(true);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    int iconC;
    GLFWimage icons[1];
    icons[0].pixels = stbi_load(sparkCombinePaths(assetsPath, sparkCreatePathFromString("/textures/icon.png")), &icons[0].width, &icons[0].height, &iconC, 0);
    glfwSetWindowIcon(renderer.window, 1, icons);

    clock_t end_0 = clock();
    double elapsed_0 = (double)(end_0 - begin_0) / CLOCKS_PER_SEC;
    printf("Initialized (%.3fs)!\n", elapsed_0);
    printf("Compiling shaders...\n");
    clock_t begin_1 = clock();
    
    /* Compile shaders */
    SparkShader colorShader0 = sparkCompileShader(&renderer, "2DColor", sparkCombinePaths(assetsPath, sparkCreatePathFromString("/shaders/2D_color_vertex.shader")), sparkCombinePaths(assetsPath, sparkCreatePathFromString("/shaders/2D_color_fragment.shader")));
    SparkShader textureShader0 = sparkCompileShader(&renderer, "2DTexture", sparkCombinePaths(assetsPath, sparkCreatePathFromString("/shaders/2D_tex_vertex.shader")), sparkCombinePaths(assetsPath, sparkCreatePathFromString("/shaders/2D_tex_fragment.shader")));
    SparkShader colorShader1 = sparkCompileShader(&renderer, "3DColor", sparkCombinePaths(assetsPath, sparkCreatePathFromString("/shaders/3D_color_vertex.shader")), sparkCombinePaths(assetsPath, sparkCreatePathFromString("/shaders/3D_color_fragment.shader")));
    SparkShader textureShader1 = sparkCompileShader(&renderer, "3DTexture", sparkCombinePaths(assetsPath, sparkCreatePathFromString("/shaders/3D_tex_vertex.shader")), sparkCombinePaths(assetsPath, sparkCreatePathFromString("/shaders/3D_tex_fragment.shader")));
    SparkShader textShader0 = sparkCompileShader(&renderer, "Text", sparkCombinePaths(assetsPath, sparkCreatePathFromString("/shaders/text_vertex.shader")), sparkCombinePaths(assetsPath, sparkCreatePathFromString("/shaders/text_fragment.shader")));

    clock_t end_1 = clock();
    double elapsed_1 = (double)(end_1 - begin_1) / CLOCKS_PER_SEC;
    printf("Compiled shaders (%i shaders in %.3fs)!\n", hashmap_count(renderer.shaders), elapsed_1);
    printf("Loading fonts...\n");
    clock_t begin_2 = clock();
    
    /* Load fonts */
    SparkFont font_0 = sparkCreateFont("Arial");
    sparkLoadFont(&renderer, &font_0, sparkCombinePaths(assetsPath, sparkCreatePathFromString("/fonts/Arial.ttf")));
    FT_Done_FreeType(renderer.ft);

    clock_t end_2 = clock();
    double elapsed_2 = (double)(end_2 - begin_2) / CLOCKS_PER_SEC;
    printf("Loaded fonts (%i fonts in %.3fs)!\n", hashmap_count(renderer.fonts), elapsed_1);
    printf("Loading textures...\n");
    clock_t begin_5 = clock();
    
    /* Load textures */
    SparkTexture texture_0 = sparkCreateTexture("dvd");
    sparkLoadTexture(&texture_0, sparkCombinePaths(assetsPath, sparkCreatePathFromString("/textures/dvd.png")));
    hashmap_set(renderer.textures, &texture_0);

    clock_t end_5 = clock();
    double elapsed_5 = (double)(end_5 - begin_5) / CLOCKS_PER_SEC;
    printf("Loaded textures (%i textures in %.3fs)!\n", hashmap_count(renderer.textures), elapsed_5);
    printf("Creating materials...\n");
    clock_t begin_3 = clock();

    /* Create Materials */
    SparkColor colors[] = { { .r=1.0f, .g=1.0f, .b=1.0f, .a=1.0f } };
    int shapes[] = { RENDERER_SHAPE_QUAD };
    SparkVector2 sizes[] = { { .x = 180.0f, .y = 180.0f }, { .x = 350.0f, .y = 50.0f } };
    float borders[] = { 0.3f };
    char* texts[] = { "abc" };

    SparkMaterial material_0 = sparkCreateMaterial("Color 2D", &colorShader0);
    hashmap_set(material_0.data, &(SparkComponentData){ .key = "color", .data = &colors[0] });
    hashmap_set(material_0.data, &(SparkComponentData){ .key = "shape", .data = &shapes[0] });
    hashmap_set(renderer.materials, &material_0);

    SparkMaterial material_1 = sparkCreateMaterial("Texture 2D", &textureShader0);
    hashmap_set(material_1.data, &(SparkComponentData){ .key = "texture", .data = &texture_0 });
    hashmap_set(material_1.data, &(SparkComponentData){ .key = "shape", .data = &shapes[0] });
    hashmap_set(renderer.materials, &material_1);

    SparkMaterial material_2 = sparkCreateMaterial("Color 3D", &colorShader1);
    hashmap_set(material_2.data, &(SparkComponentData){ .key = "color", .data = &colors[0] });
    hashmap_set(material_2.data, &(SparkComponentData){ .key = "shape", .data = &shapes[0] });
    hashmap_set(renderer.materials, &material_2);

    SparkMaterial material_3 = sparkCreateMaterial("Texture 3D", &textureShader1);
    hashmap_set(material_3.data, &(SparkComponentData){ .key = "texture", .data = &texture_0 });
    hashmap_set(material_3.data, &(SparkComponentData){ .key = "shape", .data = &shapes[0] });
    hashmap_set(renderer.materials, &material_3);

    SparkMaterial material_4 = sparkCreateMaterial("Font", &textShader0);
    hashmap_set(renderer.materials, &material_4);

    clock_t end_3 = clock();
    double elapsed_3 = (double)(end_3 - begin_3) / CLOCKS_PER_SEC;
    printf("Created materials (%i materials in %.3fs)!\n", hashmap_count(renderer.materials), elapsed_3);
    printf("Creating scene...\n");
    clock_t begin_4 = clock();

    /* Create Scene */
    SparkScene scene = sparkCreateScene("Default");

    SparkGameObject gameObject_0 = sparkCreateGameObject();
    SparkComponent* component_0 = sparkCreateComponent(&gameObject_0, COMPONENT_TYPE_2D_TEXTURE_RENDERER);
    gameObject_0.pos.y = 0.0f;
    hashmap_set(component_0->data, &(SparkComponentData){ .key = "size", .data = &sizes[0] });
    hashmap_set(component_0->data, &(SparkComponentData){ .key = "material", .data = &material_1 });
    vector_add(&scene.gameObjects, gameObject_0);

    SparkGameObject gameObject_1 = sparkCreateGameObject();
    SparkComponent* component_1 = sparkCreateComponent(&gameObject_1, COMPONENT_TYPE_TEXT_RENDERER);
    gameObject_1.pos.y = 0.0f;
    hashmap_set(component_1->data, &(SparkComponentData){ .key = "size", .data = &sizes[1] });
    hashmap_set(component_1->data, &(SparkComponentData){ .key = "text", .data = texts[0] });
    hashmap_set(component_1->data, &(SparkComponentData){ .key = "font", .data = &font_0 });
    hashmap_set(component_1->data, &(SparkComponentData){ .key = "material", .data = &material_4 });
    vector_add(&scene.gameObjects, gameObject_1);

    sparkLoadScene(&renderer, &scene);

    clock_t end_4 = clock();
    double elapsed_4 = (double)(end_4 - begin_4) / CLOCKS_PER_SEC;
    printf("Created scene (%i GameObjects in %.3fs)!\n", vector_size(scene.gameObjects), elapsed_4);
    printf("Rendering...\n");

    /* Render owo */
    sparkRender(&renderer);

    printf("Exiting...\n");
}