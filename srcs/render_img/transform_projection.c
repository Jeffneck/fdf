# include "../../includes/fdf.h"

void    apply_scaling(t_map_elem *p_map_el, t_proj current)
{
	// ft_printf("Before scaling x = %d y = %d z = %d \n", p_view_el->x, p_view_el->y, p_view_el->z);//
    p_map_el->proj_x = p_map_el->x * current.scale;
    p_map_el->proj_y = p_map_el->y * current.scale;
    //p_map_el->proj_z = p_map_el->z * current.scale;
	// ft_printf("After scaling x = %d y = %d z = %d \n", p_view_el->x, p_view_el->y, p_view_el->z);//
}

void    apply_offset(t_map_elem *p_map_el, t_proj current)
{
	// ft_printf("Before offset x = %d y = %d \n", p_view_el->x, p_view_el->y);//
    p_map_el->proj_x = p_map_el->x + current.offset_x;
    p_map_el->proj_y = p_map_el->y + current.offset_y;

}

