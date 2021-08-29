#include "utils/string.h"
#include "utils/math.h"

#include "macros/language.h"
#include "io/io.h"

#include "structs/vector_2.h"
#include "structs/vector_3.h"

#include "structs/color.h"
#include "structs/texture.h"
#include "structs/character.h"
#include "structs/font.h"
#include "structs/material.h"
#include "utils/hashmap_utils.h"
#include "utils/print.h"

#include "components/component_data.h"
#include "components/component.h"
#include "gameobjects/gameobject.h"
#include "structs/scene.h"

#include "store/store.h"
#include "utils/store_utils.h"
#include "renderer/renderer.h"

#include "utils/json_utils.h"
#include "app/app.h"
#include "editor/editor.h"

/**
 * Entrypoint of the engine.
 */
void run() {
    SparkApp app;

    printf("=========\n");
    printf("Started Spark Engine (%s)...\n", SPARK_VERSION);
    printf("=========\n");
    sparkSetupApp(&app);
    sparkSetupAppRenderer(&app);
    reloadEngine(&app, true);
    printf("=========\n");

    printf("Rendering...\n");
    runEngine(&app);
    printf("Exiting...\n");
}

/**
 * Reload the engine.
 * 
 * @param app a pointer to an app
 * @param debug true to print debug information
 * 
 */
void reloadEngine(void* _app, bool debug) {
    SparkApp* app = (SparkApp*)_app;

    if(debug) { printf("Compiling shaders... "); }
    clock_t begin_1 = clock();
    sparkCreateDefaultShaders(app);
    sparkCreateEditorShaders(app);
    clock_t end_1 = clock();
    double elapsed_1 = (double)(end_1 - begin_1) / CLOCKS_PER_SEC;
    if(debug) { printf("(%i shaders in %.3fs)\n", hashmap_count(app->renderer.shaders), elapsed_1); }

    if(debug) { printf("Loading fonts... "); }
    clock_t begin_2 = clock();
    sparkCreateDefaultFonts(app);
    sparkCreateEditorFonts(app);
    clock_t end_2 = clock();
    double elapsed_2 = (double)(end_2 - begin_2) / CLOCKS_PER_SEC;
    if(debug) { printf("(%i fonts in %.3fs)\n", hashmap_count(app->renderer.fonts), elapsed_1); }

    if(debug) { printf("Loading textures... "); }
    clock_t begin_5 = clock();
    sparkCreateDefaultTextures(app);
    sparkCreateEditorTextures(app);
    clock_t end_5 = clock();
    double elapsed_5 = (double)(end_5 - begin_5) / CLOCKS_PER_SEC;
    if(debug) { printf("(%i textures in %.3fs)\n", hashmap_count(app->renderer.textures), elapsed_5); }

    if(debug) { printf("Creating materials... "); }
    clock_t begin_3 = clock();
    sparkCreateDefaultMaterials(app);
    sparkCreateEditorMaterials(app);
    clock_t end_3 = clock();
    double elapsed_3 = (double)(end_3 - begin_3) / CLOCKS_PER_SEC;
    if(debug) { printf("(%i materials in %.3fs)\n", hashmap_count(app->renderer.materials), elapsed_3); }

    if(debug) { printf("Creating scene... "); }
    clock_t begin_4 = clock();
    SparkScene scene = sparkCreateEditorScene(app);
    sparkLoadScene(&app->renderer, &scene);
    clock_t end_4 = clock();
    double elapsed_4 = (double)(end_4 - begin_4) / CLOCKS_PER_SEC;
    if(debug) { printf("(%i GameObjects in %.3fs)\n", vector_size(scene.gameObjects), elapsed_4); }
}

/**
 * Runs the game engine.
 * 
 * @param app a pointer to an app
 * 
 */
void runEngine(void* _app) {
    SparkApp* app = (SparkApp*)_app;

    float targetFPS = 60.00f;
    float targetDeltaTime = targetFPS < 0.0f ? 0.0f : 1.00f / targetFPS;
    clock_t clock_0 = clock();
    clock_t clock_1 = clock();

    while(!glfwWindowShouldClose(app->renderer.window)) {
        float deltaTime = ((clock() - clock_0) / 1000.0f);
        float deltaTime2 = ((clock() - clock_1) / 1000.0f);
        if(deltaTime > targetDeltaTime) {
            sparkRender(&app->renderer);
            clock_0 = clock();
        }
        if(deltaTime2 >= 1.0f && glfwGetKey(app->renderer.window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && glfwGetKey(app->renderer.window, GLFW_KEY_R) == GLFW_PRESS) {
            printf("Reloading... ");
            clock_t begin = clock();
            sparkDeleteRenderer(&app->renderer);
            sparkSetupRenderer(&app->renderer);
            reloadEngine(app, false);
            clock_t end = clock();
            double elapsed = (double)(end - begin) / CLOCKS_PER_SEC;
            printf("(took %.3fs)\n", elapsed);
            clock_1 = clock();
        }

        glfwPollEvents();
    }

    sparkDeleteRenderer(&app->renderer);
    glfwDestroyWindow(app->renderer.window);
    glfwTerminate();
}