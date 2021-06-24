# include <stdio.h>

#include <stdlib.h>
#include <unistd.h>
void	ft_put_nbr(int num)
{
	int		base;
	char	c;

	base = 10;
	while (num >= base)
	{
		base *= 10;
	}
	base /= 10;
	while (base)
	{
		c =  (num / base) + '0';
		write(1, &c, 1);
		num = num % base;
		base /= 10;
	}
}

int main(int argc, char const *argv[])
{
    int k = 0;
    for (int i = 0; i < 500; i++)
    {
        ft_put_nbr(i);
        printf("\n");
    }
    printf("done %d\n", k);
    return 0;
}
