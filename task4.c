#include <stdio.h>

int main(void)
{
	printf("please input a 4 digit number");
	int number;
	float reversed[4];
	int tmp;

	scanf("%d", &number);

	reversed[3] = number / 1000;
	number = number % 1000;

	reversed[2] = number / 100;
	number = number % 100;

	reversed[1] = number / 10;
	number = number % 10;

	reversed[0] = number;

	printf("%.0f%.0f%.0f%.0f", reversed[0], reversed[1], reversed[2], reversed[3]);

	return 0;
}

