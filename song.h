
#ifndef _SONG_H
#define _SONG_H
#include <string.h>
typedef struct
{
    char name[50];
    char singer[20];
    char path[100];
} song;

void song_print(song *s);
song *song_create_with_parameter(char *song_name, char *singer_name, char* file_path);
#include "song.c"
#endif