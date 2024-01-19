# include "../../includes/fdf.h"

int close_hook(t_fdf *p_fdf)
{
    ft_printf("hook_func : close_hook\n");
    close_program(p_fdf, NULL);
    exit(1);
    return(1);
}
void rotation_hook(int keysym, t_fdf *p_fdf)
{
    ft_printf("hook_func : rotation_hook\n");
    t_proj *proj;

    proj = &(p_fdf->projs.current);
    //valider ce systeme de rotation + rot_y 
    if(keysym == XK_Up)
        proj->rot_x += 0.02;
    else if(keysym == XK_Down)
        proj->rot_x -= 0.02;
    else if(keysym == XK_Left)
        proj->rot_y += 0.02;
    else if(keysym == XK_Right)
        proj->rot_y -= 0.02;
    else if(keysym == XK_0) //remettre en vue 2D ====modifier !!!!
    {
        proj->rot_y = 0;
        proj->rot_x = 0;
    }
}
void translation_hook(int keysym, t_fdf *p_fdf)
{
    printf("hook_func : translation_hook\n");
    t_proj *proj;

    proj = &(p_fdf->projs.current);
    if(keysym == XK_w)
        proj->offset_y += proj->scale / 3;
    else if(keysym == XK_s)
        proj->offset_y -= proj->scale / 3;
    else if(keysym == XK_a)
        proj->offset_x += proj->scale / 3;
    else if(keysym == XK_d)
        proj->offset_x -= proj->scale / 3;
}
void scaling_hook(int keysym, t_fdf *p_fdf)
{
    ft_printf("hook_func : scaling_hook\n");
    t_proj *proj;

    proj = &(p_fdf->projs.current);
    if(keysym == XK_KP_Add)
    {
        if (proj->scale < 1000)
            proj->scale += 1;
    }
    else if(keysym == XK_KP_Subtract)
    {
        if (proj->scale > 2)
            proj->scale -= 1;
    }
}
void depthmodif_hook(int keysym, t_fdf *p_fdf)
{
    ft_printf("hook_func : depthmodif_hook\n");
    t_proj *proj;

    proj = &(p_fdf->projs.current);
    if(keysym == XK_1)
        proj->depthfactor -= 0.05;
    if(keysym == XK_2)
        proj->depthfactor += 0.05;
}