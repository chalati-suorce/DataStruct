#include<stdio.h>
int main() {
	int s = 0;
	int n = 1;
	while (s < 2023)
	{
		s = n * n;
		n++;
	}
	printf("n=%d/n", n);
	return 0;
}