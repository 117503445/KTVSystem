#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef char* string;
typedef struct
{
	string s[100];
	int length;
} lst_string;
typedef struct
{
	char name[20];
	char singer[20];
	char path[100];
} song;
song songs[100];
int num_songs = 2;
void write_string(string path, string text)
{
	FILE* fp = fopen(path, "w+");
	fprintf(fp, "%s", text);
	fclose(fp);
}
void write_strings(string path, lst_string texts)
{
	int i;
	FILE* fp = fopen(path, "w+");

	for (i = 0; i < texts.length; i++)
	{
		fprintf(fp, "%s\n", texts.s[i]);
	}
	fclose(fp);
}

void read_string(string path)
{
	const int max_line_char_num = 1024;
	FILE* fp = fopen(path, "r");
	if (fp == NULL)
	{
		printf("Open File failed.\n");
		return;
	}
	else
	{
		char str[1024];
		while (!feof(fp))
		{
			fgets(str, max_line_char_num, fp);
			printf("%s", str);
		}
		fclose(fp);
	}
	printf("\n");
}
void search()
{
	char s[100] = { 0 };
	gets(s);
	int i;
	for (i = 0; i < num_songs;i++) {
		if (strcmp(songs[i].singer,s)==0)
		{
			printf("\n---%s---\n---%s---\n---%s---", songs[i].name, songs[i].singer, songs[i].path);
			read_string(songs[i].path);
			printf("\n");
		}
	}
	//read_string("Can't stand the rain.lrc");
}

void user_loop()
{
	char c;
	while (1)
	{
		puts("Press Q To quit\nPress S to search");

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
		default:
			printf("invalid input\n");

			break;
		}
		//(void)getchar();
	}
}

int main()
{
	song s1 = { "¸¡¿ä","³ÂÞÈÑ¸","fk.lrc" };
	song s2 = { "Can't stand the rain","The Rescues","fk.lrc"};
	songs[0] = s1;
	songs[1] = s2;



	int isAdmin = 0;
	puts("Are you Admin? User:press 0,Admin:press 1");
	(void)scanf("%d", &isAdmin);
	if (isAdmin != 0 && isAdmin != 1)
	{
		puts("invalid input");
		return 0;
	}
	(void)getchar();

	if (isAdmin) {

	}
	else
	{
		user_loop();
	}


	return 0;
}