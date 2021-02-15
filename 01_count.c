#include <stdio.h>

main() {
	int c, i, j, nwhite, nother;
	int ndigit[10];

	nwhite = nother = 0;
	for (i = 0; i < 10; ++i)
		ndigit[i] = 0;

	while ((c = getchar()) != EOF)
		if (c >= '0' && c <= '9')
			++ndigit[c - '0'];
		else if (c == ' ' || c == '\n' || c == '\t')
			++nwhite;
		else
			++nother;

	printf("digits = \n");
	for (i = 0; i < 10; ++i)
	{
		printf("%d|", i);
		for (j = 0; j < ndigit[i]; ++j)
		{
			printf("¤±");
	    }
		printf("\n");
    }

	printf("white space = %d, other = %d \n", nwhite, nother);
}