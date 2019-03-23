#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "convert_to_csv.h"
#include "read_csv.h"

int get_char_number(const char* csv_filename) {
	FILE *f=fopen(csv_filename,"rt");
	int i = 1;
	while ((fgetc(f)) != EOF) {
		i++;
	}
	fclose(f);
	return i;
}

void filecp(const char * source,const char * dest) {
	FILE *s = fopen(source, "rt");
	FILE * d = fopen(dest, "wt");
	int c;
	while ((c = fgetc(s)) != EOF) {
		fputc(c,d);
	}
	fclose(s);
	fclose(d);
}

const char * match_line(FILE* f, const char * m) {
	int l = strlen(m);
	const char * comp = calloc(l + 1, sizeof(char));
	char * c = comp;
	for (int i = 0; i < l; i++) {
		if ((*(c++) = fgetc(f)) != *(m + i))
			break;
	}
	return comp;
}

void find_name(const char* csv_filename, const char* name) {
	FILE * f = fopen(csv_filename,"rt");
	int c;
	do {
		if ((strcmp(match_line(f, name),name)) ==0) {
			printf("%s", name);
			while((c = fgetc(f)) != '\n') putchar(c);
			putchar('\n');
		}
		else {
			do { c = fgetc(f); } while (c != '\n' && c !=EOF);
		}

	} while (c != -1);
	fclose(f);
	putchar('\n');
}

void add_record(const char*	csv_filename, const char* name, const int age, const char* city) {
	FILE * f = fopen(csv_filename,"at");
	fprintf(f, "%s,%d,%s\n", name, age, city);
	fclose(f);
}

void delete_record(const char* csv_filename, const char* name) {
	FILE * f = fopen(csv_filename, "rt");
	FILE * g = fopen("/tmp/temp.txt", "wt"); //*nix specific
	int r = 0;
	int c;
	char * result;
	do {
		result = match_line(f, name);
		if ((strcmp(result, name)) != 0) {
			fprintf(g,"%s", result);
			while ((c = fgetc(f)) != '\n') fputc(c,g);
			fputc('\n',g);
		}
		else {
			do { c = fgetc(f); } while (c != '\n' && c != EOF);
			while ((c = fgetc(f)) != EOF) {
				fputc(c,g);
			}
			break;
		}

	} while (r != -1);
	fclose(f);
	fclose(g);
	filecp("/tmp/temp.txt", csv_filename);
	system("rm /tmp/temp.txt");
}

int main()
{
	/* Question 1 */
	load_and_convert("input.txt");
	/* Question 2 */
	read_csv("output.csv");
	/* Question 3.1 */
	find_name("output.csv", "Maria");
	find_name("output.csv", "Jason"); //Jason doesn't exist
	/* Question 3.2 */
	add_record("output.csv", "Jason", 36, "Skookumchuk");
	read_csv("output.csv"); // to print to the screen
	/* Question 3.3 */
	delete_record("output.csv", "Maria");
	read_csv("output.csv"); // to print to the screen
	return 0;
}