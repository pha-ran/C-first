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

	char *tokin2 = strtok(in2, " ");      // " " ���� ���ڸ� �������� ���ڿ��� �ڸ�, ������ ��ȯ

	while (tokin2 != NULL)               // �ڸ� ���ڿ��� ������ ���� ������ �ݺ�
	{
		tok[i] = tokin2;
		tokin2 = strtok(NULL, " ");      // ���� ���ڿ��� �߶� �����͸� ��ȯ
		i++;
	}

	for (int j = i; (i - j) < i; j--)
	{
		int f = 1;

		for (int k = 0; in1[k] != '\0'; k++)
		{
			char *chrin2 = strchr(tok[i - j], in1[k]);     // 'a'�� �����ϴ� ���ڿ� �˻�, ������ ��ȯ

			while (chrin2 != NULL)              // �˻��� ���ڿ��� ���� ������ �ݺ�
			{
				if (f == 1)
				{
					printf("%s\n", tok[i - j]);         // �˻��� ���ڿ� ���
				}
				chrin2 = strchr(chrin2 + 1, in1[k]);  // �����Ϳ� 1�� ���Ͽ� a �������� �˻�
				f = -1;
				break;
			}
		}
	}

	return 0;
}