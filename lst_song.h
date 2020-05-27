#ifndef LST_SONG_H
#define LST_SONG_H

#include "song.h"

typedef struct
{
    song* s[100];
    int length;
} lst_song;
#endif