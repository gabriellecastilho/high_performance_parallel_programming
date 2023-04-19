#include <stdio.h>

int	main(void)
{
	int		item1;
	double	item2;
	char	item3;
	float	item4;
	FILE	*file;

	file = fopen("little_bin_file", "r");
	fread(&item1, sizeof(int), 1, file);
	printf("%d \n", item1);
	fread(&item2, sizeof(double), 1, file);
	printf("%f \n", item2);
	fread(&item3, sizeof(char), 1, file);
	printf("%c \n", item3);
	fread(&item4, sizeof(float), 1, file);
	printf("%f \n", item4);
	fclose(file);
	return (0);
}
