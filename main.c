#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
typedef wint_t *string;
typedef struct
{
	string s[100];
	int length;
} lst_string;

typedef struct
{
	char name[50];
	char singer[20];
	char path[100];
} song;

song songs[100];
int num_songs = 0;

char *file_songs = "songs.scv";

void save_songs()
{
	FILE *fp = fopen(file_songs, "w+");
	int i;
	for (i = 0; i < num_songs; i++)
	{
		fprintf(fp, "%s;%s;%s", songs[i].name, songs[i].cook, songs[i].path);
		if (i != num_songs - 1)
		{
			fprintf(fp, "\n");
		}
	}
	fclose(fp);
}
void load_songs()
{
	const int max_line_char_num = 1024;
	FILE *fp = fopen(file_songs, "r");
	if (fp == NULL)
	{
		printf("Sorry, open songs.scv failed.\n");
		return
	}
	else
	{
		char str[1024] = {0};
		char *t;
		while (!feof(fp))
		{
			fgets(str, max_line_char_num, fp);
			t = strtok(str, ";");
			strcpy(songs[num_songs].name, t);
			//printf("%s\n", t);
			t = strtok(NULL, ";");
			strcpy(songs[num_songs].cook, t);
			//printf("%s\n", t);
			t = strtok(NULL, ";");
			//printf("%s\n", t);
			strcpy(songs[num_songs].path, t);
			if (songs[num_songs].path[strlen(songs[num_songs].path) - 1] == '\n')
			{
				songs[num_songs].path[strlen(songs[num_songs].path) - 1] = 0;
			}
			num_songs++;
		}
		fclose(fp);
	}
}
void show_songs(int isShowIndex)
{
	printf("\nnum_songs is %d\n", num_songs);
	int i;
	for (i = 0; i < num_songs; i++)
	{
		if (isShowIndex)
		{
			printf("%d ", i);
		}
		printf("%s;%s;%s\n", songs[i].name, songs[i].cook, songs[i].path);
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
	printf("\n---%s---\n---%s---\n---%s---\n\n", s.name, s.cook, s.path);
	read_string(s.path);
	printf("\n");
}
void search()
{
	printf("Please input cook or song's name\n");
	char s[100] = {0};
	gets(s);
	int i;

	int resultNum = 0;
	int indexs[100] = {0};

	for (i = 0; i < num_songs; i++)
	{
		if (strstr(songs[i].cook, s) != NULL || strstr(songs[i].name, s) != NULL)
		{
			indexs[resultNum] = i;
			printf("%d %s *** %s *** %s\n", resultNum, songs[i].name, songs[i].cook, songs[i].path);
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
		show_lrc(songs[indexs[0]]);
	}
	else
	{
		printf("Please input index\n");
		int d;
		while (1)
		{
			(void)scanf("%d", &d);
			if (d < 0 || d >= resultNum)
			{
				printf("invalid input\n");
			}
			else
			{
				break;
			}
		}
		show_lrc(songs[indexs[d]]);
		(void)getchar();
	}
}
void remove_song()
{
	show_songs(1);
	puts("Please input the index");
	int index;
	(void)scanf("%d", &index);
	(void)getchar();
	if (index < 0 || index >= num_songs)
	{
		puts("invalid input");
	}
	else
	{
		int i;
		for (i = index; i < num_songs - 1; i++)
		{
			songs[i] = songs[i + 1];
		}
		num_songs--;
		save_songs();
		puts("remove_song successful");
	}
}
void create_test_data()
{
	song s1 = {"����", "����Ѹ", "fu_kua.lrc"};
	song s2 = {"Can't stand the rain", "The Rescues", "Can't stand the rain.lrc"};
	song s3 = {"ʮ��", "����Ѹ", "shi_nian.lrc"};
	songs[0] = s1;
	songs[1] = s2;
	songs[2] = s3;
	num_songs = 3;
	save_songs();
}
void add_song()
{
	song s = {0};
	puts("please input the song name");
	gets(s.name);
	puts("please input the cook name");
	gets(s.cook);
	puts("please input the file path, example: fu_kua.lrc, and you could only input english");
	gets(s.path);
	songs[num_songs] = s;
	num_songs++;
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
			(void)getchar();
			search();
			break;
		case 'd':
			(void)getchar();
			show_songs(0);
			break;
		case 'a':
			(void)getchar();
			if (!isAdmin)
			{
				puts("You don't have permission");
			}
			add_song();
			break;
		case 'r':
			(void)getchar();
			if (!isAdmin)
			{
				puts("You don't have permission");
			}
			remove_song();
			break;
		case 'c':
			(void)getchar();
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