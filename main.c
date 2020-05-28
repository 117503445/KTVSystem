#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include "song.h"
#include "lst_song.h"
typedef wint_t *string;

typedef struct
{
	string s[100];
	int length;
} lst_string;

// song songs[100];
// int num_songs = 0;

lst_song *list_song;

char *songs_path = "songs.scv";

void save_songs()
{
	FILE *fp = fopen(songs_path, "w+");
	int i;
	for (i = 0; i < list_song->length; i++)
	{
		song *s = list_song->songs[i];
		fprintf(fp, "%s;%s;%s", s->name, s->singer, s->path);
		if (i != list_song->length - 1)
		{
			fprintf(fp, "\n");
		}
	}
	fclose(fp);
}
void load_songs()
{
	const int max_line_char_num = 1024;
	FILE *fp = fopen(songs_path, "r");
	if (fp == NULL)
	{
		printf("Sorry, open songs.scv failed.\n");
		return;
	}
	else
	{
		char str[1024] = {0};
		char *t = (char *)malloc(sizeof(char) * 100);
		while (!feof(fp))
		{
			fgets(str, max_line_char_num, fp);
			char *name = (char *)malloc(sizeof(char) * 100);
			char *singer = (char *)malloc(sizeof(char) * 100);
			char *path = (char *)malloc(sizeof(char) * 100);
			t = strtok(str, ";");

			//song *s = list_song->

			strcpy(name, t);
			//printf("%s\n", t);
			t = strtok(NULL, ";");
			strcpy(singer, t);
			//printf("%s\n", t);
			t = strtok(NULL, ";");
			//printf("%s\n", t);
			strcpy(path, t);
			// int i;
			// for (i = 0; i < strlen(path); i++)
			// {
			// 	printf("%d ", path[i]);
			// }

			if (path[strlen(path) - 1] == '\n')
			{
				path[strlen(path) - 1] = 0;
			}
			// for (i = 0; i < strlen(path); i++)
			// {
			// 	printf("%d ", path[i]);
			// }
			song *song = song_create_with_parameter(name, singer, path);
			printf("1146");
			lst_song_append(list_song, song);

			// if (songs[num_songs].path[strlen(songs[num_songs].path) - 1] == '\n')
			// {
			// 	songs[num_songs].path[strlen(songs[num_songs].path) - 1] = 0;
			// }
			// num_songs++;
		}
		fclose(fp);
	}
}
void songs_print(int isShowIndex)
{
	printf("\nnum_songs is %d\n", list_song->length);
	int i;
	for (i = 0; i < list_song->length; i++)
	{
		if (isShowIndex)
		{
			printf("%d ", i);
		}
		song *s = lst_song_index_at(list_song, i);
		printf("%s;%s;%s\n", s->name, s->singer, s->path);
	}
	puts("");
}

void read_string(string path)
{
	const int max_line_char_num = 1024;
	FILE *fp = fopen(path, "r");
	if (fp == NULL)
	{
		printf("Open %s failed.\n", path);
		return;
	}
	else
	{
		while (!feof(fp))
		{
			char str[1024] = {0};
			fgets(str, max_line_char_num, fp);
			printf("%s", str);
		}
		fclose(fp);
	}
	printf("\n");
}

