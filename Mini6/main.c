#include "./convert_to_csv.h"

int main()
{
	printf("%d\n", get_linenumber("input.txt"));
	load_and_convert("input.txt");
	return 0;
}