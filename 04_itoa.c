#include <stdio.h>
#include <ctype.h>

int int_len(int n)  //정수의 (문자열로 변환했을 경우에) 마지막 인덱스를 반환
{
	int i, j;

	for (i = 0, j = n; ( (j /= 10) != 0 ); ++i)
		;

	return i;
}

int itoa(int n, char s[])
{
	int i, start, end;

	start = 0;
	end = int_len(n);

	if (n < 0)  //음수의 처리
	{
		s[start++] = '-'; //인덱스 0에 -대입
		n *= -1;         //n을 양수로 바꿔서 처리
		end += 1;         //- 가 들어갈 공간 추가
	}

	s[end + 1] = '\0'; //문자열의 끝 처리

	for (i = n; end >= start; i /= 10)
	{
		s[end--] = (i % 10) + '0';
	}
}

int main()
{
	int a;
	char s[10];

	printf("정수를 입력하세요. 문자열로 변환합니다. : ");
	scanf_s("%d", &a);
	itoa(a, s);
	printf("변환 결과 : %s \n", s);

	return 0;
}