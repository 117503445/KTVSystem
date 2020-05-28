#ifndef LST_SONG_H
#define LST_SONG_H

#include "song.h"

typedef struct
{
    song *songs[100];
    int length;
} lst_song;

lst_song *lst_song_create_empty();
void lst_song_print(lst_song *songs);
song *lst_song_index_at(lst_song *songs,int index);
void lst_song_append(lst_song *songs,song* song);
#include "lst_song.c"
#endif