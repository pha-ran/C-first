#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int i, j, user, bot, num = 0;

	for (;;)
	{
		printf("�� ���� ���� �θ����? (3 ���Ϸ� �Է�)");
		scanf_s("%d", &user);

		if (user > 3 || user < 0)
		{
			printf("�ٽ� �Է��ϼ��� \n");
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
			printf("BOT �¸�");
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
			printf("���� �¸�");
			break;
		}
	}

	return 0;
}