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
	frame_hook(p_fdf); //test
	return (1);
	
}
int	frame_hook(void *param) //on pourrait mettre direct p_fdf
{
	ft_printf("hooks : frame_hook\n");
	t_fdf *p_fdf;

	p_fdf = param;
    mlx_hook(p_fdf->win, 17, 0, close_hook, p_fdf); //bouton fermeture fenetre
    //mlx_hook(p_fdf->win, 2, 1L<<0, manage_keyhook, p_fdf);
	//mlx_key_hook(p_fdf->win, manage_keyhook, p_fdf);
    create_view(p_fdf, p_fdf->map, p_fdf->map_view);
    //etape pour clear l' img precedente ou en creer une nouvelle a chaque fois ?
	clear_img(p_fdf->img_struct);
    put_view_in_img(p_fdf, p_fdf->map_view); //ajouter les pixels a l'image
    ft_printf("hooks : frame_hook before image put window\n");
	mlx_put_image_to_window(p_fdf->mlx, p_fdf->win, p_fdf->img_struct.img, 0, 0); //on ajoute l' image a l'origine de la fenetre
	return (1); //il n' y a pas de retour d'erreur dans cette fonction 
}