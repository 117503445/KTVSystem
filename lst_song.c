#include "lst_song.h"

lst_song *lst_song_create_empty()
{
    lst_song *s = (lst_song *)malloc(sizeof(lst_song));
    s->length = 0;
    return s;
}

void lst_song_print(lst_song *lst_song)
{
    int i;
    for (i = 0; i < lst_song->length; i++)
    {
        song_print(lst_song->songs[i]);
    }
}
song *lst_song_index_at(lst_song *lst_song, int index)
{
    if (index < 0)
    {
        printf("Index should >= 0");
        return NULL;
    }
    if (index >= lst_song->length)
    {
        printf("Index should < length");
        return NULL;
    }

    return lst_song->songs[index];
}

void lst_song_append(lst_song *songs, song *song)
{
    songs->songs[songs->length] = song;
    songs->length++;
}