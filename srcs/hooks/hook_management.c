# include "../../includes/fdf.h"

void modify_projection_hook(int keysym, t_fdf *p_fdf)
{
    t_proj *proj;

    proj = &(p_fdf->projs.current);
    if(keysym == XK_0)
    {
        proj->rot_y = 0;
        proj->rot_x = 0;
	    proj->rot_z = 0;
    }
    else if(keysym == XK_9)
    {
	    proj->rot_x = -0.52;
	    proj->rot_y = 0.52;
	    proj->rot_z = 0;
    }

    else if(keysym == XK_8)
    {
	    proj->rot_x = -1;
	    proj->rot_y = 0;
	    proj->rot_z = 0;
    }
}

int	manage_keyhook(int keysym, t_fdf *p_fdf)
{
	ft_printf("hooks : manage_keyhook KEYSYM = %d \n", keysym);//
	if (keysym == XK_Escape)
        close_hook(p_fdf); //exit ou return erreur ?
	else if (keysym == XK_Left || keysym == XK_Right || keysym == XK_Up || keysym == XK_Down)
		rotation_hook(keysym, p_fdf);
	else if (keysym == XK_0 || keysym == XK_9 || keysym == XK_8)
		modify_projection_hook(keysym, p_fdf);
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
	// ft_printf("hooks : frame_hook\n");

	if (ft_memcmp(&(p_fdf->projs.current), &(p_fdf->projs.last), sizeof(t_proj)) == 0)
	{
		// ft_printf("img unchanged\n");
		return (0);
	}
	// p_fdf->s_imgtoclean = p_fdf->s_new_img;
	ft_memmove(&(p_fdf->s_img_to_del), &(p_fdf->s_new_img), sizeof(t_proj));//il faut garder ca pour free
	p_fdf->s_new_img = init_new_img(p_fdf);
	init_proj_map(p_fdf, p_fdf->map);//ajout test
	put_view_in_img(p_fdf, &(p_fdf->s_new_img), p_fdf->map);
	// ft_printf("hooks : frame_hook\n");//
	ft_memmove(&(p_fdf->projs.last), &(p_fdf->projs.current), sizeof(t_proj));
	// ft_printf("hooks : frame_hook before image put window\n");
	mlx_put_image_to_window(p_fdf->mlx, p_fdf->win, p_fdf->s_new_img.img_mlx, 0, 0);
	// if (p_fdf->s_img_to_del.img_mlx)
	// 	mlx_destroy_image(p_fdf->mlx, p_fdf->s_img_to_del.img_mlx);
	clean_close_imgstruct(p_fdf, &(p_fdf->s_img_to_del));
	// ft_printf("hooks : frame_hook sortie\n");
	return (1);
}