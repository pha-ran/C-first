#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 1000

int stack[MAX], stklen = 0;

void push(int i);
int pop();
int calculator(char c);

int main(int argc, char *argv[])
{
	if (argc < 11) // argc�� ���� �Ǻ�
	{
		printf("\n10�� �̻��� ���ڳ� �����ڸ� �Է��ϼ���. \n");
		return -1;
	}

	for (int i = 1; i < argc; i++) //*argv[]�� ��� ���ڳ� ��Ģ���������� �Ǻ�
	{
		int j = 0;

		if ( ( (*argv[i]) == '+' ) && ( (*(argv[i] + 1) ) == '\0') )
		{
			continue;
		}
		if (((*argv[i]) == '-') && ((*(argv[i] + 1)) == '\0'))
		{
			continue;
		}
		if (((*argv[i]) == '*') && ((*(argv[i] + 1)) == '\0'))
		{
			continue;
		}
		if (((*argv[i]) == '/') && ((*(argv[i] + 1)) == '\0'))
		{
			continue;
		}

		if ( ((*argv[i]) == '+') || ((*argv[i]) == '-')) //��ȣ�� �ִ� ���� �Ǻ��� ����
		{
			j++;
		}

		for (; *(argv[i] + j) != '\0'; j++) //��ΰ� ������ ���ڿ����� �Ǻ�
		{
			if (isdigit(*(argv[i] + j)) == 0)
			{
				printf("\n[  %s  ] �� ���� ���ڿ��� �ƴմϴ�. ������ ������ �Է��ϼ���.\n", argv[i]);
				return -1; //�ϳ��� ���ڰ� �ƴ϶��, -1�� ����
			}
		}
	}

	for (int i = 1, j = 1; i < argc; i++) //argc�� 10�� �̻��̸�(��Ȯ���� 11�� �̻�) ��� ���ڳ� ��Ģ�����ȣ�ΰ��
	{
		if (((*argv[i]) == '+') && ((*(argv[i] + 1)) == '\0'))
		{
			j = calculator('+');

			if (j == -1)     //���ڰ� 2�� �̸��� ��� ���� ���
			{
				printf("\n������ ������ �ƴմϴ�. \n");
				return -1;
			}

			continue;
		}
		else if (((*argv[i]) == '-') && ((*(argv[i] + 1)) == '\0'))
		{
			j = calculator('-');

			if (j == -1)     //���ڰ� 2�� �̸��� ��� ���� ���
			{
				printf("\n������ ������ �ƴմϴ�. \n");
				return -1;
			}

			continue;
		}
		else if (((*argv[i]) == '*') && ((*(argv[i] + 1)) == '\0'))
		{
			j = calculator('*');

			if (j == -1)     //���ڰ� 2�� �̸��� ��� ���� ���
			{
				printf("\n������ ������ �ƴմϴ�. \n");
				return -1;
			}

			continue;
		}
		else if (((*argv[i]) == '/') && ((*(argv[i] + 1)) == '\0'))
		{
			j = calculator('/');
			
			if (j == -1)     //���ڰ� 2�� �̸��̰ų�, 0���� ���� ��� ���� ���
			{
				printf("\n������ ������ �ƴϰų�, 0���� ���� �� �����ϴ�. \n");
				return -1;
			}
			continue;
		}
		else
		{
			stack[stklen] = atoi(argv[i]); //��Ģ���� ��ȣ�� �ƴҰ�� ���ÿ� ���ڸ� ����
			stklen += 1;                   //������ ���� +1
		}
	}

	if (stklen == 1)
	{
		printf("\n��� �Ϸ� : %d \n", stack[0]);
		return 0;
	}
	else
	{
		printf("\n������ ������ �ƴմϴ�. \n");
		return -1;
	}
}

void push(int i)
{
	stack[stklen] = i;
	stklen += 1;
}

int pop()
{
	int p;

	p = stack[stklen - 1];
	stklen -= 1;

	return p;
}

int calculator(char s)
{
	int c1 = 0, c2 = 0, r = 0;

	if (stklen >= 2)
	{
		c2 = pop();
		c1 = pop();

		switch (s)
		{
		case '+':
			r = c1 + c2;
			push(r);
			break;
		case '-':
			r = c1 - c2;
			push(r);
			break;
		case '*':
			r = c1 * c2;
			push(r);
			break;
		case '/':
			if (c2 == 0)
			{
				return -1;
			}
			r = c1 / c2;
			push(r);
			break;
		}
		
		return 0;
	}
	else
	{
		return -1;
	}
}