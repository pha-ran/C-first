#include <stdio.h>

#define MAXLINE 1000

int lastindex(char s[])  //문자열의 '\0'을 제외한 마지막 인덱스를 리턴
{
	int i;

	for (i = 0; s[i] != '\0'; i++)
		;

	return i - 1;
}

int strrindex2(char s[], char t[])  //문자열 s에서 t와 같은 문자 패턴이 있으면 마지막 패턴의 첫 글자 인덱스를 리턴, 없으면 -1을 리턴
{
	int i, j, k;

	for (i = lastindex(s); i >= lastindex(t); i--)  // 문자열 s가 문자열 t보다 길이가 길 경우에만 실행
	{
		for (j = i, k = lastindex(t); s[j] == t[k]; j--, k--)
			;
		if (k < 0)
			return i - lastindex(t);
	}
	return -1;
}

/*
	매개변수
	- strrindex는 매개변수로 문자열 두개를 받습니다. s는 전체 문자열, t는 s에서 찾을 문자열 패턴입니다.

	반환값
	- strrindex는 첫 번째 문자열 s에서 두 번째 문자열 t와 같은 문자열 패턴이 존재할 경우, t와 같은 패턴이 시작점 인덱스를 반환합니다.
	- ex) s가 12345이고, t가 34 이면 2를 반환
	- t와 같은 문자열 패턴이 여러 개 존재할 경우, 가장 오른쪽 패턴의 시작점 인덱스를 반환합니다.
	- ex) s가 12341234이고, t가 3이면 6을 반환
	- s에서 t와 같은 패턴을 찾을 수 없을 경우, -1을  반환합니다.

	설명
	-  먼저 lastindex에서 두 문자열의 마지막 인덱스를 얻습니다, s가 t보다 클 경우에만 탐색이 시작되고, 작을 경우 -1이 반환됩니다.
	-  탐색이 시작되면, s 문자열의 뒤에서부터 첫번째 글자까지, s의 i번째 인덱스의 글자와 t의 마지막 글자가 같은지 검사합니다.
	-  같을 경우, 첫 번째 글자까지 t와 글자가 모두 같은지 검사합니다.
	-  한 글자라도 다를 경우, s의 비교 인덱스를 줄여가면서 검사합니다.
	-  모든 글자가 같을 경우, 가장 오른쪽 패턴의 시작점 인덱스를 반환합니다.
*/

int main()
{
	char s[MAXLINE], p[MAXLINE];

	printf("전체 문자열에 입력한 패턴이 존재하면, 마지막 패턴의 첫 인덱스를 출력합니다.  \n \n");

	for (;;)
	{
		for (;;)
		{
			printf("전체 문자열을 입력하세요. : ");
			gets_s(s, MAXLINE);
			if (s[0] != '\0')
				break;
			else
				printf("문자열을 입력하지 않았습니다. 문자열을 입력해주세요. \n \n");
		}
		for (;;)
		{
			printf("찾을 문자열 패턴을 입력하세요. : ");
			gets_s(p, MAXLINE);
			if (p[0] != '\0')
				break;
			else
				printf("문자열을 입력하지 않았습니다. 문자열을 입력해주세요. \n \n");
		}

		if (strrindex2(s, p) >= 0)
		{
			printf("[strrindex2] 마지막으로 나온 패턴의 첫글자 인덱스는 %d 입니다. \n \n", strrindex2(s, p));
		}
		else
			printf("-1 \n \n");
	}

	return 0;
}