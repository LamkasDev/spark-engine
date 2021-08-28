#ifndef JSON_UTILS_H_INCLUDED
#define JSON_UTILS_H_INCLUDED

void sparkLoadSceneFromJSON(SparkRenderer* renderer, SparkScene* scene, const unsigned char* json);
SparkComponentData sparkCreateComponentDataFromJSON(SparkRenderer* renderer, cJSON* data);

#endif