#ifndef LST_SONG_H
#define LST_SONG_H

#include "song.h"

typedef struct
{
    song *songs[100];
    int length;
} lst_song;

void lst_song_print(lst_song *songs);

#include "lst_song.c"
#endif