#include<stdio.h>
#include <stdlib.h>

read_csv(const char* csv_filename) {
	FILE * f =fopen(csv_filename,"r+");
	int c;
	while ((c = fgetc(f)) != EOF) {
		putchar(c);
	}
	fclose(f);
}