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
	if (argc < 11) // argc의 개수 판별
	{
		printf("\n10개 이상의 숫자나 연산자를 입력하세요. \n");
		return -1;
	}

	for (int i = 1; i < argc; i++) //*argv[]가 모두 숫자나 사칙연산자인지 판별
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

		if ( ((*argv[i]) == '+') || ((*argv[i]) == '-')) //부호가 있는 정수 판별을 위해
		{
			j++;
		}

		for (; *(argv[i] + j) != '\0'; j++) //모두가 숫자인 문자열인지 판별
		{
			if (isdigit(*(argv[i] + j)) == 0)
			{
				printf("\n[  %s  ] 는 숫자 문자열이 아닙니다. 온전한 수식을 입력하세요.\n", argv[i]);
				return -1; //하나라도 숫자가 아니라면, -1을 리턴
			}
		}
	}

	for (int i = 1, j = 1; i < argc; i++) //argc가 10개 이상이며(정확히는 11개 이상) 모두 숫자나 사칙연산부호인경우
	{
		if (((*argv[i]) == '+') && ((*(argv[i] + 1)) == '\0'))
		{
			j = calculator('+');

			if (j == -1)     //숫자가 2개 미만일 경우 오류 출력
			{
				printf("\n온전한 수식이 아닙니다. \n");
				return -1;
			}

			continue;
		}
		else if (((*argv[i]) == '-') && ((*(argv[i] + 1)) == '\0'))
		{
			j = calculator('-');

			if (j == -1)     //숫자가 2개 미만일 경우 오류 출력
			{
				printf("\n온전한 수식이 아닙니다. \n");
				return -1;
			}

			continue;
		}
		else if (((*argv[i]) == '*') && ((*(argv[i] + 1)) == '\0'))
		{
			j = calculator('*');

			if (j == -1)     //숫자가 2개 미만일 경우 오류 출력
			{
				printf("\n온전한 수식이 아닙니다. \n");
				return -1;
			}

			continue;
		}
		else if (((*argv[i]) == '/') && ((*(argv[i] + 1)) == '\0'))
		{
			j = calculator('/');
			
			if (j == -1)     //숫자가 2개 미만이거나, 0으로 나눌 경우 오류 출력
			{
				printf("\n온전한 수식이 아니거나, 0으로 나눌 수 없습니다. \n");
				return -1;
			}
			continue;
		}
		else
		{
			stack[stklen] = atoi(argv[i]); //사칙연산 부호가 아닐경우 스택에 숫자를 쌓음
			stklen += 1;                   //스택의 길이 +1
		}
	}

	if (stklen == 1)
	{
		printf("\n계산 완료 : %d \n", stack[0]);
		return 0;
	}
	else
	{
		printf("\n온전한 수식이 아닙니다. \n");
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