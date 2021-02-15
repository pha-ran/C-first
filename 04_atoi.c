#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int char_len(char s[])  //문자열의 길이를 리턴 ('\0'을 제외)
{
	int i;

	for (i = 0; s[i] != '\0'; i++)
		;

	return i - 1;
}

int int_or_not(char s[])  //문자열이 온전한 정수인지 판단 F = 0, T = 1
{
	int i, j;

	if ( (s[0] == '\0') || ( (char_len(s) + 1 == 1) && (s[0] == '-') ) )  //입력값이 공백이거나 '-' 일경우 False
		return 0;

	for (i = char_len(s), j = 0; i >= 0; i--)
	{
		if (isdigit(s[i]))
			;
		//printf("T");  //디버깅용
		else
		{
			j += 1;  //숫자가 아닐경우 J를 증가시킴
			//printf("F");	//디버깅용
		}
	}

	if (s[0] == '-')  //음의 정수 처리
		j -= 1;

	if (j == 0)
		return 1;
	else
		return 0;
}

int atoi (char s[])  //문자열을 정수로 전환
{
	if (int_or_not(s) == 1)
	{
		int i, n, sign;

		for (i = 0; isspace(s[i]); i++)
			;

		sign = (s[i] == '-') ? -1 : 1;

		if (s[i] == '+' || s[i] == '-')
			i++;

		for (n = 0; isdigit(s[i]); i++)
			n = 10 * n + (s[i] - '0');

		return sign * n;
	}
	else
		return INT_MIN;
}

int main()
{
	char a[10];

	printf("문자열을 입력하세요. 정수일 경우, 정수로 변환합니다. : ");
	
	gets_s(a, 10);
	
	//scanf_s("%s", a, 12);  //문자 사이 공백을 읽지 못함. gets_s는 가능

	printf("결과 (-2147483648일 경우 에러) : %d \n", atoi(a));

	return 0;
}