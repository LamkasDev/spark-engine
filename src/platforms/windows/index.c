#include <stdio.h>
#include <time.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "../../core.h"

/* too lazy to put these in make */
#include "../../../libs/include/vector/vector.c"
#include "../../../libs/include/hashmap/hashmap.c"

#include "../../core.c"
#include "../../components/component.c"
#include "../../components/component_data.c"
#include "../../gameobjects/gameobject.c"
#include "../../io/io.c"
#include "../../renderer/renderer.c"
#include "../../renderer/glad/glad.c"
#include "../../renderer/shaders/shader.c"
#include "../../renderer/utils/renderer_object.c"
#include "../../utils/color.c"
#include "../../utils/hashmap_utils.c"
#include "../../utils/scene.c"
#include "../../utils/texture.c"
#include "../../utils/vector_2.c"
#include "../../utils/vector_3.c"
#include "../../utils/math.c"

int main() {
    run();
}