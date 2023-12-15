# include "../../includes/fdf.h"

void    apply_scaling(t_map_elem *p_map_el, t_proj current)
{
	// ft_printf("Before scaling x = %d y = %d", p_map_el->x, );//
    p_map_el->proj_x = p_map_el->x * ceil(current.scale); // ceil == test proj_x au lieu de x  = test 
    p_map_el->proj_y = p_map_el->y * ceil(current.scale);
    p_map_el->temp_z = p_map_el->z * current.scale;
	// ft_printf("After scaling proj x = %d proj y = %d\n", p_view_el->x, p_view_el->y, p_view_el->z);//
}

void    apply_offset(t_map_elem *p_map_el, t_proj current)
{
	//ft_printf("Before offset projx = %d projy = %d, current offsetx %d  current offsety %d \n", p_view_el->x, p_view_el->y);//
    p_map_el->proj_x = p_map_el->proj_x + current.offset_x;
    p_map_el->proj_y = p_map_el->proj_y + current.offset_y;

}

void    apply_depthmodif(t_map_elem *p_map_el, t_proj current)
{
    if(p_map_el->z)
        p_map_el->z *= current.depthfactor;
    else
        p_map_el->z = p_map_el->z * current.depthfactor;
}