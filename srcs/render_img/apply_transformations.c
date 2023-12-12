# include "../../includes/fdf.h"

void    apply_scaling(t_map_elem *p_view_el, t_projection_utils p_utils)
{
	// ft_printf("Before scaling x = %d y = %d z = %d \n", p_view_el->x, p_view_el->y, p_view_el->z);//
    p_view_el->x *= p_utils.scale;
    p_view_el->y *= p_utils.scale;
    //p_view_el->z *= p_utils.scale;
	// ft_printf("After scaling x = %d y = %d z = %d \n", p_view_el->x, p_view_el->y, p_view_el->z);//
}

void    apply_offset(t_map_elem *p_view_el, t_projection_utils p_utils)
{
	// ft_printf("Before offset x = %d y = %d \n", p_view_el->x, p_view_el->y);//
    p_view_el->x += p_utils.offset_x;
    p_view_el->y += p_utils.offset_y;
}

void    apply_depthmodif(t_map_elem *p_view_el, t_projection_utils p_utils)
{
    p_view_el->z *= p_utils.depth;
}