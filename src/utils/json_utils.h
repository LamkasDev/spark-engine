#ifndef JSON_UTILS_H_INCLUDED
#define JSON_UTILS_H_INCLUDED

void sparkCreateShadersFromJSON(void* _app, const unsigned char* json);
void sparkCreateFontsFromJSON(void* _app, const unsigned char* json);
void sparkCreateTexturesFromJSON(void* _app, const unsigned char* json);
void sparkCreateMaterialsFromJSON(void* _app, const unsigned char* json);
void sparkLoadSceneFromJSON(void* _app, SparkScene* scene, const unsigned char* json);

SparkComponentData sparkCreateComponentDataFromJSON(void* _app, cJSON* data);
void* sparkCreateComponentDataValueFromJSON(void* _app, char* key, cJSON* data);

#endif