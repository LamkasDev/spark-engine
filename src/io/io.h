#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

unsigned char* sparkReadFile(char path[255], bool terminate, int* size);
char* sparkGetExecutablePath();
char* sparkCombinePaths(char* path1, char* path2);
char* sparkCreatePathFromString(char* path);

#endif