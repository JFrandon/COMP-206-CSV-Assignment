#include<stdio.h>
#include <stdlib.h>


typedef unsigned long long size;

size get_linenumber(const char* filename) {
	FILE * file = fopen(filename, "rt");
	size count = 0;
	int c;
	if (file == NULL) return -1;
	while ((c = fgetc(file)) != EOF) {
		if (c == '\n') {
			count++;
		}
	}
	fclose(file);
	return count;
}

int check_file(FILE * file) {
	return file->_fileno != -1;
}


FILE ** get_array_from_file(const char* filename) {
	size linenum = get_linenumber(filename);
	FILE * * fileArr = (FILE **)calloc(linenum, sizeof(FILE *));
	FILE * * current = fileArr;
	for (int i = 0; i < linenum; i++) {
		*current = fopen(filename, "rt");
		for (int j = 0; j < i; j++) {
			while (fgetc(*current) != '\n');
		}
		current++;
	}
	return fileArr;
}

void convert_arr_to_csv(FILE * output, FILE * *  fileArr, int linenum) {
	int i = 0;
	int next = linenum;
	int c;
	while (next != 0) {
		if (check_file(*(fileArr + i))) {
			c = fgetc(*(fileArr + i));
		}
		else {
			i = (i + 1) % linenum;
			continue;
		}
		if (c == '\r') continue;
		if (c == '\n' || c == EOF)
		{
			fclose(*(fileArr + i));
			next--;
		}
		if (c == ' ' || c == '\n' || c == EOF) {
			if (i == linenum - 1)  c = '\n';
			else c = ',';
			i = (i + 1) % linenum;
		}
		fputc(c, output);
	}
}

void load_and_convert(const char* filename) {
	
	size linenum = get_linenumber(filename);
	FILE * *  fileArr = get_array_from_file(filename);

	FILE * output = fopen("./output.csv", "w+");
	convert_arr_to_csv(output, fileArr, linenum);
}