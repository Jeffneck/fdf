# include "../../includes/fdf.h"

void    transform_map_in_view(t_fdf *p_fdf, t_map_elem *p_view_el, t_map_elem map_el)
{
	// printf("render_img : transform_map_in_view scale = %f offsetx = %d offsety = %d\n", p_fdf->p_utils.scale, p_fdf->p_utils.offset_x, p_fdf->p_utils.offset_y);//
    t_projection_utils p_utils;

    p_utils = p_fdf->p_utils;
    *p_view_el = (t_map_elem) {map_el.x, map_el.y, map_el.z,
        map_el.depth, map_el.color, map_el.end};
    if (p_utils.scale != 1) //modifie pdt tests
        apply_scaling(p_view_el, p_utils);
    if (p_utils.offset_x != 0 || p_utils.offset_y != 0)
        apply_offset(p_view_el, p_utils);
    apply_depthmodif(p_view_el, p_utils);
    apply_rotation(p_view_el, p_utils);// a garder
}

void    create_view(t_fdf *p_fdf, t_map_elem **map, t_map_elem **view)
{
	// ft_printf("render_img : create_view\n");//
    size_t  i; 
    size_t  j;

    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j].end != 1)
        {
            //ft_printf("before transform map in view : coor line = %d col = %d\n", i, j);//
            transform_map_in_view(p_fdf, &view[i][j], map[i][j]);
            j++;
        }
        i++;
    }
}

void    put_view_in_img(t_fdf *p_fdf, t_map_elem **view)
{
    //on utilise les int car l'img s_img de mlx a des size_line .. en int ?
	// ft_printf("put_view_in_img : create_view\n");//
    int i; 
    int j;

    i = 0; 
    while (view[i])
    {
        j = 0; 
        while (view[i][j].end != 1)
        {
            if (view[i][j + 1].end != 1)
                plot_line(p_fdf,view[i][j], view[i][j + 1]);
            if (view[i + 1])
                plot_line(p_fdf,view[i][j], view[i + 1][j]);
            j++;
        }
        i++;
    }
}