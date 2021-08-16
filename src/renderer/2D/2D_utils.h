#ifndef RENDERER_2D_UTILS_H_INCLUDED
#define RENDERER_2D_UTILS_H_INCLUDED

SparkRendererObject sparkCreateRendererObject2D(SparkRenderer* renderer, SparkGameObject* gameObject, SparkComponent* component);
void sparkUpdateRendererObject2D(SparkRenderer* renderer, SparkRendererObject* rendererObject);

#endif