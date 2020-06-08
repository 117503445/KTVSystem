#include "song.h"
#include <stdio.h>
#include <stdlib.h>
void song_print(song *s)
{
    printf("%s %s %s\n", s->name, s->singer, s->path);
}
song *song_create_with_parameter(wchar_t *song_name, wchar_t *singer_name, wchar_t* file_path)
{
    song *s = (song *)malloc(sizeof(song));
    wcscpy(s->name, song_name);
    wcscpy(s->singer, singer_name);
    wcscpy(s->path, file_path);
    return s;
}