void show_lrc(song s)
{
	printf("\n---%s---\n---%s---\n---%s---\n\n", s.name, s.singer, s.path);
	read_string(s.path);
	printf("\n");
}
void search()
{
	printf("Please input singer or song's name\n");
	char s[100] = {0};
	gets(s);
	int i;

	int resultNum = 0;
	int indexs[100] = {0};

	for (i = 0; i < list_song->length; i++)
	{
		song *song = lst_song_index_at(list_song, i);
		if (strstr(song->singer, s) != NULL || strstr(song->name, s) != NULL)
		{
			indexs[resultNum] = i;
			printf("%d %s *** %s *** %s\n", resultNum, song->name, song->singer, song->path);
			resultNum++;
		}
	}
	printf("\n");
	if (resultNum == 0)
	{
		printf("get nothing :(\n");
	}
	else if (resultNum == 1)
	{
		song *so = lst_song_index_at(list_song, indexs[0]);
		show_lrc(*so);
	}
	else
	{
		printf("Please input index\n");
		int d;
		while (1)
		{
			scanf("%d", &d);
			if (d < 0 || d >= resultNum)
			{
				printf("invalid input\n");
			}
			else
			{
				break;
			}
		}
		song *so = lst_song_index_at(list_song, indexs[d]);
		show_lrc(*so);
		getchar();
	}
}
void remove_song()
{
	songs_print(1);
	puts("Please input the index");
	int index;
	scanf("%d", &index);
	getchar();
	if (index < 0 || index >= list_song->length)
	{
		puts("invalid input");
	}
	else
	{
		int i;
		for (i = index; i < list_song->length - 1; i++)
		{
			list_song->songs[i] = list_song->songs[i + 1];
		}
		list_song->length--;
		save_songs();
		puts("remove_song successful");
	}
}
void create_test_data()
{
	// song s1 = {"浮夸", "陈奕迅", "fu_kua.lrc"};
	// song s2 = {"Can't stand the rain", "The Rescues", "Can't stand the rain.lrc"};
	// song s3 = {"十年", "陈奕迅", "shi_nian.lrc"};
	lst_song_append(list_song, song_create_with_parameter((char *)"浮夸", (char *)"陈奕迅", (char *)"fu_kua.lrc"));

	save_songs();
}
void add_song()
{
	song s = {0};
	puts("please input the song name");
	gets(s.name);
	puts("please input the singer name");
	gets(s.singer);
	puts("please input the file path, example: fu_kua.lrc, and you could only input english");
	gets(s.path);
	//songs[num_songs] = s;
	//num_songs++;
	lst_song_append(list_song, &s);
	save_songs();

	puts("please input words, enter blank line to stop input\n");

	FILE *fp = fopen(s.path, "w+");
	while (1)
	{
		char buf[1024] = {0};
		gets(buf);
		if (strlen(buf) == 0)
		{
			break;
		}
		buf[strlen(buf)] = '\n';
		fputs(buf, fp);
	}
	fclose(fp);

	puts("add successful");
}
void main_loop(int isAdmin)
{
	char c;
	while (1)
	{
		puts("Press Q To quit\nPress S to search\nPress D To display all songs");
		if (isAdmin)
		{
			puts("Press A To add song\nPress R To romove songs\nPress C To create default data");
		}
		c = getchar();
		if (c >= 'A' && c <= 'Z')
		{
			c += 'a' - 'A';
		}
		switch (c)
		{
		case 'q':
			printf("Bye");
			return;
			break;
		case 's':
			getchar();
			search();
			break;
		case 'd':
			getchar();
			songs_print(0);
			break;
		case 'a':
			getchar();
			if (!isAdmin)
			{
				puts("You don't have permission");
			}
			add_song();
			break;
		case 'r':
			getchar();
			if (!isAdmin)
			{
				puts("You don't have permission");
			}
			remove_song();
			break;
		case 'c':
			getchar();
			if (!isAdmin)
			{
				puts("You don't have permission");
			}
			create_test_data();
			break;
		default:
			printf("invalid input\n");
			break;
		}
	}
}

int main()
{

	list_song = lst_song_create_empty();
	load_songs();
	int isAdmin = 0;
	puts("Are you Admin?\nUser: please press 0\nAdmin: please press 1");
	while (1)
	{
		scanf("%d", &isAdmin);
		getchar();
		if (isAdmin != 0 && isAdmin != 1)
		{
			puts("invalid input");
		}
		else
		{
			break;
		}
	}
	main_loop(isAdmin);
	return 0;
}