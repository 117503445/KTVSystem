#include "lst_song.h"
void lst_song_print(lst_song *lst_song)
{
    int i;
    for (i = 0; i < lst_song->length; i++)
    {
        song_print(lst_song->songs[i]);
    }
}