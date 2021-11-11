#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iconv.h>

#include "search.c"

#define RECNUM 4000

#ifndef RECONPAGE
#define RECONPAGE 10
#endif

#include "struct.h"
#include "mergeSort.h"

Que g_mergedQue;

void from_866_to_utf8(char *in, size_t *sizein, char *out, size_t *sizeout) {
	iconv_t cd = iconv_open("UTF-8", "CP866");
	iconv(cd, &in, sizein, &out, sizeout);
}

void decode(struct record2* base2, struct record* base) {
	for (int i = 0; i < RECNUM; ++i) {
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

void printRecord(Record* record) {
	printf("%-32s %-18s %-6d %-6d %-10s\n", 
					record->person,
					record->street,
					record->house,
					record->apt,
					record->date
					);	
}

void printHelp() {
	printf("\n\n\e[3mPress 'd' for the next page\n" \
					"Press 'a' for the previous page\n" \
					"Press 'l' for the last page\n" \
					"Press 'k' for the first page\n" \
					"Press 's' for the search\n" \
					"Press 'q' to exit\n\e[0m");
}

void printHelpQue() {
	printf("\n\n\e[3mPress 'd' for the next page\n" \
					"Press 'a' for the previous page\n" \
					"Press 'l' for the last page\n" \
					"Press 'k' for the first page\n" \
					"Press 'q' to exit from search mode.\n\e[0m");
}


void showPageList(Node* list, int page, int size) {
	int N = RECONPAGE;
	int idx = page*N;
	printf("Page %d.\n", page);
	
	int count = 0;
	while (count < idx && count < size) {
		list = list->next;
		++count;
	}

	for (int i = idx; i < (idx+N) && i < size; ++i) {
		printRecord(list->pdata);
		list = list->next;
	}

	printHelp();
}

// TODO: fix (check until `tail` is reached)
void showPageQue(Que que, int page, int size) {
	int N = RECONPAGE;
	int idx = page*N;
	printf("Search mode.\n");
	printf("Page %d.\n", page);
	
	int count = 0;
	Node* p = que.head;
	while (count < idx && count < size) {
		p = p->next;
		++count;
	}

	for (int i = idx; i < (idx+N) && i < size; ++i) {
		printRecord(p->pdata);
		p = p->next;
	}

	printHelpQue();
}


void clearScreen() {
	#ifndef ALL
	system("clear");
	#endif
}

void showList(Node*, int);

int nextPage(int page, int size) {
	if ((page+1) < (size/RECONPAGE + (size%RECONPAGE ? 1 : 0))) ++page;
	return page;
}

int prevPage(int page, int size) {
	if ((page-1) >= 0) --page;
	return page;
}

int lastPage(int page, int size) {
	return size ? size/RECONPAGE+(size%RECONPAGE?1:0) - 1 : 0;
}

void showQueSort(Que que) {
	char c;
	int page = 0;
	int N = RECONPAGE;
	printf("inside:\n");
	int size = sizeQue(que);

	//Node* list = (Node*)que.head;

	clearScreen();
	showPageQue(que, page, size);
	while ((c = getc(stdin)) != 'q') {
		switch(c) {
				case 'd':
					clearScreen();
					page = nextPage(page, size);
					showPageQue(que, page, size);
					break;
				case 'a':
					clearScreen();
					page = prevPage(page, size);
					showPageQue(que, page, size);
					break;
				case 'l':
					clearScreen();
					page = lastPage(page, size);
					showPageQue(que, page, size);
					break;
				case 'k':
					clearScreen();
					page = 0;
					showPageQue(que, page, size);
					break;
				default:
					break;
		}
	}
}

void startSearch(Node* list) {

	Record** indexArray = calloc(sizeof(Record*), 4000);
	Node* p = list;
	for (int i = 0; i < 4000; ++i, p = p->next)
		indexArray[i] = p->pdata;

	printf("Using the field 'year' as a key of the search.\n");
	printf("Enter '0' to exit.\n");
	printf("Valid year format: 94 (not 1994)\n");
	int year;
	while (1) {
		printf("Please enter the year: ");
		scanf("%d", &year);
		if (year == 0) return; // exit
		if (year > 0 && year < 100) break;
		else {
			printf("\nHint: Use 94 if you want to search by 1994.\n");
			printf("Year's range: (1-99)\n");
			printf("Enter '0' to exit.\n");
			printf("Try again!\n\n");
		}
	};

	Que que;
	que = search(g_mergedQue, indexArray, 4000, year);
	
	showQueSort(que);
}

void showList(Node* list, int size) {
	char c;
	int page = 0;
	int N = RECONPAGE;
	clearScreen();
	showPageList(list, page, size);
	while ((c = getc(stdin)) != 'q') {
		switch(c) {
				case 'd':
					clearScreen();
					page = nextPage(page, size);
					showPageList(list, page, size);
					break;
				case 'a':
					clearScreen();
					page = prevPage(page, size);
					showPageList(list, page, size);
					break;
				case 'l':
					clearScreen();
					page = lastPage(page, size);
					showPageList(list, page, size);
					break;
				case 'k':
					clearScreen();
					page = 0;
					showPageList(list, page, size);
					break;
				case 's':
					clearScreen();
					printf("Search.\n");
					startSearch(list);
					clearScreen();
					page = 0;
					showPageList(list, page, size);
					break;
				default:
					break;
		}
	}
}

Node* createNode() {
	Node* node = calloc(sizeof(Node), 1);
	node->next = NULL;
	return node;
}

Node* createList(Record* base) {
	Node* list = createNode();
	Node* head = list;
	list->pdata = base;
	for (int i = 1; i < RECNUM; ++i) {
		list->next = createNode();
		list = list->next;

		list->pdata = (base + i);
	}
	return head;
}

int main() {
	FILE *fp;
	fp = fopen("testBase4.dat", "rb");

	struct record* base = calloc(sizeof(struct record), RECNUM);
	struct record2* base2 = calloc(sizeof(struct record2), RECNUM);

	int i = fread((struct record *) base, sizeof(struct record), RECNUM, fp);
	if (i != RECNUM) fprintf(stderr, "Some errors with reading from .dat file\n");

	decode(base2, base);
	fclose(fp);
	free(base);

	Node* list = createList((Record*)base2);

	g_mergedQue = mergeSort(&list, 4000, sortDateStreet);

	showList(list, 4000);

	return 0;
}

