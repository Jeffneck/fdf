# include "../../includes/fdf.h"
//tant que le nombre est dans la base


int	strhexa_to_colorint(char *strhexa)
{
	int		i;

	i = 2; 
	if(!strhexa)
		return (0xFFFFFFFF); //si pas de couleur de base on choisit blanc par defaut, valide le code hexa
	if (strncmp("0x", strhexa, 2) != 0)
		exit_error("Bad format for color");
	while(strhexa[i] && strhexa[i] != ' ')
	{
		if (strhexa[i] >= 'a' && strhexa[i] <= 'f')
			strhexa[i] -= 32;
		i++;
	}
	return (ft_atoi_base(&strhexa[2], "0123456789ABCDEF", 16)); //atoi avance a l' infini ou s' arrete tt seul ?
}

t_argb create_argb(int color)
{
	t_argb argb;
	int	mask;

	mask = 0xFF;

	argb.a = (unsigned char) (color >> 24) & mask;
	argb.r = (unsigned char) (color >> 16) & mask;
	argb.g = (unsigned char) (color >> 8) & mask;
	argb.b = (unsigned char) color & mask;
	return (argb);git 
}

int		create_color_gradient(float delta, t_argb color1, t_argb color2)
{
	t_argb new_c;
	int		color_int;

	new_c.a = (1 - delta) * color1.a + delta * color2.a; 
	new_c.r = (1 - delta) * color1.r + delta * color2.r; 
	new_c.g = (1 - delta) * color1.g + delta * color2.g; 
	new_c.b = (1 - delta) * color1.b + delta * color2.b; 
	color_int = (new_c.a << 24) + (new_c.r << 16) + (new_c.g << 8) + new_c.b; 
	return (color_int);
}

int		process_color(int curr_steps, int tot_steps, int color_ini, int color_end)
{
	// ft_printf("color : process_color curr_steps = %d tot_steps = %d int color_ini = %d  int color_end%d\n", curr_steps, tot_steps, color_ini, color_end);//test
	float	delta;
	int c_processed; 
	// if (tot_steps != 0)
	delta = (float) curr_steps / tot_steps; 
	// else
	// 	delta = curr_steps / (tot_steps + 1);
	c_processed = create_color_gradient(delta, 
		create_argb(color_ini), 
		create_argb(color_end));
	// printf("delta = %f color after process%d\n", delta, c_processed);//test
	return (c_processed);
}


// int		create_color_gradient(int a, int b, int color_begin, int color_end)
// {
// 	int		gradient;
// 	int		color_gradient;

// 	if (b != 0)
// 		gradient = a / b;
// 	else
// 		gradient = a / (b + 1);
//     // Gérer la division par zéro, par exemple, en retournant une valeur par défaut ou en générant une erreur.
// 	// ft_printf("Avant color gradient"); //

// 	if (color_end != 0)
// 		color_gradient = color_begin + (color_begin / color_end) * gradient;
// 	else
// 		color_gradient = color_begin + (color_begin / (color_end + 1)) * gradient;
	
// 	ft_printf("color begin = %d color end = %d color gradient = %d", color_begin, color_end, color_gradient);
// 	return (color_gradient);
// }