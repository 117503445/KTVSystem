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
	char name[50];
	char cook[20];
	char path[100];
} food;


food foods[100];
int num_foods = 0;

char* file_foods = "foods.scv";

void save_foods() {
	FILE* fp = fopen(file_foods, "w+");
	int i;
	for (i = 0; i < num_foods; i++)
	{
		fprintf(fp, "%s;%s;%s", foods[i].name, foods[i].cook, foods[i].path);
		if (i != num_foods - 1)
		{
			fprintf(fp, "\n");
		}
	}
	fclose(fp);
}
void load_foods() {
	const int max_line_char_num = 1024;
	FILE* fp = fopen(file_foods, "r");
	if (fp == NULL)
	{
		printf("Open foods.scv failed.\n");
		return;
	}
	else
	{
		char str[1024] = { 0 };
		char* t;
		while (!feof(fp))
		{
			fgets(str, max_line_char_num, fp);
			t = strtok(str, ";");
			strcpy(foods[num_foods].name, t);
			//printf("%s\n", t);
			t = strtok(NULL, ";");
			strcpy(foods[num_foods].cook, t);
			//printf("%s\n", t);	
			t = strtok(NULL, ";");
			//printf("%s\n", t);
			strcpy(foods[num_foods].path, t);
			if (foods[num_foods].path[strlen(foods[num_foods].path) - 1] == '\n')
			{
				foods[num_foods].path[strlen(foods[num_foods].path) - 1] = 0;
			}
			num_foods++;
		}
		fclose(fp);
	}
}
void show_foods(int isShowIndex) {
	printf("\nnum_foods is %d\n", num_foods);
	int i;
	for (i = 0; i < num_foods; i++)
	{
		if (isShowIndex) {
			printf("%d ", i);
		}
		printf("%s;%s;%s\n", foods[i].name, foods[i].cook, foods[i].path);
	}
	puts("");
}

void read_string(string path)
{
	const int max_line_char_num = 1024;
	FILE* fp = fopen(path, "r");
	if (fp == NULL)
	{
		printf("Open %s failed.\n", path);
		return;
	}
	else
	{
		while (!feof(fp))
		{
			char str[1024] = { 0 };
			fgets(str, max_line_char_num, fp);
			printf("%s", str);
		}
		fclose(fp);
	}
	printf("\n");
}

void show_lrc(food s) {
	printf("\n---%s---\n---%s---\n---%s---\n\n", s.name, s.cook, s.path);
	read_string(s.path);
	printf("\n");
}
void search()
{
	printf("Please input cook or food's name\n");
	char s[100] = { 0 };
	gets(s);//ËÑË÷×Ö·û´®
	int i;

	int resultNum = 0;
	int indexs[100] = { 0 };

	for (i = 0; i < num_foods; i++) {
		if (strstr(foods[i].cook, s) != NULL || strstr(foods[i].name, s) != NULL)
		{
			indexs[resultNum] = i;
			printf("%d %s *** %s *** %s\n", resultNum, foods[i].name, foods[i].cook, foods[i].path);
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
		show_lrc(foods[indexs[0]]);
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
		show_lrc(foods[indexs[d]]);
		(void)getchar();
	}
}
void remove_food() {
	show_foods(1);
	puts("Please input the index");
	int index;
	(void)scanf("%d", &index);
	(void)getchar();
	if (index < 0 || index >= num_foods)
	{
		puts("invalid input");
	}
	else
	{
		int i;
		for (i = index; i < num_foods - 1; i++)
		{
			foods[i] = foods[i + 1];
		}
		num_foods--;
		save_foods();
		puts("remove_food successful");
	}


}
void create_test_data() {
	food s1 = { "¸¡¿ä","³ÂÞÈÑ¸","fu_kua.lrc" };
	food s2 = { "Can't stand the rain","The Rescues","Can't stand the rain.lrc" };
	food s3 = { "Ê®Äê","³ÂÞÈÑ¸","shi_nian.lrc" };
	foods[0] = s1;
	foods[1] = s2;
	foods[2] = s3;
	num_foods = 3;
	save_foods();
}
void add_food() {
	food s = { 0 };
	puts("please input the food name");
	gets(s.name);
	puts("please input the cook name");
	gets(s.cook);
	puts("please input the file path,example: fu_kua.lrc, and you could only input english");
	gets(s.path);
	foods[num_foods] = s;
	num_foods++;
	save_foods();

	puts("please input words, enter blank line to stop input\n");


	FILE* fp = fopen(s.path, "w+");
	while (1) {
		char buf[1024] = { 0 };
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
void main_loop(int isAdmin) {
	char c;
	while (1)
	{
		puts("Press Q To quit\nPress S to search\nPress D To display all foods");
		if (isAdmin) {
			puts("Press A To add food\nPress R To romove foods\nPress C To create default data");
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
			show_foods(0);
			break;
		case 'a':
			(void)getchar();
			if (!isAdmin)
			{
				puts("You don't have permission");
			}
			add_food();
			break;
		case 'r':
			(void)getchar();
			if (!isAdmin)
			{
				puts("You don't have permission");
			}
			remove_food();
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
	load_foods();
	int isAdmin = 0;
	puts("Are you Admin? User:press 0,Admin:press 1");
	while (1) {
		(void)scanf("%d", &isAdmin);
		(void)getchar();
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