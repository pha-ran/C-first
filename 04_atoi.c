#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int char_len(char s[])  //���ڿ��� ���̸� ���� ('\0'�� ����)
{
	int i;

	for (i = 0; s[i] != '\0'; i++)
		;

	return i - 1;
}

int int_or_not(char s[])  //���ڿ��� ������ �������� �Ǵ� F = 0, T = 1
{
	int i, j;

	if ( (s[0] == '\0') || ( (char_len(s) + 1 == 1) && (s[0] == '-') ) )  //�Է°��� �����̰ų� '-' �ϰ�� False
		return 0;

	for (i = char_len(s), j = 0; i >= 0; i--)
	{
		if (isdigit(s[i]))
			;
		//printf("T");  //������
		else
		{
			j += 1;  //���ڰ� �ƴҰ�� J�� ������Ŵ
			//printf("F");	//������
		}
	}

	if (s[0] == '-')  //���� ���� ó��
		j -= 1;

	if (j == 0)
		return 1;
	else
		return 0;
}

int atoi (char s[])  //���ڿ��� ������ ��ȯ
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

	printf("���ڿ��� �Է��ϼ���. ������ ���, ������ ��ȯ�մϴ�. : ");
	
	gets_s(a, 10);
	
	//scanf_s("%s", a, 12);  //���� ���� ������ ���� ����. gets_s�� ����

	printf("��� (-2147483648�� ��� ����) : %d \n", atoi(a));

	return 0;
}