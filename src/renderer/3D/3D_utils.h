#ifndef RENDERER_3D_UTILS_H_INCLUDED
#define RENDERER_3D_UTILS_H_INCLUDED

SparkRendererObject sparkCreateRendererObject3D(SparkRenderer* renderer, SparkGameObject* gameObject, SparkComponent* component);
void sparkUpdateRendererObject3D(SparkRenderer* renderer, SparkRendererObject* rendererObject);

#endif