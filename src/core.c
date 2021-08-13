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

void run() {
    printf("Started Spark Engine (%s)...\n", SPARK_VERSION);
    printf("Initializing...\n");
    clock_t begin_0 = clock();

    /* Initialize stupid stuff */
    SparkRenderer renderer;
    sparkSetupWindow(&renderer);

    stbi_set_flip_vertically_on_load(true);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
    
    int iconC;
    GLFWimage icons[1];
    icons[0].pixels = stbi_load("D:\\Coding\\spark-engine\\build_src\\textures\\icon.png", &icons[0].width, &icons[0].height, &iconC, 0);
    glfwSetWindowIcon(renderer.window, 1, icons);

    clock_t end_0 = clock();
    double elapsed_0 = (double)(end_0 - begin_0) / CLOCKS_PER_SEC;
    printf("Initialized (%.3fs)!\n", elapsed_0);
    printf("Compiling shaders...\n");
    clock_t begin_1 = clock();
    
    /* Compile shaders */
    sparkCompileShaders(&renderer);

    /* [temporary] Get shaders */
    SparkShader* colorShader0 = hashmap_get(renderer.shaders, &(SparkShader){ .name = "2DColor" });
    SparkShader* textureShader0 = hashmap_get(renderer.shaders, &(SparkShader){ .name = "2DTexture" });
    SparkShader* colorShader1 = hashmap_get(renderer.shaders, &(SparkShader){ .name = "3DColor" });
    SparkShader* textureShader1 = hashmap_get(renderer.shaders, &(SparkShader){ .name = "3DTexture" });

    clock_t end_1 = clock();
    double elapsed_1 = (double)(end_1 - begin_1) / CLOCKS_PER_SEC;
    printf("Compiled shaders (%i shaders in %.3fs)!\n", hashmap_count(renderer.shaders), elapsed_1);
    printf("Loading textures...\n");
    clock_t begin_2 = clock();
    
    /* Load textures */
    SparkTexture texture_0 = sparkCreateTexture("chocola");
    sparkLoadTexture(&texture_0, "D:\\Coding\\spark-engine\\build_src\\textures\\chocola.png");
    hashmap_set(renderer.textures, &texture_0);

    clock_t end_2 = clock();
    double elapsed_2 = (double)(end_2 - begin_2) / CLOCKS_PER_SEC;
    printf("Loaded textures (%i textures in %.3fs)!\n", hashmap_count(renderer.textures), elapsed_2);
    printf("Creating materials...\n");
    clock_t begin_3 = clock();

    /* Create Materials */
    SparkColor colors[] = { { .r=1.0f, .g=1.0f, .b=1.0f, .a=1.0f } };
    int shapes[] = { RENDERER_SHAPE_QUAD };
    SparkVector2 sizes[] = { { .x = 100.0f, .y = 100.0f } };
    float borders[] = { 0.5f };

    SparkMaterial material_0 = sparkCreateMaterial("Color 2D", colorShader0);
    hashmap_set(material_0.data, &(SparkComponentData){ .key = "color", .data = &colors[0] });
    hashmap_set(material_0.data, &(SparkComponentData){ .key = "shape", .data = &shapes[0] });
    hashmap_set(renderer.materials, &material_0);

    SparkMaterial material_1 = sparkCreateMaterial("Texture 2D", textureShader0);
    hashmap_set(material_1.data, &(SparkComponentData){ .key = "texture", .data = &texture_0 });
    hashmap_set(material_1.data, &(SparkComponentData){ .key = "shape", .data = &shapes[0] });
    hashmap_set(renderer.materials, &material_1);

    SparkMaterial material_2 = sparkCreateMaterial("Color 3D", colorShader1);
    hashmap_set(material_2.data, &(SparkComponentData){ .key = "color", .data = &colors[0] });
    hashmap_set(material_2.data, &(SparkComponentData){ .key = "shape", .data = &shapes[0] });
    hashmap_set(renderer.materials, &material_2);

    SparkMaterial material_3 = sparkCreateMaterial("Texture 3D", textureShader1);
    hashmap_set(material_3.data, &(SparkComponentData){ .key = "texture", .data = &texture_0 });
    hashmap_set(material_3.data, &(SparkComponentData){ .key = "shape", .data = &shapes[0] });
    hashmap_set(renderer.materials, &material_3);

    clock_t end_3 = clock();
    double elapsed_3 = (double)(end_3 - begin_3) / CLOCKS_PER_SEC;
    printf("Created materials (%i materials in %.3fs)!\n", hashmap_count(renderer.materials), elapsed_3);
    printf("Creating scene...\n");
    clock_t begin_4 = clock();

    /* Create Scene */
    SparkScene scene = sparkCreateScene("Default");

    SparkGameObject gameObject_0 = sparkCreateGameObject();
    SparkComponent* component_0 = sparkCreateComponent(&gameObject_0, COMPONENT_TYPE_2D_RENDERER);
    gameObject_0.pos.y = 0.0f;
    hashmap_set(component_0->data, &(SparkComponentData){ .key = "size", .data = &sizes[0] });
    hashmap_set(component_0->data, &(SparkComponentData){ .key = "border", .data = &borders[0] });
    hashmap_set(component_0->data, &(SparkComponentData){ .key = "material", .data = &material_0 });
    vector_add(&scene.gameObjects, gameObject_0);

    /*SparkGameObject gameObject_1 = sparkCreateGameObject();
    SparkComponent* component_1 = sparkCreateComponent(&gameObject_1, COMPONENT_TYPE_2D_RENDERER);
    gameObject_1.pos.y = 100.0f;
    hashmap_set(component_1->data, &(SparkComponentData){ .key = "size", .data = &sizes[0] });
    hashmap_set(component_1->data, &(SparkComponentData){ .key = "material", .data = &material_0 });
    vector_add(&scene.gameObjects, gameObject_1);

    SparkGameObject gameObject_2 = sparkCreateGameObject();
    SparkComponent* component_2 = sparkCreateComponent(&gameObject_2, COMPONENT_TYPE_2D_RENDERER);
    gameObject_2.pos.y = 200.0f;
    hashmap_set(component_2->data, &(SparkComponentData){ .key = "size", .data = &sizes[0] });
    hashmap_set(component_2->data, &(SparkComponentData){ .key = "material", .data = &material_0 });
    vector_add(&scene.gameObjects, gameObject_2);

    SparkGameObject gameObject_t = sparkCreateGameObject();
    SparkComponent* component_t = sparkCreateComponent(&gameObject_t, COMPONENT_TYPE_2D_TEXTURE_RENDERER);
    gameObject_t.pos.x = 100.0f;
    hashmap_set(component_t->data, &(SparkComponentData){ .key = "size", .data = &sizes[0] });
    hashmap_set(component_t->data, &(SparkComponentData){ .key = "material", .data = &material_1 });
    vector_add(&scene.gameObjects, gameObject_t);*/

    sparkLoadScene(&renderer, &scene);

    clock_t end_4 = clock();
    double elapsed_4 = (double)(end_4 - begin_4) / CLOCKS_PER_SEC;
    printf("Created scene (%i GameObjects in %.3fs)!\n", vector_size(scene.gameObjects), elapsed_4);
    printf("Rendering...\n");

    /* Render owo */
    sparkRender(&renderer);

    printf("Exiting...\n");
}