#include <stdio.h>
#include <string.h>

char* add_big_number(char a[], char b[], char buf[], int len);

int main()
{
	char a[100], b[100], buf[100];
	char *res;
	printf("첫 번째 자연수를 입력하시오. :");
	scanf_s("%s", a, 100);
	printf("두 번쨰 자연수를 압력하시오. :");
	scanf_s("%s", b, 100);
	res = add_big_number(a, b, buf, 100);
	printf("결과값: %s\n", res);

	return 0;
}

char* add_big_number(char a[], char b[], char buf[], int len)
{
	int i, j, k, alen, blen;

	buf[len - 1] = '\0';

	alen = strlen(a);
	blen = strlen(b);

	if (alen > blen)
	{
		int s1, next = 0, next2 = 0;

		for (i = blen - 1, j = alen - 1, k = len - 2; i >= 0; i--, j--, k--)
		{
			s1 = (a[j] - '0') + (b[i] - '0');
			next = (s1 + next2) / 10;
			s1 = (s1 + next2) % 10;
			next2 = next;

			buf[k] = s1 + '0';
		}
		for (j; j >= 0; j--, k--)
		{
			s1 = (a[j] - '0') + next2;
			next = s1 / 10;
			s1 = s1 % 10;
			next2 = next;

			buf[k] = s1 + '0';
		}

		if (next2)
		{
			buf[k] = next2 + '0';

			return &buf[k];
		}
		else
		{
			return &buf[++k];
		}
	}
	else
	{
		int s1, next = 0, next2 = 0;

		for (i = blen - 1, j = alen - 1, k = len - 2; j>= 0; i--, j--, k--) //i가 더 클때
		{
			s1 = (a[j] - '0') + (b[i] - '0');
			next = (s1 + next2) / 10;
			s1 = (s1 + next2) % 10;
			next2 = next;

			buf[k] = s1 + '0';
		}
		for (i; i >= 0; i--, k--)
		{
			s1 = (b[i] - '0') + next2;
			next = s1 / 10;
			s1 = s1 % 10;
			next2 = next;

			buf[k] = s1 + '0';
		}

		if (next2)
		{
			buf[k] = next2 + '0';

			return &buf[k];
		}
		else
		{
			return &buf[++k];
		}
	}
}