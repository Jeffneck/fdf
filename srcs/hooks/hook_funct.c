# include "../../includes/fdf.h"

int close_hook(t_fdf *p_fdf)
{
    close_program(p_fdf, NULL);
}
void rotation_hook(int keysym, t_fdf *p_fdf)
{
    t_projection_utils p_utils;

    p_utils = p_fdf->p_utils;
    //valider ce systeme de rotation + rot_y 
    if(keysym == XK_KP_Up)
        p_utils.rot_x += 0.01;
    else if(keysym == XK_KP_Down)
        p_utils.rot_x -= 0.01;
    else if(keysym == XK_KP_Left)
        p_utils.rot_z += 0.01;
    else if(keysym == XK_KP_Right)
        p_utils.rot_z -= 0.01;
}
void translation_hook(int keysym, t_fdf *p_fdf)
{
    t_projection_utils p_utils;

    p_utils = p_fdf->p_utils;
    //remplacer offset_y par offset_z ?
    if(keysym == XK_W)
        p_utils.offset.y += p_utils.scale;
    else if(keysym == XK_S)
        p_utils.offset.y -= p_utils.scale;
    else if(keysym == XK_A)
        p_utils.offset.x += p_utils.scale;
    else if(keysym == XK_D)
        p_utils.offset.x -= p_utils.scale;
}
void scaling_hook(int keysym, t_fdf *p_fdf)
{
    t_projection_utils p_utils;

    p_utils = p_fdf->p_utils;
    if(keysym == XK_KP_Add)
    {
        if (p_utils.scale < 1000)
            p_utils.scale += 1;
    }
    else if(keysym == XK_KP_Subtract)
    {
        if (p_utils.scale > 2)
            p_utils.scale -= 1;
    }
}
void depthmodif_hook(int keysym, t_fdf *p_fdf)
{
    t_projection_utils p_utils;

    //comprendre l'utilite avant de valider apply_depthmodif
    p_utils = p_fdf->p_utils;
    if(keysym == XK_1)
        p_utils.depth -= 0.1;
    if(keysym == XK_2)
        p_utils.depth += 0.1;
    
}