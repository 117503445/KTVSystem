#include "song.h"
#include <stdio.h>
#include <stdlib.h>
void song_print(song *s)
{
    printf("%s %s %s\n", s->name, s->singer, s->path);
}
song *song_create_with_parameter(char *song_name, char *singer_name, char* file_path)
{
    song *s = (song *)malloc(sizeof(song));
    strcpy(s->name, song_name);
    strcpy(s->singer, singer_name);
    strcpy(s->path, file_path);
    int i;
    for (i = 0; i < strlen(file_path); i++)
    {
        printf("%d ", file_path[i]);
    }
    printf("1148");
    return s;
}