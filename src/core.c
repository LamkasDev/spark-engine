#include "macros/language.h"
#include "io/io.h"

#include "utils/color.h"
#include "utils/vector_2.h"
#include "utils/texture.h"
#include "utils/scene.h"

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
    printf("Creating Scene...\n");
    clock_t begin_3 = clock();

    /* Create Scene */
    SparkScene scene = sparkCreateScene("Default");

    SparkVector2 sizes[] = { { .x = 100.0f, .y = 100.0f } };
    SparkColor colors[] = { { .r=1.0f, .g=0.0f, .b=0.0f, .a=1.0f }, { .r=0.0f, .g=1.0f, .b=0.0f, .a=1.0f }, { .r=0.0f, .g=0.0f, .b=1.0f, .a=1.0f } };
    int shapes[] = { RENDERER_SHAPE_QUAD, RENDERER_SHAPE_CIRCLE, RENDERER_SHAPE_EMPTY_CIRCLE, RENDERER_SHAPE_EMPTY_QUAD };

    SparkGameObject gameObject_0 = sparkCreateGameObject();
    SparkComponent* component_0 = sparkCreateComponent(&gameObject_0, COMPONENT_TYPE_2D_RENDERER);
    gameObject_0.pos.y = 0.0f;
    hashmap_set(component_0->data, &(SparkComponentData){ .key = "shape", .data = &shapes[0] });
    hashmap_set(component_0->data, &(SparkComponentData){ .key = "size", .data = &sizes[0] });
    hashmap_set(component_0->data, &(SparkComponentData){ .key = "color", .data = &colors[0] });
    vector_add(&scene.gameObjects, gameObject_0);

    SparkGameObject gameObject_1 = sparkCreateGameObject();
    SparkComponent* component_1 = sparkCreateComponent(&gameObject_1, COMPONENT_TYPE_2D_RENDERER);
    gameObject_1.pos.y = 100.0f;
    hashmap_set(component_1->data, &(SparkComponentData){ .key = "shape", .data = &shapes[0] });
    hashmap_set(component_1->data, &(SparkComponentData){ .key = "size", .data = &sizes[0] });
    hashmap_set(component_1->data, &(SparkComponentData){ .key = "color", .data = &colors[1] });
    vector_add(&scene.gameObjects, gameObject_1);

    SparkGameObject gameObject_2 = sparkCreateGameObject();
    SparkComponent* component_2 = sparkCreateComponent(&gameObject_2, COMPONENT_TYPE_2D_RENDERER);
    gameObject_2.pos.y = 200.0f;
    hashmap_set(component_2->data, &(SparkComponentData){ .key = "shape", .data = &shapes[0] });
    hashmap_set(component_2->data, &(SparkComponentData){ .key = "size", .data = &sizes[0] });
    hashmap_set(component_2->data, &(SparkComponentData){ .key = "color", .data = &colors[2] });
    vector_add(&scene.gameObjects, gameObject_2);

    SparkGameObject gameObject_3 = sparkCreateGameObject();
    SparkComponent* component_3 = sparkCreateComponent(&gameObject_3, COMPONENT_TYPE_2D_TEXTURE_RENDERER);
    gameObject_3.pos.y = 300.0f;
    hashmap_set(component_3->data, &(SparkComponentData){ .key = "shape", .data = &shapes[0] });
    hashmap_set(component_3->data, &(SparkComponentData){ .key = "size", .data = &sizes[0] });
    hashmap_set(component_3->data, &(SparkComponentData){ .key = "texture", .data = &texture_0 });
    vector_add(&scene.gameObjects, gameObject_3);

    SparkGameObject gameObject_4 = sparkCreateGameObject();
    SparkComponent* component_4 = sparkCreateComponent(&gameObject_4, COMPONENT_TYPE_2D_RENDERER);
    gameObject_4.pos.x = 100.0f;
    hashmap_set(component_4->data, &(SparkComponentData){ .key = "shape", .data = &shapes[1] });
    hashmap_set(component_4->data, &(SparkComponentData){ .key = "size", .data = &sizes[0] });
    hashmap_set(component_4->data, &(SparkComponentData){ .key = "color", .data = &colors[0] });
    vector_add(&scene.gameObjects, gameObject_4);

    SparkGameObject gameObject_5 = sparkCreateGameObject();
    SparkComponent* component_5 = sparkCreateComponent(&gameObject_5, COMPONENT_TYPE_2D_RENDERER);
    gameObject_5.pos.x = 200.0f;
    hashmap_set(component_5->data, &(SparkComponentData){ .key = "shape", .data = &shapes[2] });
    hashmap_set(component_5->data, &(SparkComponentData){ .key = "size", .data = &sizes[0] });
    hashmap_set(component_5->data, &(SparkComponentData){ .key = "color", .data = &colors[0] });
    vector_add(&scene.gameObjects, gameObject_5);

    SparkGameObject gameObject_6 = sparkCreateGameObject();
    SparkComponent* component_6 = sparkCreateComponent(&gameObject_6, COMPONENT_TYPE_2D_RENDERER);
    gameObject_6.pos.x = 100.0f;
    gameObject_6.pos.y = 100.0f;
    hashmap_set(component_6->data, &(SparkComponentData){ .key = "shape", .data = &shapes[0] });
    hashmap_set(component_6->data, &(SparkComponentData){ .key = "size", .data = &sizes[0] });
    hashmap_set(component_6->data, &(SparkComponentData){ .key = "color", .data = &colors[1] });
    vector_add(&scene.gameObjects, gameObject_6);

    SparkGameObject gameObject_7 = sparkCreateGameObject();
    SparkComponent* component_7 = sparkCreateComponent(&gameObject_7, COMPONENT_TYPE_3D_RENDERER);
    gameObject_7.pos.x = 100.0f;
    gameObject_7.pos.y = 100.0f;
    hashmap_set(component_7->data, &(SparkComponentData){ .key = "shape", .data = &shapes[3] });
    hashmap_set(component_7->data, &(SparkComponentData){ .key = "size", .data = &sizes[0] });
    hashmap_set(component_7->data, &(SparkComponentData){ .key = "color", .data = &colors[0] });
    vector_add(&scene.gameObjects, gameObject_7);

    SparkGameObject gameObject_8 = sparkCreateGameObject();
    SparkComponent* component_8 = sparkCreateComponent(&gameObject_8, COMPONENT_TYPE_2D_RENDERER);
    gameObject_8.pos.x = 200.0f;
    gameObject_8.pos.y = 100.0f;
    hashmap_set(component_8->data, &(SparkComponentData){ .key = "shape", .data = &shapes[3] });
    hashmap_set(component_8->data, &(SparkComponentData){ .key = "size", .data = &sizes[0] });
    hashmap_set(component_8->data, &(SparkComponentData){ .key = "color", .data = &colors[0] });
    vector_add(&scene.gameObjects, gameObject_8);

    sparkLoadScene(&renderer, &scene);

    clock_t end_3 = clock();
    double elapsed_3 = (double)(end_3 - begin_3) / CLOCKS_PER_SEC;
    printf("Created Scene (%i GameObjects in %.3fs)!\n", vector_size(scene.gameObjects), elapsed_3);
    printf("Rendering...\n");

    /* Render owo */
    sparkRender(&renderer);

    printf("Exiting...\n");
}