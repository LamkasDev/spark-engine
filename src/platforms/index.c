#include "../core.h"

/* too lazy to put these in make */
#include "../../libs/include/vector/vector.c"
#include "../../libs/include/hashmap/hashmap.c"

#include "../core.c"
#include "../app/app.c"
#include "../components/component.c"
#include "../components/component_data.c"
#include "../editor/editor.c"
#include "../gameobjects/gameobject.c"
#include "../io/io.c"
#include "../renderer/renderer.c"
#include "../renderer/2D/2D_utils.c"
#include "../renderer/2D/text_utils.c"
#include "../renderer/3D/3D_utils.c"
#include "../renderer/glad/glad.c"
#include "../renderer/shaders/shader.c"
#include "../renderer/utils/renderer_object_group.c"
#include "../renderer/utils/renderer_object.c"
#include "../structs/color.c"
#include "../structs/font.c"
#include "../structs/material.c"
#include "../structs/scene.c"
#include "../structs/texture.c"
#include "../structs/vector_2.c"
#include "../structs/vector_3.c"
#include "../utils/hashmap_utils.c"
#include "../utils/math.c"
#include "../utils/print.c"
#include "../utils/string.c"

int main() {
    run();
}