# include "../../includes/fdf.h"

void    apply_rot_x(t_map_elem *p_view_el, double cos_a, double sin_a)
{
    int old_y;
    int old_z; 

    old_y = p_view_el->y;
    old_z = p_view_el->z;
    p_view_el->y = old_y * cos_a + old_z * sin_a;
    p_view_el->z = old_y * (-sin_a) + old_z * cos_a;    
}

void apply_rot_y(t_map_elem *p_view_el, double cos_a, double sin_a)
{
    int old_x;
    int old_z;

    old_x = p_view_el->x;
    old_z = p_view_el->z;
    p_view_el->x = old_x * cos_a + old_z * (-sin_a);
    p_view_el->z = old_x * sin_a + old_z * cos_a;
}

void apply_rot_z(t_map_elem *p_view_el, double cos_a, double sin_a)
{
    int old_x;
    int old_y;

    old_x = p_view_el->x;
    old_y = p_view_el->y;
    p_view_el->x = old_x * cos_a + old_y * sin_a;
    p_view_el->y = old_x * (-sin_a) + old_y * cos_a;
}

// void    apply_rot_x(t_map_elem *p_view_el, double cos_a, double sin_a)
// {
//     int old_y;
//     int old_z; 

//     old_y = (p_view_el->y) - HEIGHT / 2;
//     old_z = p_view_el->z; // de quelle maniere obtenir la valeur de z centrale ? idee : obtenir dz dans get map borders ?? ou centrer autours de 0 ??
//     p_view_el->y = (old_y * cos_a + old_z * sin_a) + HEIGHT / 2;
//     p_view_el->z = old_y * (-sin_a) + old_z * cos_a;//ne se voit pas a l' ecran mais utile pour les calculs suivants
// }

// void apply_rot_y(t_map_elem *p_view_el, double cos_a, double sin_a)
// {
//     int old_x;
//     int old_z;

//     old_x = (p_view_el->x) - WIDTH / 2;
//     old_z = p_view_el->z;
//     p_view_el->x = (old_x * cos_a + old_z * (-sin_a)) + WIDTH / 2;
//     p_view_el->z = old_x * sin_a + old_z * cos_a;
// }

// void apply_rot_z(t_map_elem *p_view_el, double cos_a, double sin_a)
// {
//     int old_x;
//     int old_y;

//     old_x = (p_view_el->x) - WIDTH / 2;
//     old_y = (p_view_el->y) - HEIGHT / 2;
//     p_view_el->x = (old_x * cos_a + old_y * sin_a) + WIDTH / 2;
//     p_view_el->y = (old_x * (-sin_a) + old_y * cos_a) + HEIGHT / 2;
// }

void    apply_rotation(t_map_elem *p_view_el, t_projection_utils p_utils)
{
    //avant test les conditions etaient du type if (p_view_el->y)
    if (p_utils.rot_x != 0.0)
        apply_rot_x(p_view_el, (double)cos(p_utils.rot_x), (double)sin(p_utils.rot_x));
    if (p_utils.rot_y != 0.0) 
        apply_rot_y(p_view_el, (double)cos(p_utils.rot_y), (double)sin(p_utils.rot_y));
    if (p_utils.rot_z != 0.0)
        apply_rot_z(p_view_el, (double)cos(p_utils.rot_z), (double)sin(p_utils.rot_z));
}