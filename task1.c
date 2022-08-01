#include <stdio.h>


int main(void)
{

	char first_name[20];
	char last_name[20];
	printf("Enter your first name:\n");
	scanf("%s", first_name);
	printf("Enter your last name:\n");
	scanf("%s", last_name);

	printf("%c%c\n", first_name[0], last_name[0]);

	return 0;
}
