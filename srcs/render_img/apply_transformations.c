# include "../../includes/fdf.h"

void    apply_scaling(t_map_elem *p_view_el, t_projection_utils p_utils)
{
    t_map_elem view_el;

    view_el = *p_view_el;
    view_el.x *= p_utils.scale;
    view_el.y *= p_utils.scale;
    view_el.z *= p_utils.scale;
}

void    apply_offset(t_map_elem *p_view_el, t_projection_utils p_utils)
{
    t_map_elem view_el;

    view_el = *p_view_el;
    view_el.x += p_utils.offset_x;
    view_el.y += p_utils.offset_y;
}

// void    apply_depthmodif(t_map_elem *p_view_el, t_projection_utils p_utils)
// {

// }