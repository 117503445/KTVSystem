#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include "song.h"
#include "lst_song.h"

#define debug

typedef wint_t *string;

typedef struct
{
	string s[100];
	int length;
} lst_string;

lst_song *list_song;

char *songs_path = "songs.scv";

void create_test_data();

void lst_song_save()
{
	FILE *fp = fopen(songs_path, "w+");
	int i;
	for (i = 0; i < list_song->length; i++)
	{
		song *s = lst_song_index_at(list_song, i);
		fprintf(fp, "%s;%s;%s", s->name, s->singer, s->path);
		if (i != list_song->length - 1)
		{
			fprintf(fp, "\n");
		}
	}
	fclose(fp);
}
void lst_song_load()
{
	const int max_line_char_num = 1024;
	FILE *fp = fopen(songs_path, "r");
	if (fp == NULL)
	{
		printf("Sorry, open songs.scv failed. Try to create test data. \n");
		create_test_data();
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
			strcpy(name, t);
			t = strtok(NULL, ";");
			strcpy(singer, t);
			t = strtok(NULL, ";");
			strcpy(path, t);

			if (path[strlen(path) - 1] == '\n')
			{
				path[strlen(path) - 1] = 0;
			}

			song *song = song_create_with_parameter(name, singer, path);
			lst_song_append(list_song, song);
		}
		fclose(fp);
	}
}
void songs_print(int is_show_index)
{
	printf("\nnum_songs is %d\n", list_song->length);
	int i;
	for (i = 0; i < list_song->length; i++)
	{
		if (is_show_index)
		{
			printf("%d ", i);
		}
		song *s = lst_song_index_at(list_song, i);
		printf("%s;%s;%s\n", s->name, s->singer, s->path);
	}
	puts("");
}

void read_string(char *path)
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

void show_lrc(song *s)
{
	printf("\n---%s---\n---%s---\n---%s---\n\n", s->name, s->singer, s->path);
	read_string(s->path);
	printf("\n");
}
void search()
{
	printf("Please input singer or song's name\n");
	char s[100] = {0};

	gets(s);

	int i;

	int result_num = 0;
	int dict_index[100] = {0};

	for (i = 0; i < list_song->length; i++)
	{
		song *song = lst_song_index_at(list_song, i);
		if (strstr(song->singer, s) != NULL || strstr(song->name, s) != NULL)
		{
			dict_index[result_num] = i;
			printf("%d %s *** %s *** %s\n", result_num, song->name, song->singer, song->path);
			result_num++;
		}
	}
	printf("\n");
	if (result_num == 0)
	{
		printf("get nothing :(\n");
	}
	else if (result_num == 1)
	{
		song *so = lst_song_index_at(list_song, dict_index[0]);
		show_lrc(so);
	}
	else
	{
		printf("Please input index\n");
		int d;
		while (1)
		{
			scanf("%d", &d);
			if (d < 0 || d >= result_num)
			{
				printf("invalid input\n");
			}
			else
			{
				break;
			}
		}
		song *so = lst_song_index_at(list_song, dict_index[d]);
		show_lrc(so);
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
		lst_song_save();
		puts("remove_song successful");
	}
}
void create_test_data()
{
	lst_song_append(list_song, song_create_with_parameter((char *)"浮夸", (char *)"陈奕迅", (char *)"fu_kua.lrc"));
	lst_song_append(list_song, song_create_with_parameter((char *)"Can't stand the rain", (char *)"The Rescues", (char *)"Can't stand the rain.lrc"));
	lst_song_append(list_song, song_create_with_parameter((char *)"十年", (char *)"陈奕迅", (char *)"shi_nian.lrc"));

	lst_song_save();
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
	lst_song_save();

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
void main_loop(int is_admin)
{
	char c;
	while (1)
	{
		puts("Press Q To quit\nPress S to search\nPress D To display all songs");
		if (is_admin)
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
			if (!is_admin)
			{
				puts("You don't have permission");
			}
			add_song();
			break;
		case 'r':
			getchar();
			if (!is_admin)
			{
				puts("You don't have permission");
			}
			remove_song();
			break;
		case 'c':
			getchar();
			if (!is_admin)
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
int test_show_lrc_0()
{
	song *s = song_create_with_parameter((char *)"浮夸", (char *)"陈奕迅", (char *)"fu_kua.lrc");
	show_lrc(s);
	return 0;
}
int test_show_lrc_1()
{
	song *s = song_create_with_parameter((char *)"浮夸", (char *)"陈奕迅", (char *)"浮夸.lrc");
	show_lrc(s);
	return 0;
}
int test_read_string_0()
{
	read_string((wint_t *)"浮夸.lrc");
}
void func_debug()
{
	test_read_string_0();
}
int main()
{
#ifdef debug
	func_debug();
	printf("debug finished");
	return 0;
#endif

	list_song = lst_song_create_empty();
	lst_song_load();
	int is_admin = 0;
	puts("Are you Admin?\nUser: please press 0\nAdmin: please press 1");
	while (1)
	{
		scanf("%d", &is_admin);
		getchar();
		if (is_admin != 0 && is_admin != 1)
		{
			puts("invalid input");
		}
		else
		{
			break;
		}
	}
	main_loop(is_admin);
	return 0;
}