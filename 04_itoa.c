#include <stdio.h>
#include <ctype.h>

int int_len(int n)  //������ (���ڿ��� ��ȯ���� ��쿡) ������ �ε����� ��ȯ
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

	if (n < 0)  //������ ó��
	{
		s[start++] = '-'; //�ε��� 0�� -����
		n *= -1;         //n�� ����� �ٲ㼭 ó��
		end += 1;         //- �� �� ���� �߰�
	}

	s[end + 1] = '\0'; //���ڿ��� �� ó��

	for (i = n; end >= start; i /= 10)
	{
		s[end--] = (i % 10) + '0';
	}
}

int main()
{
	int a;
	char s[10];

	printf("������ �Է��ϼ���. ���ڿ��� ��ȯ�մϴ�. : ");
	scanf_s("%d", &a);
	itoa(a, s);
	printf("��ȯ ��� : %s \n", s);

	return 0;
}