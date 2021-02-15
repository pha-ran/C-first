#include <stdio.h>

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

static char *dayweek[] = { "������", "ȭ����", "������", "�����", "�ݿ���", "�����", "�Ͽ���" };

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

int main(int argc, char *argv[])
{
	if (argc == 2) //�μ��� �Ѱ� �Է������� (��� : �ش� ��¥�� ����)
	{
		for (int j = 0; *(argv[1] + j) != '\0'; j++) //�Է� �μ��� yyyy.mm.dd ������ ��¥���� �Ǻ�
		{
			if (isdigit(*(argv[1] + j)) == 0) //���ڰ� �ƴ� ���ڰ� ������
			{
				if ((*(argv[1] + j) == '.') && (*(argv[1] + j + 1) == '.')) //.�� �ΰ� �̻� �پ��������
				{
					printf("\nUsage: calendar <date1> {<date2> �Ǵ� <days>} \n");

					return -1; //�Է� ����, -1�� ����
				}
				else if (*(argv[1] + j) == '.') //.�ϰ�츸 ���
				{
					;
				}
				else //'.'�� �ƴҰ��
				{
					printf("\nUsage: calendar <date1> {<date2> �Ǵ� <days>} \n");

					return -1; //�Է� ����, -1�� ����
				}
			}
		}

		int yyyy = 0, mm = 0, dd = 0, scc = 0, isy = 0, isd = 0;
		
		scc = sscanf_s(argv[1], "%d.%d.%d.%d", &yyyy, &mm, &dd, &isy); //3���� ���ڸ� ��ĵ�ߴ��� �Ǻ��ϱ� ����

		isd = (yyyy % 4 == 0) && (yyyy % 100 != 0) || (yyyy % 400 == 0); //�Է°��� �ùٸ� ���� ������ �Ǻ��� ���� �Ǻ��� ����

		if ((scc == 3) && ((yyyy > 0) && (yyyy <= 3000)) && (mm > 0) && (mm <= 12) && (dd > 0) && (dd <= daytab[isd][mm]))
		{                                                                            //��ĵ�� ���ڰ� 3���̰�, �⵵�� 1~3000�̸�, �ùٸ� ��¥ ǥ���϶�
			int i = 0, s = 0, dw = 0;

			if (yyyy == 1)
			{
				s += (day_of_year(yyyy, mm, dd) - day_of_year(1, 1, 1));

				dw = s % 7;

				printf("\n[���] %s\n", dayweek[dw]);

				return 0;
			}

			s += 364;

			for (i = 2; i < yyyy; i++)
			{
				if ((i % 4 == 0) && (i % 100 != 0) || (i % 400 == 0))
					s += 366;
				else
					s += 365;
			}

			s += day_of_year(yyyy, mm, dd);

			dw = s % 7;

			printf("\n[���] %s\n", dayweek[dw]);
			
			return 0;
		}
		else
		{
			printf("\nUsage: calendar <date1> {<date2> �Ǵ� <days>} \n");

			return -1;
		}
	}
	
	//-----------------------------------------------------------------------------//
	
	if (argc == 3) //�μ��� �ΰ� �Է������� (��� : ����ϼ� �Ǵ� ��� �� ��¥)
	{
		for (int k = 1; k <= 2; k++) //�ι� �ݺ�
		{
			for (int j = 0; *(argv[k] + j) != '\0'; j++) //�� �Է� �μ��� yyyy.mm.dd ������ ��¥�̰ų� ������� �Ǻ�
			{
				if (isdigit(*(argv[k] + j)) == 0) //���ڰ� �ƴ� ���ڰ� ������
				{
					if ((*(argv[k] + j) == '.') && (*(argv[k] + j + 1) == '.')) //.�� �ΰ� �̻� �پ��������
					{
						printf("\nUsage: calendar <date1> {<date2> �Ǵ� <days>} \n");

						return -1; //�Է� ����, -1�� ����
					}
					else if (*(argv[k] + j) == '.') //.�ϰ�츸 ���
					{
						;
					}
					else //'.'�� �ƴҰ��
					{
						printf("\nUsage: calendar <date1> {<date2> �Ǵ� <days>} \n");

						return -1; //�Է� ����, -1�� ����
					}
				}
			}
		}

		int yyyy1 = 0, mm1 = 0, dd1 = 0, scc1 = 0, isy1 = 0, isd1 = 0;
		int yyyy2 = 0, mm2 = 0, dd2 = 0, scc2 = 0, isy2 = 0, isd2 = 0;
		
		scc1 = sscanf_s(argv[1], "%d.%d.%d.%d", &yyyy1, &mm1, &dd1, &isy1); //ù��° �μ��� 3���� ���ڸ� ��ĵ�ߴ��� �Ǻ��ϱ�����
		scc2 = sscanf_s(argv[2], "%d.%d.%d.%d", &yyyy2, &mm2, &dd2, &isy2); //�ι�° �μ��� 1�� �Ǵ� 3���� ���ڸ� ��ĵ�ߴ��� �Ǻ��ϱ�����

		isd1 = (yyyy1 % 4 == 0) && (yyyy1 % 100 != 0) || (yyyy1 % 400 == 0); //�Է°��� �ùٸ� ���� ������ �Ǻ��� ���� �Ǻ��� ����

		if (scc2 == 3) //2��° �μ��� yyyy.mm.dd �����϶� (��� : �� ��¥���� ����ϼ�)
		{
			isd2 = (yyyy2 % 4 == 0) && (yyyy2 % 100 != 0) || (yyyy2 % 400 == 0); //�Է°��� �ùٸ� ���� ������ �Ǻ��� ���� �Ǻ��� ����

			if ((scc1 == 3) && ((yyyy1 > 0) && (yyyy1 <= 3000)) && (mm1 > 0) && (mm1 <= 12) && (dd1 > 0) && (dd1 <= daytab[isd1][mm1]) && ((yyyy2 > 0) && (yyyy2 <= 3000)) && (mm2 > 0) && (mm2 <= 12) && (dd2 > 0) && (dd2 <= daytab[isd2][mm2]))
			{                                                        //�� �μ� ��� ��ĵ�� ���ڰ� 3���̰�, �⵵�� 1~3000�̸�, �ùٸ� ��¥ ǥ���϶�
				int s = 0, i = 0;

				if (yyyy1 == yyyy2)
				{
					s += (day_of_year(yyyy2, mm2, dd2) - day_of_year(yyyy1, mm1, dd1));

					printf("\n[���] ��� �ϼ�: %d�� \n", s);

					return 0;
				}

				if ((yyyy1 % 4 == 0) && (yyyy1 % 100 != 0) || (yyyy1 % 400 == 0))
					s += (366 - day_of_year(yyyy1, mm1, dd1));
				else
					s += (365 - day_of_year(yyyy1, mm1, dd1));

				for (i = yyyy1 + 1; i < yyyy2; i++)
				{
					if ((i % 4 == 0) && (i % 100 != 0) || (i % 400 == 0))
						s += 366;
					else
						s += 365;
				}

				s += day_of_year(yyyy2, mm2, dd2);

				printf("\n[���] ��� �ϼ�: %d�� \n", s);

				return 0;
			}
			else
			{
				printf("\nUsage: calendar <date1> {<date2> �Ǵ� <days>} \n");

				return -1;
			}
		}
		else if ((scc2 == 1))  //2��° �μ��� ����϶� (��� : ��� ��¥)
		{
			if ((scc1 == 3) && ((yyyy1 > 0) && (yyyy1 <= 3000)) && (mm1 > 0) && (mm1 <= 12) && (dd1 > 0) && (dd1 <= daytab[isd1][mm1]))
			{
				if (yyyy2 == 0)
				{
					printf("\n[���] ��� ��¥: %d�� %d�� %d�� \n", yyyy1, mm1, dd1);

					return 0;
				}

				int y = 0, m = 0, d = 0, yad = 0, ybd = 0, n = 0;

				if ((yyyy1 % 4 == 0) && (yyyy1 % 100 != 0) || (yyyy1 % 400 == 0))
				{
					yad += 366;
				}
				else
				{
					yad += 365;
				}

				ybd = yad - day_of_year(yyyy1, mm1, dd1);

				if (yyyy2 > ybd) //�ι�° �μ��� �ش� �⵵�� ���� �ϼ����� Ŭ�� (�⵵ ���)
				{
					yyyy2 -= ybd; //��¥ : yyyy1�� 12�� 31��
					y += 1;

					while (1)
					{
						if ( ((yyyy1 + y) % 4 == 0) && ((yyyy1 + y) % 100 != 0) || ((yyyy1 + y) % 400 == 0) )
						{
							if (yyyy2 > 366)
							{
								yyyy2 -= 366;
								y += 1;
							}
							else
							{
								month_day(yyyy1 + y, yyyy2, &m, &d);

								printf("\n[���] ��� ��¥: %d�� %d�� %d�� \n", yyyy1 + y, m, d);

								return 0;
							}
						}
						else
						{
							if (yyyy2 > 365)
							{
								yyyy2 -= 365;
								y += 1;
							}
							else
							{
								month_day(yyyy1 + y, yyyy2, &m, &d);

								printf("\n[���] ��� ��¥: %d�� %d�� %d�� \n", yyyy1 + y, m, d);

								return 0;
							}
						}
					}
				}
				else //�ι�° �μ��� �ش� �⵵�� ���� �ϼ����� ������ (�ش� �⵵���� ��¥ �ٷ� ���)
				{
					n += day_of_year(yyyy1, mm1, dd1) + yyyy2;
					month_day(yyyy1, n, &m, &d);

					printf("\n[���] ��� ��¥: %d�� %d�� %d�� \n", yyyy1, m, d);

					return 0;
				}
			}
			else
			{
				printf("\nUsage: calendar <date1> {<date2> �Ǵ� <days>} \n");

				return -1;
			}
		}
		else
		{
			printf("\nUsage: calendar <date1> {<date2> �Ǵ� <days>} \n");

			return -1;
		}
	}

	else  //�μ��� �Է����� �ʾҰų� �μ��� ���� �̻��϶�
	{
		printf("\nUsage: calendar <date1> {<date2> �Ǵ� <days>} \n");

		return -1;
	}
}

int day_of_year(int year, int month, int day) //�ش� ��¥ �� ������ �ϼ��� �Է��� �ϼ��� ���� (2�� 14�� : 1���� �ϼ� 31 + 14�� �̹Ƿ� 45)
{
	int i, leap;

	leap = (year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0);

	for (i = 1; i < month; i++)
		day += daytab[leap][i];

	return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) //�ش� �⵵ 1�� 1�Ͽ��� �ι�° �μ���ŭ ���� ��¥�� �ް� ���� ����(1988,60 : �����̹Ƿ� 2�� 29��)
{                                                             //�ι�° ���ڰ� x���� �ϼ����� ���� �� ���� �� ���� �ϼ���ŭ�� �ι�° ���ڿ��� ���鼭 ���
	int i, leap;

	leap = (year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0);

	for (i = 1; yearday > daytab[leap][i]; i++)
		yearday -= daytab[leap][i];

	*pmonth = i;
	*pday = yearday;
}