#include <stdio.h>

int pos_in_base(char c, char *base)
{
	int	i;

    i = 0;
	while(base[i])
	{
		if (c == base[i])
			return (i);
		i++;
	}
	return (-1);
}

int	ft_atoi_base(const char *nptr, char *base, int size_base)
{
	int			i;
	int			pos;
	long long	nbr;
	int			sign;

	i = 0;
	nbr = 0;
	sign = 1;
	if (nptr == NULL)
		return (0);
	while (nptr[i] == ' ' || (nptr[i] >= 9 && (nptr[i] <= 13)))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	while (nptr[i])
    {
        pos = pos_in_base(nptr[i], base);
        if (pos < 0)
            return ((int)(nbr * sign));
        nbr *= size_base;
        nbr += pos;
        i++;
    }
	return ((int)(nbr * sign));
}

int main (int argc, char **argv)
{
    printf("%d\n", ft_atoi_base(argv[1], "0123456789abcdef", 16));
    return(argc);
}