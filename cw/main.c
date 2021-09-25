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
	char person[32*2];
	char street[18*2];
	short int house;
	short int apt;
	char date[10*2];
} Record;

typedef struct node Node;
struct node {
	Record data;
	Node* next;
	Node* prev;
};

void from_866_to_utf8(char *in, size_t *sizein, char *out, size_t *sizeout) {
	iconv_t cd = iconv_open("UTF-8", "CP866");
	iconv(cd, &in, sizein, &out, sizeout);
}

void decode(struct record2* base2, struct record* base) {
	for (int i = 0; i < 4000; ++i) {
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
/*
void showPage(Record* base, int page) {
	int N = RECONPAGE;
	int idx = page*N;
	printf("Page %d.\n", page);
	for (int i = idx; i < (idx + N) && i < 4000; ++i) {
		printRecord(base[i]);
	}

	printf("\n\n\e[3mPress 'd' for next page\nPress 'a' for previous page\n\e[0m");
}
*/
void showPageList(Node* list, int page) {
	int N = RECONPAGE;
	int idx = page*N;
	printf("Page %d.\n", page);
	
	int count = 0;
	while (count < idx && count < 4000) {
		list = list->next;
		++count;
	}

	for (int i = idx; i < (idx+N) && i < 4000; ++i) {
		printRecord(list->data);
		list = list->next;
	}

	printf("\n\n\e[3mPress 'd' for next page\n" \
					"Press 'a' for previous page\n" \
					"Press 'q' to exit\n\e[0m");
}

void clearScreen() {
	#ifndef ALL
	system("clear");
	#endif
}
/*
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
					if ((page+1) < (4000/N + (4000%N ? 1 : 0))) ++page;
					showPage(base, page);
					break;
				case 'a':
					clearScreen();
					if ((page-1) >= 0) --page;
					showPage(base, page);
					break;
				default:
					break;
		}
	}
}
*/
void showList(Node* list) {
	char c;
	int page = 0;
	int N = RECONPAGE;
	clearScreen();
	showPageList(list, page);
	while ((c = getc(stdin)) != 'q') {
		switch(c) {
				case 'd':
					clearScreen();
					if ((page+1) < (4000/N + (4000%N ? 1 : 0))) ++page;
					showPageList(list, page);
					break;
				case 'a':
					clearScreen();
					if ((page-1) >= 0) --page;
					showPageList(list, page);
					break;
				default:
					break;
		}
	}
}


Node* createNode() {
	Node* node = calloc(sizeof(Node), 1);
	node->next = NULL;
	node->prev = NULL;
	return node;
}

Node* createList(Record* base) {
	Node* list = createNode();
	Node* head = list;
	list->data = (base[0]);
	list->prev = NULL;
	Node* prev;
	for (int i = 1; i < 4000; ++i) {
		list->next = createNode();
		prev = list;
		list = list->next;

		list->data = (base[i]);
		list->prev = prev;
	}
	return head;
}

int main() {
	FILE *fp;
	fp = fopen("testBase4.dat", "rb");

	struct record* base = calloc(sizeof(struct record), 4000);
	struct record2* base2 = calloc(sizeof(struct record2), 4000);

	int i = fread((struct record *) base, sizeof(struct record), 4000, fp);
	if (i != 4000) fprintf(stderr, "Some errors with reading from .dat file\n");

	// decode from cp866 to utf-8
	decode(base2, base);

	fclose(fp);
	free(base);

	Record* baseArr = base2;

	//show(base2);
	
	Node* list = createList(baseArr);

	//printRecord(list->data);

	showList(list);

	return 0;
}

