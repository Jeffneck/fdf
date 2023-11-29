# include "../includes/fdf.h"

int close_hook(t_fdf *p_fdf)
{
    mlx_destroy_window(p_fdf->mlx, p_fdf->win);
    free_mapelem2(); // liberer + NULL t_map_elem
    mlx_destroy_display(p_fdf->mlx);
    free(p_fdf->mlx);
    exit(1);
}
void rotation_hook(int keysym, t_fdf *p_fdf)
{
    t_projection_utils p_utils;

    p_utils = p_fdf->p_utils
    //valider ce systeme de rotation
    if(keysym == XK_UP)
        p_utils.rot_x += 0.01;
    else if(keysym == XK_DOWN)
        p_utils.rot_x -= 0.01;
    else if(keysym == XK_LEFT)
        p_utils.rot_z += 0.01;
    else if(keysym == XK_RIGHT)
        p_utils.rot_z -= 0.01;
}
void translation_hook(int keysym, t_fdf *p_fdf)
{
    t_projection_utils p_utils;

    p_utils = p_fdf->p_utils
    //remplacer offset_y par offset_z ?
    if(keysym == XK_W)
        p_utils.offset_y += p_utils.scale;
    else if(keysym == XK_S)
        p_utils.offset_y -= p_utils.scale;
    else if(keysym == XK_A)
        p_utils.offset_x += p_utils.scale;
    else if(keysym == XK_D)
        p_utils.offset_x -= p_utils.scale;
}
void scaling_hook(int keysym, t_fdf *p_fdf)
{
    t_projection_utils p_utils;

    p_utils = p_fdf->p_utils
    if(keysym == XK_ADD)
    {
        if (p_utils.scale < 1000)
            p_utils.scale += 1;
    }
    else if(keysym == XK_SUBTRACT)
    {
        if (p_utils.scale > 2)
            p_utils.scale -= 1;
    }
}
void depthmodif_hook(int keysym, t_fdf *p_fdf)
{
    t_projection_utils p_utils;

    p_utils = p_fdf->p_utils
    if(keysym == XK_1)
        p_utils.depth -= 0.1;
    if(keysym == XK_1)
        p_utils.depth -= 0.1;
    
}

int	manage_keyhook(int keysym, t_fdf *p_fdf)
{
	if (keysym == XK_Escape)
        close_hook(p_fdf); //exit ou return erreur ?
	if (keysym == XK_LEFT || keysym == XK_RIGHT || keysym == XK_UP || keysym == XK_DOWN)
		rotation_hook(keysym, p_fdf);
	else if (keysym == XK_W || keysym == XK_D || keysym == XK_S || keysym == XK_A)
		translation_hook(keysym, p_fdf);
	else if (keysym == XK_ADD || keysym == XK_SUBTRACT)
		scaling_hook(keysym, p_fdf);
	else if (keysym == XK_1 || keysym == XK_2)
		depthmodif_hook(keysym, p_fdf);
	return (0);
	
}
void	frame_hooks(void *param) //on pourrait mettre direct p_fdf
{
	t_fdf *p_fdf;

	p_fdf = param;
	mlx_hook(p_fdf->win, 17, 0, close_hook, p_fdf); //bouton fermeture fenetre
    mlx_key_hook(p_fdf->win, manage_keyhook, p_fdf);
    render_projection(p_fdf); 



	
    


	
}