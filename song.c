#include "song.h"
void song_print(song *s)
{
    printf("%s %s %s\n", s->name, s->singer, s->path);
}