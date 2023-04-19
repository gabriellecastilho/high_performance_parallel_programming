#include <stdio.h>
#include <stdlib.h>

void	pascal_triangle(int lines)
{
	int	n;
	int	i;
	int	result;

	result = 1;
	for (n = 0; n < lines; n++)
	{
			for (i = 0; i <= n; i++)
			{
					if (i == 0 || n == 0)
						result = 1;
					else
						result = result * (n + 1 - i) / i;
					printf("% 4d", result);
			}
			printf("\n");
	}
}

int	main(int argc, char const *argv[])
{
	int	lines;

	argc = 1;
	lines = atoi(argv[1]);
	pascal_triangle(lines);
	return (0);
}
