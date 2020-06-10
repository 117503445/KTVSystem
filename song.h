
#ifndef _SONG_H
#define _SONG_H
#include <string.h>
#include <wchar.h>
typedef struct
{
    wchar_t name[50];
    wchar_t singer[20];
    wchar_t path[100];
} song;

void song_print(song *s);
song *song_create_with_parameter(wchar_t *song_name, wchar_t *singer_name, wchar_t* file_path);
song *song_create_new();
#include "song.c"
#endif