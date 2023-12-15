# include "../../includes/fdf.h"

int	strhexa_to_colorint(char *strhexa)
{
	if(!strhexa)
		return (0xFFFFFFFF); //si pas de couleur de base on choisit blanc par defaut, valide le code hexa
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