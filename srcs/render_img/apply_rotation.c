# include "../../includes/fdf.h"

void    apply_rot_x(t_map_elem *p_map_el, double cos_a, double sin_a, t_proj proj)
{
    int old_y;
    int old_z; 

    old_y = p_map_el->proj_y;
    old_z = p_map_el->z * proj.depthfactor;
    p_map_el->proj_y = old_y * cos_a + old_z * sin_a;
    // p_map_el->proj_z = old_y * (-sin_a) + old_z * cos_a; //est ce reellement utile
	// ft_printf("apply_rotation : rot X old proj_z = %d old proj_y = %d new proj_z = %d new proj_y = %d \n", old_z, old_y, p_map_el->proj_z, p_map_el->proj_y);//
}

void    apply_rot_y(t_map_elem *p_map_el, double cos_a, double sin_a, t_proj proj)
{
    int old_x;
    int old_z;

    old_x = p_map_el->x;
    old_z = p_map_el->z * proj.depthfactor;
    p_map_el->x = old_x * cos_a + old_z * (-sin_a);
    p_map_el->z = old_x * sin_a + old_z * cos_a;
	// ft_printf("apply_rotation : rot Y old z = %d old x = %d new z = %d new x = %d \n", old_z, old_x, p_map_el->z, p_map_el->x);//
}

void    apply_rot_z(t_map_elem *p_map_el, double cos_a, double sin_a)
{
    int old_x;
    int old_y;

    old_x = p_map_el->x;
    old_y = p_map_el->proj_y;
    p_map_el->x = old_x * cos_a + old_y * sin_a;
    p_map_el->y = old_x * (-sin_a) + old_y * cos_a;
	// ft_printf("apply_rotation : rot Z old y = %d old x = %d new y = %d new x = %d \n", old_y, old_x, p_map_el->y, p_map_el->x);//

}

// void    apply_rot_x(t_map_elem *p_map_el, double cos_a, double sin_a)
// {
//     int old_y;
//     int old_z; 

//     old_y = (p_map_el->y) - HEIGHT / 2;
//     old_z = p_map_el->z; // de quelle maniere obtenir la valeur de z centrale ? idee : obtenir dz dans get map borders ?? ou centrer autours de 0 ??
//     p_map_el->y = (old_y * cos_a + old_z * sin_a) + HEIGHT / 2;
//     p_map_el->z = old_y * (-sin_a) + old_z * cos_a;//ne se voit pas a l' ecran mais utile pour les calculs suivants
// }

// void apply_rot_y(t_map_elem *p_map_el, double cos_a, double sin_a)
// {
//     int old_x;
//     int old_z;

//     old_x = (p_map_el->x) - WIDTH / 2;
//     old_z = p_map_el->z;
//     p_map_el->x = (old_x * cos_a + old_z * (-sin_a)) + WIDTH / 2;
//     p_map_el->z = old_x * sin_a + old_z * cos_a;
// }

// void apply_rot_z(t_map_elem *p_map_el, double cos_a, double sin_a)
// {
//     int old_x;
//     int old_y;

//     old_x = (p_map_el->x) - WIDTH / 2;
//     old_y = (p_map_el->y) - HEIGHT / 2;
//     p_map_el->x = (old_x * cos_a + old_y * sin_a) + WIDTH / 2;
//     p_map_el->y = (old_x * (-sin_a) + old_y * cos_a) + HEIGHT / 2;
// }


void    apply_rotation(t_map_elem *p_view_el, t_proj proj)
{
    //avant test les conditions etaient du type if (p_view_el->y)
    // printf("WWWWWWWWWWWWWW ROT X = %f  ROT Y =   ROT Z =  ", proj.rot_x);
    apply_rot_x(p_view_el, (double)cos(proj.rot_x), (double)sin(proj.rot_x), proj);
    apply_rot_y(p_view_el, (double)cos(proj.rot_y), (double)sin(proj.rot_y), proj);
    apply_rot_z(p_view_el, (double)cos(proj.rot_z), (double)sin(proj.rot_z));
}