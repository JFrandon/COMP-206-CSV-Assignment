#include<stdio.h>
#include <stdlib.h>

void read_csv(const char* csv_filename) {
	FILE * f =fopen(csv_filename,"rt");
	int c;
	while ((c = fgetc(f)) != EOF) {
		putchar(c);
	}
	fclose(f);
	putchar('\n');
}
