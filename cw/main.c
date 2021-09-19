
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

struct record {
	char person[32];
	char street[18];
	short int house;
	short int apt;
	char date[10];
};

int main() {
	//setlocale(LC_ALL, "utf8");
	printf("Coursework.\n");

	FILE *fp;
	fp = fopen("testBase4.dat", "rb");

	struct record base[4000] = { 0 };

	int i;
	i = fread((struct record *) base, sizeof(struct record), 4000, fp);

	for (i = 0; i < 4; ++i) {
		printf("%s %s %4d %4d %s\n",
			base[i].person,
			base[i].street,
			base[i].house,
			base[i].apt,
			base[i].date
			);
	}

	FILE *fout;
	fout = fopen("base_newlines.txt", "w");
	for (i = 0; i < 4000; ++i) {
		fprintf(fout, "%-32s\n%-18s\n%-4d\n%-4d\n%-10s\n",
			base[i].person,
			base[i].street,
			base[i].house,
			base[i].apt,
			base[i].date
		);
	}

	system("iconv -f cp866 -t utf-8 -o base_utf.txt base_newlines.txt");

	printf("Converted!!\n\n\n");

	char c;
	FILE *fin;
	fin = fopen("base_utf.txt", "r");
	for (i = 0; i < 4000; ++i) {
			/*
		char *read_person = calloc(sizeof(char), 32);
		size_t len = 0;
		getline(&read_person, &len, fin);
		strcpy(base[i].person, read_person);
		base[i].person[31] = '\0';

		char *read_street = calloc(sizeof(char), 18);
		size_t len2 = 0;
		getline(&read_street, &len2, fin);
		strcpy(base[i].street, read_street);
		base[i].street[17] = '\0';
		
		char *read_date = calloc(sizeof(char), 10);
		size_t len3 = 0;
		getline(&read_date, &len3, fin);
		strcpy(base[i].date, read_date);
		base[i].date[9] = '\0';
			*/

		//getline(base[i].street, 18, fin);
		//getline(base[i].date, 10, fin);

		//fscanf(fin, "%[^\n]", base[i].person);
		//fscanf(fin, "%[^\n]", base[i].street);
		//fscanf(fin, "%[^\n]", base[i].date);
		
		
		int idx = 0;
		char c;
		while ((c = getc(fin)) != '\n' && (c != EOF))
			base[i].person[idx++] = c;
		base[i].person[31] = '\0';

		idx = 0;
		while ((c = getc(fin)) != '\n' && (c != EOF))
			base[i].street[idx++] = c;
		base[i].street[17] = '\0';

		fscanf(fin, "%hd", &(base[i].house));
		fscanf(fin, "%hd", &(base[i].apt));

		while ((c = getc(fin)) != '\n') ;

		idx = 0;
		while ((c = getc(fin)) != '\n' && (c != EOF))
			base[i].date[idx++] = c;
		base[i].date[9] = '\0';
			

		//fgets(base[i].person, 32, fin);
		//fgets(base[i].street, 18, fin);
		//fgets(base[i].date,   10, fin);
		//fread(&base[i].person, sizeof(char), 32, fin);
		//fread(&base[i].street, sizeof(char), 18, fin);
		//fread(&base[i].date, sizeof(char), 10, fin);
	}

	for (i = 0; i < 2; ++i) {
		printf("%s ... %s ... %4d ... %4d ... %s\n",
			base[i].person,
			base[i].street,
			base[i].house,
			base[i].apt,
			base[i].date
			);
	}

	printf(":::: %c\n", base[0].person[1]);



	return 0;
}

