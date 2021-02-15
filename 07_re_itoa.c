#include <stdio.h>
#include <string.h>

/* 1. itoa�� ���� ������ ���̰� ���� ���ڿ��� ���̺��� ũ��, ������ �����.*/

char* itoa(int n, char *s, int length)
{
	int i, sign;

	if ((sign = n) < 0)
	{
		n = -n;
	}
	
	i = 1;
	
	do {
		s[length -1 -i] = n % 10 + '0';
		i += 1;
	}   while ((n /= 10) > 0);
	
	s[length - 1] = '\0';

	if (sign < 0)
	{
		i += 1;
		s[length - i] = '-';
	}
	
	return &s[length - i];
}

int main()
{
	int a;
	char s[100];

	printf("������ �Է��ϼ���. ���ڿ��� ��ȯ�մϴ�. : ");
	scanf_s("%d", &a);
	printf("��ȯ ��� : %s \n", itoa(a, s, sizeof(s)) );

	return 0;
}