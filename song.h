
#ifndef _SONG_H
#define _SONG_H

typedef struct
{
    char name[50];
    char singer[20];
    char path[100];
} song;

void song_print(song *s);
#include "song.c"
#endif