#ifndef EDITOR_H_INCLUDED
#define EDITOR_H_INCLUDED

void sparkCompileEditorShaders(SparkApp* app);
void sparkLoadEditorFonts(SparkApp* app);
void sparkLoadEditorTextures(SparkApp* app);
void sparkCreateEditorMaterials(SparkApp* app);
SparkScene sparkCreateEditorScene(SparkApp* app);

#endif