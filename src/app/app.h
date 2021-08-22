#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED

struct SparkApp {
    SparkRenderer renderer;
    char* executablePath;
    char* assetsPath;
};
typedef struct SparkApp SparkApp;

void sparkSetupApp(SparkApp* app);
void sparkSetupAppRenderer(SparkApp* app);
void sparkCompileDefaultShaders(SparkApp* app);
void sparkLoadDefaultFonts(SparkApp* app);
void sparkLoadDefaultTextures(SparkApp* app);
void sparkCreateDefaultMaterials(SparkApp* app);

#endif