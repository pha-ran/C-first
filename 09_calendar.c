#include <stdio.h>

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

static char *dayweek[] = { "월요일", "화요일", "수요일", "목요일", "금요일", "토요일", "일요일" };

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

int main(int argc, char *argv[])
{
	if (argc == 2) //인수를 한개 입력했을때 (결과 : 해당 날짜의 요일)
	{
		for (int j = 0; *(argv[1] + j) != '\0'; j++) //입력 인수가 yyyy.mm.dd 형식의 날짜인지 판별
		{
			if (isdigit(*(argv[1] + j)) == 0) //숫자가 아닌 문자가 있으면
			{
				if ((*(argv[1] + j) == '.') && (*(argv[1] + j + 1) == '.')) //.이 두개 이상 붙어있을경우
				{
					printf("\nUsage: calendar <date1> {<date2> 또는 <days>} \n");

					return -1; //입력 오류, -1을 리턴
				}
				else if (*(argv[1] + j) == '.') //.일경우만 허용
				{
					;
				}
				else //'.'이 아닐경우
				{
					printf("\nUsage: calendar <date1> {<date2> 또는 <days>} \n");

					return -1; //입력 오류, -1을 리턴
				}
			}
		}

		int yyyy = 0, mm = 0, dd = 0, scc = 0, isy = 0, isd = 0;
		
		scc = sscanf_s(argv[1], "%d.%d.%d.%d", &yyyy, &mm, &dd, &isy); //3개의 숫자를 스캔했는지 판별하기 위해

		isd = (yyyy % 4 == 0) && (yyyy % 100 != 0) || (yyyy % 400 == 0); //입력값이 올바른 월과 일인지 판별시 윤년 판별을 위해

		if ((scc == 3) && ((yyyy > 0) && (yyyy <= 3000)) && (mm > 0) && (mm <= 12) && (dd > 0) && (dd <= daytab[isd][mm]))
		{                                                                            //스캔한 숫자가 3개이고, 년도는 1~3000이며, 올바른 날짜 표현일때
			int i = 0, s = 0, dw = 0;

			if (yyyy == 1)
			{
				s += (day_of_year(yyyy, mm, dd) - day_of_year(1, 1, 1));

				dw = s % 7;

				printf("\n[결과] %s\n", dayweek[dw]);

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

			printf("\n[결과] %s\n", dayweek[dw]);
			
			return 0;
		}
		else
		{
			printf("\nUsage: calendar <date1> {<date2> 또는 <days>} \n");

			return -1;
		}
	}
	
	//-----------------------------------------------------------------------------//
	
	if (argc == 3) //인수를 두개 입력했을때 (결과 : 경과일수 또는 경과 후 날짜)
	{
		for (int k = 1; k <= 2; k++) //두번 반복
		{
			for (int j = 0; *(argv[k] + j) != '\0'; j++) //두 입력 인수가 yyyy.mm.dd 형식의 날짜이거나 양수인지 판별
			{
				if (isdigit(*(argv[k] + j)) == 0) //숫자가 아닌 문자가 있으면
				{
					if ((*(argv[k] + j) == '.') && (*(argv[k] + j + 1) == '.')) //.이 두개 이상 붙어있을경우
					{
						printf("\nUsage: calendar <date1> {<date2> 또는 <days>} \n");

						return -1; //입력 오류, -1을 리턴
					}
					else if (*(argv[k] + j) == '.') //.일경우만 허용
					{
						;
					}
					else //'.'이 아닐경우
					{
						printf("\nUsage: calendar <date1> {<date2> 또는 <days>} \n");

						return -1; //입력 오류, -1을 리턴
					}
				}
			}
		}

		int yyyy1 = 0, mm1 = 0, dd1 = 0, scc1 = 0, isy1 = 0, isd1 = 0;
		int yyyy2 = 0, mm2 = 0, dd2 = 0, scc2 = 0, isy2 = 0, isd2 = 0;
		
		scc1 = sscanf_s(argv[1], "%d.%d.%d.%d", &yyyy1, &mm1, &dd1, &isy1); //첫번째 인수가 3개의 숫자를 스캔했는지 판별하기위해
		scc2 = sscanf_s(argv[2], "%d.%d.%d.%d", &yyyy2, &mm2, &dd2, &isy2); //두번째 인수가 1개 또는 3개의 숫자를 스캔했는지 판별하기위해

		isd1 = (yyyy1 % 4 == 0) && (yyyy1 % 100 != 0) || (yyyy1 % 400 == 0); //입력값이 올바른 월과 일인지 판별시 윤년 판별을 위해

		if (scc2 == 3) //2번째 인수가 yyyy.mm.dd 형식일때 (결과 : 두 날짜간의 경과일수)
		{
			isd2 = (yyyy2 % 4 == 0) && (yyyy2 % 100 != 0) || (yyyy2 % 400 == 0); //입력값이 올바른 월과 일인지 판별시 윤년 판별을 위해

			if ((scc1 == 3) && ((yyyy1 > 0) && (yyyy1 <= 3000)) && (mm1 > 0) && (mm1 <= 12) && (dd1 > 0) && (dd1 <= daytab[isd1][mm1]) && ((yyyy2 > 0) && (yyyy2 <= 3000)) && (mm2 > 0) && (mm2 <= 12) && (dd2 > 0) && (dd2 <= daytab[isd2][mm2]))
			{                                                        //두 인수 모두 스캔한 숫자가 3개이고, 년도는 1~3000이며, 올바른 날짜 표현일때
				int s = 0, i = 0;

				if (yyyy1 == yyyy2)
				{
					s += (day_of_year(yyyy2, mm2, dd2) - day_of_year(yyyy1, mm1, dd1));

					printf("\n[결과] 경과 일수: %d일 \n", s);

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

				printf("\n[결과] 경과 일수: %d일 \n", s);

				return 0;
			}
			else
			{
				printf("\nUsage: calendar <date1> {<date2> 또는 <days>} \n");

				return -1;
			}
		}
		else if ((scc2 == 1))  //2번째 인수가 양수일때 (결과 : 경과 날짜)
		{
			if ((scc1 == 3) && ((yyyy1 > 0) && (yyyy1 <= 3000)) && (mm1 > 0) && (mm1 <= 12) && (dd1 > 0) && (dd1 <= daytab[isd1][mm1]))
			{
				if (yyyy2 == 0)
				{
					printf("\n[결과] 경과 날짜: %d년 %d월 %d일 \n", yyyy1, mm1, dd1);

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

				if (yyyy2 > ybd) //두번째 인수가 해당 년도에 남은 일수보다 클때 (년도 계산)
				{
					yyyy2 -= ybd; //날짜 : yyyy1년 12월 31일
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

								printf("\n[결과] 경과 날짜: %d년 %d월 %d일 \n", yyyy1 + y, m, d);

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

								printf("\n[결과] 경과 날짜: %d년 %d월 %d일 \n", yyyy1 + y, m, d);

								return 0;
							}
						}
					}
				}
				else //두번째 인수가 해당 년도에 남은 일수보다 작을때 (해당 년도에서 날짜 바로 계산)
				{
					n += day_of_year(yyyy1, mm1, dd1) + yyyy2;
					month_day(yyyy1, n, &m, &d);

					printf("\n[결과] 경과 날짜: %d년 %d월 %d일 \n", yyyy1, m, d);

					return 0;
				}
			}
			else
			{
				printf("\nUsage: calendar <date1> {<date2> 또는 <days>} \n");

				return -1;
			}
		}
		else
		{
			printf("\nUsage: calendar <date1> {<date2> 또는 <days>} \n");

			return -1;
		}
	}

	else  //인수를 입력하지 않았거나 인수가 세개 이상일때
	{
		printf("\nUsage: calendar <date1> {<date2> 또는 <days>} \n");

		return -1;
	}
}

int day_of_year(int year, int month, int day) //해당 날짜 전 월들의 일수를 입력한 일수에 더함 (2월 14일 : 1월의 일수 31 + 14일 이므로 45)
{
	int i, leap;

	leap = (year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0);

	for (i = 1; i < month; i++)
		day += daytab[leap][i];

	return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) //해당 년도 1월 1일에서 두번째 인수만큼 지난 날짜의 달과 일을 구함(1988,60 : 윤년이므로 2월 29일)
{                                                             //두번째 인자가 x월의 일수보다 적을 때 까지 그 달의 일수만큼을 두번째 인자에서 빼면서 계산
	int i, leap;

	leap = (year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0);

	for (i = 1; yearday > daytab[leap][i]; i++)
		yearday -= daytab[leap][i];

	*pmonth = i;
	*pday = yearday;
}