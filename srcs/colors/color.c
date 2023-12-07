# include "../../includes/fdf.h"

int	strhexa_to_colorint(char *strhexa)
{
	if(!strhexa)
		return (427819035); //si pas de couleur de base on choisit blanc par defaut, valide le code hexa
	if (strncmp("0x", strhexa, 2) != 0) //en comparant 2 char il est possible d' acceder a une zone memoire interdite
		exit_error("Bad format for color");
	return (ft_atoi(strhexa + 2)); //atoi avance a l' infini ou s' arrete tt seul ?
}