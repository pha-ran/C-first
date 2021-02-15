#include <stdio.h>

void squeeze(char s[], int c)
{
	int i, j;

	for (i = j = 0; s[i] != '\0'; i++)
	{
		if (s[i] != c)
		{
			s[j++] = s[i];
		}
	}
	s[j] = '\0';
}

void squeeze2(char s1[], char s2[])
{
	int i, j, k;

	for (i = 0; s2[i] != '\0'; i++)
	{
		for (j = k = 0; s1[j] != '\0'; j++)
		{
			if (s1[j] != s2[i])
			{
				s1[k++] = s1[j];
			}
		}
		s1[k] = '\0';
	}
}

int main()
{
	char s[10] = "abc12345";
	int c = '3';
	squeeze(s, c);

	printf("%s \n", s);

	/* -------------------- */

	char s1[10] = "abc12345";
	char s2[5] = "bc4";

	squeeze2(s1, s2);

	printf("%s \n", s1);

	return 0;
}