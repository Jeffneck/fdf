# include "../../includes/fdf.h"

int	manage_keyhook(int keysym, t_fdf *p_fdf)
{
	ft_printf("hooks : manage_keyhook KEYSYM = %d \n", keysym);//
	if (keysym == XK_Escape)
        close_hook(p_fdf); //exit ou return erreur ?
	if (keysym == XK_Left || keysym == XK_Right || keysym == XK_Up || keysym == XK_Down)
		rotation_hook(keysym, p_fdf);
	else if (keysym == XK_w || keysym == XK_d || keysym == XK_s || keysym == XK_a)
		translation_hook(keysym, p_fdf);
	else if (keysym == XK_KP_Add || keysym == XK_KP_Subtract)
		scaling_hook(keysym, p_fdf);
	else if (keysym == XK_1 || keysym == XK_2)
		depthmodif_hook(keysym, p_fdf);
	// frame_hook(p_fdf); //test
	return (1);
	
}
void	init_imgstruct(t_fdf *p_fdf, int action)
{
	t_imgstruct *img;

	if (action = 1)
		img = &(p_fdf->s_img);
	else
		img = &(p_fdf->s_nxt_img);
	img->img = mlx_new_image(p_fdf->mlx, WIDTH, HEIGHT); 
	if (!img)
		close_program(p_fdf, "Error : mlx_new_image()");//bien fermer la seconde image lors de close
	img->p_img_pixels = mlx_get_data_addr(img->img, &(img->bits_per_pixel), &(img->line_len), &(img->endian));
}

int	frame_hook(t_fdf *p_fdf) //on pourrait mettre direct p_fdf
{
	ft_printf("hooks : frame_hook\n");

    if (ft_memcmp(&(p_fdf->proj), &(p_fdf->proj.last_proj), sizeof(t_proj)) == 0);
        return (0);
	init_imgstruct(p_fdf, 2);
    put_view_in_img(p_fdf, p_fdf->s_nxt_img, p_fdf->map);
	ft_memove( &(p_fdf->proj), &(p_fdf->proj), sizeof(t_proj)); //attention a la last proj est contenu dans proj
    //ft_printf("hooks : frame_hook before image put window\n");
	mlx_put_image_to_window(p_fdf->mlx, p_fdf->win, p_fdf->img_struct.img, 0, 0); //on ajoute l' image a l'origine de la fenetre
	return (1);
}