#include <stdio.h>
#define PI 3.141


int main(void)
{

	float radius;
	float surface_area;
	float volume;
	printf("What is the radius?");
	scanf("%f", &radius);
	surface_area = radius * PI * 4;
	volume = 4/3*PI*radius * radius * radius;

	printf("The surface area is %.2f and the volume is %.2f", surface_area, volume);
	

	return 0;
}
