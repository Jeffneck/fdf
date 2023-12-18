# include "../../includes/fdf.h"
int pos_in_base(char c, char *base)
{
	int	i; 

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
	size_t			i;
	int			pos;
	long long	nbr;
	int			sign;

	i = 0;
	nbr = 0;
	sign = 1;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && (nptr[i] <= 13)))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	pos = pos_in_base(nptr[i], base);
	while (pos_in_base >= 0)
	{
		nbr = nbr * size_base + pos;
		i++;
		pos = pos_in_base(nptr[i], base);
	}
	return ((int)(nbr * sign));
}

//tant que le nombre est dans la base


int	strhexa_to_colorint(char *strhexa)
{
	if(!strhexa)
		return (0xFFFFFFFF); //si pas de couleur de base on choisit blanc par defaut, valide le code hexa
	//return (0xFFFFFFFF); //test
	if (strncmp("0x", strhexa, 2) != 0) //en comparant 2 char il est possible d' acceder a une zone memoire interdite
		exit_error("Bad format for color");
	return (ft_atoi(strhexa + 2)); //atoi avance a l' infini ou s' arrete tt seul ?
}

int		create_color_gradient(int a, int b, int color_begin, int color_end)
{
	int		gradient;
	int		color_gradient;

	if (b != 0)
		gradient = a / b;
	else
		gradient = a / (b + 1);
    // Gérer la division par zéro, par exemple, en retournant une valeur par défaut ou en générant une erreur.
	// ft_printf("Avant color gradient"); //

	if (color_end != 0)
		color_gradient = color_begin + (color_begin / color_end) * gradient;
	else
		color_gradient = color_begin + (color_begin / (color_end + 1)) * gradient;
	
	// ft_printf("Apres color gradient"); //
	return (color_gradient);
}