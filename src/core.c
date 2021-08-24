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

#include "app/app.h"
#include "editor/editor.h"

/**
 * Main engine loop.
 */
void run() {
    printf("=========\n");
    printf("Started Spark Engine (%s)...\n", SPARK_VERSION);
    printf("=========\n");
    SparkApp app;

    printf("Setting up app...\n");
    clock_t begin_0 = clock();
    sparkSetupApp(&app);
    sparkSetupAppRenderer(&app);
    clock_t end_0 = clock();
    double elapsed_0 = (double)(end_0 - begin_0) / CLOCKS_PER_SEC;
    printf("Initialized (%.3fs)!\n", elapsed_0);

    printf("Compiling shaders...\n");
    clock_t begin_1 = clock();
    sparkCompileDefaultShaders(&app);
    sparkCompileEditorShaders(&app);
    clock_t end_1 = clock();
    double elapsed_1 = (double)(end_1 - begin_1) / CLOCKS_PER_SEC;
    printf("Compiled shaders (%i shaders in %.3fs)!\n", hashmap_count(app.renderer.shaders), elapsed_1);

    printf("Loading fonts...\n");
    clock_t begin_2 = clock();
    sparkLoadDefaultFonts(&app);
    sparkLoadEditorFonts(&app);
    clock_t end_2 = clock();
    double elapsed_2 = (double)(end_2 - begin_2) / CLOCKS_PER_SEC;
    printf("Loaded fonts (%i fonts in %.3fs)!\n", hashmap_count(app.renderer.fonts), elapsed_1);

    printf("Loading textures...\n");
    clock_t begin_5 = clock();
    sparkLoadDefaultTextures(&app);
    sparkLoadEditorTextures(&app);
    clock_t end_5 = clock();
    double elapsed_5 = (double)(end_5 - begin_5) / CLOCKS_PER_SEC;
    printf("Loaded textures (%i textures in %.3fs)!\n", hashmap_count(app.renderer.textures), elapsed_5);

    printf("Creating materials...\n");
    clock_t begin_3 = clock();
    sparkCreateDefaultMaterials(&app);
    sparkCreateEditorMaterials(&app);
    clock_t end_3 = clock();
    double elapsed_3 = (double)(end_3 - begin_3) / CLOCKS_PER_SEC;
    printf("Created materials (%i materials in %.3fs)!\n", hashmap_count(app.renderer.materials), elapsed_3);

    printf("Creating scene...\n");
    clock_t begin_4 = clock();
    SparkScene scene = sparkCreateEditorScene(&app);
    sparkLoadScene(&app.renderer, &scene);
    clock_t end_4 = clock();
    double elapsed_4 = (double)(end_4 - begin_4) / CLOCKS_PER_SEC;
    printf("Created scene (%i GameObjects in %.3fs)!\n", vector_size(scene.gameObjects), elapsed_4);
    printf("=========\n");

    printf("Rendering...\n");
    sparkRender(&app.renderer);
    printf("Exiting...\n");
}