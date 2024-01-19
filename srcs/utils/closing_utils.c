# include "../../includes/fdf.h"

int close_program(t_fdf *p_fdf, char *strerr)
{
	ft_printf("closing_utils : close_program\n");//
	if (!p_fdf->mlx)
		exit_error(strerr);
	clean_close_imgstruct(p_fdf, &(p_fdf->s_img_to_del));
	clean_close_imgstruct(p_fdf, &(p_fdf->s_new_img));
	// if (p_fdf->s_img_to_del.img_mlx)
	// 	mlx_destroy_image(p_fdf->mlx, p_fdf->s_img_to_del.img_mlx);
	// if (p_fdf->s_new_img.img_mlx)
	// 	mlx_destroy_image(p_fdf->mlx, p_fdf->s_new_img.img_mlx);
	if (&(p_fdf->win))
		mlx_destroy_window(p_fdf->mlx, p_fdf->win);
	free_map_elem2(&(p_fdf->map));
    mlx_destroy_display(p_fdf->mlx);
    free(p_fdf->mlx);
	if(strerr)
		exit_error(strerr);
    exit(EXIT_SUCCESS);
}

void	clean_close_imgstruct(t_fdf *p_fdf, t_imgstruct *p_img)
{
	ft_printf("closing_utils : close_imgstruct\n");//
	//pas necessaie de free p_img pixels
	
	if (p_img->img_mlx)
		mlx_destroy_image(p_fdf->mlx, p_img->img_mlx);
	p_img->img_mlx = NULL;
}
