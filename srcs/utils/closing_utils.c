# include "../../includes/fdf.h"

int close_program(t_fdf *p_fdf, char *strerr)
{
	ft_printf("main : close_program\n");//
	
	if (!p_fdf->mlx)
		exit_error(strerr);
	clean_close_imgstruct(p_fdf->s_last_img);
	clean_close_imgstruct(p_fdf, p_fdf->s_new_img);
	clean_close_window(p_fdf->mlx, p_fdf->win);
    free_map_elem2(&(p_fdf->map)); // liberer + NULL t_map_elem
    mlx_destroy_display(p_fdf->mlx);
    free(p_fdf->mlx);
	if(strerr)
		exit_error(strerr);
    return(EXIT_SUCCESS);
}

void	clean_close_imgstruct(t_fdf *p_fdf, t_imgstruct *p_imgtoclear)
{
	//free les elems qui doivent l'etre ?
	if (p_imgtoclear->p_img_pixels) //voir s' il est necessaire de liberer les elems obtenus par mlx_get_data_address
		free(p_imgtoclear->p_img_pixels); 
	if (p_imgtoclear->img_mlx)
		mlx_destroy_image(p_fdf->mlx, p_imgtoclear->img_mlx);
}

void	clean_close_window(t_fdf *p_fdf, void *p_win)
{
	//free les elems qui doivent l'etre ?
	if (p_win)
		mlx_destroy_window(p_fdf->mlx, p_win);
}