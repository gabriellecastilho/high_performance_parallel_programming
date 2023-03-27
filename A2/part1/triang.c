#include <stdio.h>
#include <stdlib.h>

void  pascal_triang(int lines)
{
	int n;
	int i;
	int c;

	c = 1;
	for(n = 0; n < lines; n++)
	{
        	for(i = 0; i <= n; i++)
        	{
            		if (i == 0 || n == 0)
               			c = 1;
            		else
               			c = c * (n + 1 - i) / i;
	            	printf("% 4d", c);
        	}
        	printf("\n");
	}
}

int main(int argc, char *argv[])
{
	int lines;

	argc = 1;
	lines = atoi(argv[1]);
	pascal_triang(lines);
	return (0);
}
