#include <stdio.h>

int main()
{
	int i, j, user, bot, n, num = 0;

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
		n = 4 - user;

		switch (n)
		{
  	 	    case 1:
			    bot = 1;
			    break;
		    case 2:
			    bot = 2;
			    break;
		    case 3:
			    bot = 3;
			    break;
		}

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