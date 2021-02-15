#include <stdio.h>
#include <stdlib.h>

int *createIntArray(int row, int column);

int main()
{
	int x, y, i;
	int *Arr;
	int (*B)[5];

	x = 4;
	y = 5;

	Arr = createIntArray(x, y);
	B = Arr;

	for (i = 0; i < (x * y); i++)//Arr에 값 대입
		*(Arr + i) = i;

	printf("A는 : ");

	for (i = 0; i < (x * y); i++)
		printf("%d ", *(Arr + i));

	printf("\n");

	/*
	free(Arr);

	for (i = 0; i < (x * y); i++)
		printf("%d ", *(Arr + i));
	*/

	printf("B는 : ");

	for (i = 0; i < (x * y); i++)
		printf("%d ", B[i/5][i%5]);

	printf("\n\n");

	Arr[6] = 100;
	B[2][2] = 200;

	for (i = 0; i < (x * y); i++)
		printf("B : %d(%p)     A : %d(%p) \n", B[i / 5][i % 5], &(B[i / 5][i % 5]), Arr[i], Arr + i);

	return 0;
}

int *createIntArray(int row, int column)
{
	int *A = (int*) malloc (sizeof(int) * row * column);

	return A;
}