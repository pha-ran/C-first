#include <stdio.h>
#include <string.h>

/* 1. itoa는 받은 정수의 길이가 넣을 문자열의 길이보다 크면, 에러가 생긴다.*/

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

	printf("정수를 입력하세요. 문자열로 변환합니다. : ");
	scanf_s("%d", &a);
	printf("변환 결과 : %s \n", itoa(a, s, sizeof(s)) );

	return 0;
}