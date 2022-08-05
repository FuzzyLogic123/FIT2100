#include <stdio.h>

void add(int num1, int num2);
void subtract(int num1, int num2);
void multiply(int num1, int num2);
void divide(int num1, int num2);


int main(void)
{
	int a;
	int b;
	printf("Enter two integers");
	scanf("%d %d", &a, &b);
	add(a, b);
	subtract(a, b);
	multiply(a, b);
	divide(a, b);

	return 0;
}

void add(int num1, int num2)
{
	int result = num1 + num2;
	printf("%d added by %d is: %d\n",num1, num2, result);
}

void subtract(int num1, int num2)
{
	int result = num1 - num2;
	printf("%d subtracted by %d is: %d\n",num1, num2, result);
}

void multiply(int num1, int num2)
{
	int result = num1 * num2;
	printf("%d multipied by %d is: %d\n",num1, num2, result);
}

void divide(int num1, int num2)
{
	float result = num1 / (float) num2;
	printf("%d divided by %d is: %.2f\n",num1, num2, result);
}

