#include <stdio.h>

int main ()
{
	int item1;
 	double item2;
 	char item3;
 	float item4;
	size_t mem_size;

	FILE *file;
 	file = fopen("little_bin_file", "r");
	mem_size = 1;
 	fread(&item1, sizeof(int), mem_size, file);
 	printf("%d \n", item1);
 	fread(&item2, sizeof(double), mem_size, file);
 	printf("%f \n", item2);
 	fread(&item3, sizeof(char), mem_size, file);
 	printf("%c \n", item3);
 	fread(&item4, sizeof(float), mem_size, file);
 	printf("%f \n", item4);
 	fclose(file);
 	return 0;
}
