#include <stdio.h>
#include <limits.h>

char *itobs(int n, char *ps);
void show_bstr(const char * str);
int invert_end(int num, int bits);

int main(void)
{
	char bin_str[CHAR_BIT * sizeof(int) + 1];
	int number;
	puts("Enter integers and see them in binary.");
	puts("Non-numeric input terminates program.");
	
	while (scanf("%d", &number) == 1)
	{
		printf("%d is:", number);
		show_bstr(itobs(number, bin_str));
		putchar('\n');

		/* new add */
		number = invert_end(number, 4);
		printf("Inverting the last 4 bits gives\n");
		show_bstr(itobs(number, bin_str));
		putchar('\n');


	}

	puts("Bye!");
	return 0;
}

char *itobs(int n, char *ps)
{
	int i;
	const static int size = CHAR_BIT * sizeof(int);

	for (i = size - 1; i >= 0; i--, n >>= 1)
		ps[i] = (01 & n) + '0';
	ps[size] = '\0';

	return ps;
}

void show_bstr(const char *str)
{
	int i = 0;
	while (str[i])
	{
		putchar(str[i]);
		if (++i % 4 == 0 && str[i])
			putchar(' ');
	}
}

/* 打开mask的后n位 */
int invert_end(int num, int bits)
{
	int mask = 0;
	int bitval = 1;
	while (bits-- > 0)
	{
		mask |= bitval;
		bitval <<= 1;
	}
	
	/* 将num的后n位切换 */
	return num ^ mask;
}
