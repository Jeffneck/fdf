# include "../../includes/fdf.h"

int close_hook(t_fdf *p_fdf)
{
    ft_printf("hook_func : close_hook\n");
    close_program(p_fdf, NULL);
    return(1);
}
void rotation_hook(int keysym, t_fdf *p_fdf)
{
    ft_printf("hook_func : rotation_hook\n");
    t_projection_utils *p_utils;

    p_utils = &(p_fdf->p_utils);
    //valider ce systeme de rotation + rot_y 
    if(keysym == XK_Up)
        p_utils->rot_x += 0.01;
    else if(keysym == XK_Down)
        p_utils->rot_x -= 0.01;
    else if(keysym == XK_Left)
        p_utils->rot_y += 0.01;
    else if(keysym == XK_Right)
        p_utils->rot_y -= 0.01;
}
void translation_hook(int keysym, t_fdf *p_fdf)
{
    printf("hook_func : translation_hook\n");
    t_projection_utils *p_utils;

    p_utils = &(p_fdf->p_utils);
    //remplacer offset_y par offset_z ?
    if(keysym == XK_w)
        p_utils->offset_y += p_utils->scale;
    else if(keysym == XK_s)
        p_utils->offset_y -= p_utils->scale;
    else if(keysym == XK_a)
        p_utils->offset_x += p_utils->scale;
    else if(keysym == XK_d)
        p_utils->offset_x -= p_utils->scale;
}
void scaling_hook(int keysym, t_fdf *p_fdf)
{
    ft_printf("hook_func : scaling_hook\n");
    t_projection_utils *p_utils;

    p_utils = &(p_fdf->p_utils);
    if(keysym == XK_KP_Add)
    {
        if (p_utils->scale < 1000)
            p_utils->scale += 1;
    }
    else if(keysym == XK_KP_Subtract)
    {
        if (p_utils->scale > 2)
            p_utils->scale -= 1;
    }
}
void depthmodif_hook(int keysym, t_fdf *p_fdf)
{
    ft_printf("hook_func : depthmodif_hook\n");
    t_projection_utils *p_utils;

    p_utils = &(p_fdf->p_utils);
    if(keysym == XK_1)
        p_utils->depthfactor -= 0.1;
    if(keysym == XK_2)
        p_utils->depthfactor += 0.1;
}