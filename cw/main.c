
#include <stdio.h>
#include <locale.h>

struct record {
	char person[32];
	char street[18];
	short int house;
	short int apt;
	char date[10];
};

int main() {
	setlocale(LC_ALL, "utf-16");
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
	fout = fopen("base_newlines.txt", "wb");
	for (i = 0; i < 4000; ++i) {
		fprintf(fout, "%32s\n%18s\n%10s\n", 
			base[i].person,
			base[i].street,
			//base[i].house,
			//base[i].apt,
			base[i].date
		);
	}

	system("iconv -f cp866 -t utf-8 -o base_utf.txt base_newlines.txt");

	char c;
	FILE *fin;
	fin = fopen("base_utf.txt", "rb");
	for (i = 0; i < 4000; ++i) {
		fscanf(fin, "%[^\n]", base[i].person);

		fscanf(fin, "%[^\n]", base[i].street);	
		fscanf(fin, "%[^\n]", base[i].date);	
		//fgets(base[i].person, sizeof(base[i].person), fin);
		//fgets(base[i].street, sizeof(base[i].street), fin);
		//fgets(base[i].date,   sizeof(base[i].date), fin);
		//fread(&base[i].person, sizeof(char), 32, fin);
		//fread(&base[i].street, sizeof(char), 18, fin);
		//fread(&base[i].date, sizeof(char), 10, fin);
	}

	for (i = 0; i < 4; ++i) {
		printf("%s %s %4d %4d %s\n", 
			base[i].person,
			base[i].street,
			base[i].house,
			base[i].apt,
			base[i].date
			);	
	}



	return 0;
}

