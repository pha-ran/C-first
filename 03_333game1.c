#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int i, j, user, bot, num = 0;

	for (;;)
	{
		printf("몇 개의 수를 부를까요? (3 이하로 입력)");
		scanf_s("%d", &user);

		if (user > 3 || user < 0)
		{
			printf("다시 입력하세요 \n");
			continue;
		}
			
		j = num;

		for (i = j + 1; i <= user + j; i++)
		{
			printf("%d ", i);
			num++;
			if (num >= 33)
				break;
		}
		printf("\n");

		if (num >= 33)
		{
			printf("BOT 승리");
			break;
		}

		j = num;

		srand(time(NULL));
		bot = rand() % 3 + 1;
	
		printf("BOT : %d \n", bot);

		for (i = j + 1; i <= (bot + j); i++)
		{
			printf("%d ", i);
			num++;
			if (num >= 33)
				break;
		}
		printf("\n");

		if (num >= 33)
		{
			printf("유저 승리");
			break;
		}
	}

	return 0;
}