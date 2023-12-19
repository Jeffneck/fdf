# include "../../includes/fdf.h"

int close_program(t_fdf *p_fdf, char *strerr)
{
	ft_printf("closing_utils : close_program\n");//
	if (!p_fdf->mlx)
		exit_error(strerr);
	if (&(p_fdf->s_img_to_del))
	{
		ft_printf("closing_utils : close_program\n");//
		clean_close_imgstruct(p_fdf, &(p_fdf->s_img_to_del)); //attention segfault on dirait que l' img a deja ete close avant d' arriver ici
	}
	if (&(p_fdf->s_new_img))
		clean_close_imgstruct(p_fdf, &(p_fdf->s_new_img));//logiquement devrait rester
	// if (&(p_fdf->s_new_img))
	// 	clean_close_window(p_fdf->mlx, p_fdf->win); //necessaire mais cree une segfault 
	free_map_elem2(&(p_fdf->map)); // liberer + NULL t_map_elem
	mlx_loop_end(p_fdf->mlx);//test
    mlx_destroy_display(p_fdf->mlx);
    free(p_fdf->mlx);
	free(p_fdf);
	if(strerr)
		exit_error(strerr);
    exit(EXIT_SUCCESS);
	// return (1);
}

void	clean_close_imgstruct(t_fdf *p_fdf, t_imgstruct *p_img)
{
	ft_printf("closing_utils : close_imgstruct\n");//
	//pas necessaie de free p_img pixels
	
	if (p_img->img_mlx)
		mlx_destroy_image(p_fdf->mlx, p_img->img_mlx);
	//free(p_img);//erreur ?
	p_img = NULL;
}

void	clean_close_window(t_fdf *p_fdf, void *p_win)
{
	ft_printf("closing_utils : close_windows\n");//
	//free les elems qui doivent l'etre ?
	if (p_win)
		mlx_destroy_window(p_fdf->mlx, p_win);
}