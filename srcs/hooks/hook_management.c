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
	return (1);
	
}

int	frame_hook(t_fdf *p_fdf)
{
	ft_printf("hooks : frame_hook\n");

    if (ft_memcmp(&(p_fdf->projs.current), &(p_fdf->projs.last), sizeof(t_proj)) == 0);
        return (0);
	p_fdf->s_imgtoclean = p_fdf->s_new_img;
	p_fdf->s_new_img = init_new_img(p_fdf);
    put_view_in_img(p_fdf, p_fdf->s_new_img, p_fdf->map);
	ft_memove( &(p_fdf->projs.current), &(p_fdf->projs.last), sizeof(t_proj)); //attention a la last proj est contenu dans proj
    //ft_printf("hooks : frame_hook before image put window\n");
	mlx_put_image_to_window(p_fdf->mlx, p_fdf->win, p_fdf->s_new_img->img_mlx, 0, 0);
	clean_close_imgstruct(p_fdf, p_fdf->s_imgtoclean);
	return (1);
}