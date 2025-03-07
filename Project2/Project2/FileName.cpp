#include<stdio.h>
void fun(int n)
{
	char c = 'A';
	if (n == 1)
		printf("%c\n", c++);
	else
	{
		printf("%c", c++);
		fun(n - 1);
	}
}
void main()
{
	int i;
	for (i = 1; i <= 4; i++)
		fun(i);
	printf("ÊäÈëÍê±Ï\n");
}