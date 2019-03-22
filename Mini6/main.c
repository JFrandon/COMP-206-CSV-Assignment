#include<stdio.h>
#include <stdlib.h>
#include "./convert_to_csv.h"

int match_line(FILE* f, char * m) {
	int c = fgetc(f);
	int d;
	if (c == EOF) return -1;
	if (*m == 0 && c == ',') { 
		return 1;
	}
	if (c != *m) {
		return 0;
	}
	if (c == *m && (d = match_line(f,++m)) > 0) {
		return 1;
	}
	else {
		return 0;
	}

}

void find_name(const char* csv_filename, const char* name) {
	FILE * f = fopen(csv_filename,"rt");
	int r = 0;
	char c;
	do {
		if ((r=match_line(f, name)) ==1) {
			printf("%s,", name);
			while((c = fgetc(f)) != '\n') putchar(c);
			putchar('\n');
		}
		else {
			do { c = fgetc(f); } while (c != '\n' && c !=EOF);
		}

	} while (r != -1);
	fclose(f);

}



int main()
{
	
	load_and_convert("input.txt");
	read_csv("output.csv");
	find_name("output.csv", "Maria");
	find_name("output.csv", "Jason");

	return 0;
}