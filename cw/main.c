
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iconv.h>

#ifndef RECONPAGE
#define RECONPAGE 10
#endif

struct record {
	char person[32];
	char street[18];
	short int house;
	short int apt;
	char date[10];
};

typedef struct record2 {
	char person[64];
	char street[36];
	short int house;
	short int apt;
	char date[20];
} Record;

void from_866_to_utf8(char *in, size_t *sizein, char *out, size_t *sizeout) {
	iconv_t cd = iconv_open("UTF-8", "CP866");
	iconv(cd, &in, sizein, &out, sizeout);
}

void printRecord(Record record) {
	printf("%-32s %-18s %-6d %-6d %-10s\n", 
					record.person,
					record.street,
					record.house,
					record.apt,
					record.date
					);	
}

void showPage(Record* base, int page) {
	int idx = page;
	int N = RECONPAGE;
	printf("Page %d.\n", page);
	for (int i = idx; i < (idx + N); ++i) {
		printRecord(base[i]);
	}

	printf("\n\n\e[3mPress 'd' for next page\nPress 'a' for previous page\n\e[0m");
}

void clearScreen() {
	system("clear");
}

void show(Record* base) {
	char c;
	int page = 0;
	int N = RECONPAGE;
	clearScreen();
	showPage(base, page);
	while ((c = getc(stdin)) != 'q') {
		switch(c) {
				case 'd':
					clearScreen();
					if ((page+1) <= (4000/N + (4000%N ? 1 : 0))) ++page;
					showPage(base, page);
					break;
				case 'a':
					clearScreen();
					if ((page-1) >= 0) --page;
					showPage(base, page);
					break;
		}
	}
}

int main() {
	FILE *fp;
	fp = fopen("testBase4.dat", "rb");

	struct record base[4000] = { 0 };
	struct record2 base2[4000] = { 0 };

	int i;
	i = fread((struct record *) base, sizeof(struct record), 4000, fp);

	/*
	for (i = 0; i < 4; ++i) {
		printf("'%s'='%s'='%4d' %4d %s\n",
			base[i].person,
			base[i].street,
			base[i].house,
			base[i].apt,
			base[i].date
			);
	}
	printf("--------------\n");
	*/

	for (i = 0; i < 4000; ++i) {
			size_t sizein = sizeof(base[i].person);
			size_t sizeout = sizeof(base2[i].person);
			char *in = calloc(sizeof(char), sizein);
			char *out = calloc(sizeof(char), sizeout);
			strcpy(in, base[i].person);
			from_866_to_utf8(in, &sizein, out, &sizeout);
			strcpy(base2[i].person, out);
			free(in);
			free(out);

			sizein = sizeof(base[i].street);
			sizeout = sizeof(base2[i].street);
			in = calloc(sizeof(char), sizein);
			out = calloc(sizeof(char), sizeout);
			strcpy(in, base[i].street);
			from_866_to_utf8(in, &sizein, out, &sizeout);
			strcpy(base2[i].street, out);
			free(in);
			free(out);

			base2[i].apt = base[i].apt;
			base2[i].house = base[i].house;
			strcpy(base2[i].date, base[i].date);
	}

	/*
	for (i = 0; i < 4; ++i) {
		printf("%s ... %s ... %4d ... %4d ... %s\n",
			base2[i].person,
			base2[i].street,
			base2[i].house,
			base2[i].apt,
			base2[i].date
			);
	}
	*/

	show(base2);

	return 0;
}

