#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main()
{
	char in1[100], in2[100];
	char *tok[100];
	int i = 0;

	FILE *fp1 = fopen("in1.txt", "r");
	fgets(in1, sizeof(in1), fp1);
	fclose(fp1);

	FILE *fp2 = fopen("in2.txt", "r");
	fgets(in2, sizeof(in2), fp2);
	fclose(fp2);

	char *tokin2 = strtok(in2, " ");      // " " 공백 문자를 기준으로 문자열을 자름, 포인터 반환

	while (tokin2 != NULL)               // 자른 문자열이 나오지 않을 때까지 반복
	{
		tok[i] = tokin2;
		tokin2 = strtok(NULL, " ");      // 다음 문자열을 잘라서 포인터를 반환
		i++;
	}

	for (int j = i; (i - j) < i; j--)
	{
		int f = 1;

		for (int k = 0; in1[k] != '\0'; k++)
		{
			char *chrin2 = strchr(tok[i - j], in1[k]);     // 'a'로 시작하는 문자열 검색, 포인터 반환

			while (chrin2 != NULL)              // 검색된 문자열이 없을 때까지 반복
			{
				if (f == 1)
				{
					printf("%s\n", tok[i - j]);         // 검색된 문자열 출력
				}
				chrin2 = strchr(chrin2 + 1, in1[k]);  // 포인터에 1을 더하여 a 다음부터 검색
				f = -1;
				break;
			}
		}
	}

	return 0;
}