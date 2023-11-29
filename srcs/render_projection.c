# include "../includes/fdf.h"

void    apply_scaling(t_map_elem *p_view_el, t_projection_utils p_utils)
{
    t_map_elem view_el;

    view_el = *p_view_el;
    view_el.x *= scale;
    view_el.y *= scale;
    view_el.z *= scale;
}

void    apply_offset(t_map_elem *p_view_el, t_projection_utils p_utils)
{
    t_map_elem view_el;

    view_el = *p_view_el;
    view_el.x += offset_x;
    view_el.z += offset_z;
}

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

void    apply_rotation(t_map_elem *p_view_el, t_projection_utils p_utils)
{
    if (p_view_el->x)
        apply_rot_x(p_view_el, (double)cos(p_utils->rot_x), (double)sin(p_utils->rot_x));
    if (p_view_el->y)
        apply_rot_y(p_view_el, (double)cos(p_utils->rot_y), (double)sin(p_utils->rot_y));
    if (p_view_el->z)
        apply_rot_z(p_view_el, (double)cos(p_utils->rot_z), (double)sin(p_utils->rot_z));
}

void    apply_transformations(t_fdf *p_fdf, t_map_elem *p_view_el, t_map_elem map_el)
{
    t_map_elem view_el;

    view_el = *p_view_el;
    view_el.x = map_el.x;
    view_el.y = map_el.y;
    view_el.z = map_el.z;
    view_el.color = map_el.color;
    view_el.depth = map_el.depth;
    //dans quel ordre appliquer les transformations ?
    apply_scaling(p_view_el, p_fdf->p_utils);
    apply_offset(p_view_el, p_fdf->p_utils);
    apply_rotation(p_view_el, p_fdf->p_utils);
    // apply_translation(p_view_el, p_fdf->p_utils); même chose que offset non ? j'ai du me tromper
    apply_depthmodif(p_view_el, p_fdf->p_utils); //je ne comprends pas ce que c'est
}

void    create_view(p_fdf)
{
    size_t  i; 
    size_t  j;
    t_map_elem **map;
    t_map_elem **view;

    map = p_fdf->map;
    view = p_fdf->map_view;
    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j].end != 0)
        {
            update_view_elem(p_fdf, &view[i][j], map[i][j]);
            j++;
        }
        i++;
    }
}

//mlx_put img to window n'existe plus, comment faire
void	ft_clear_img(mlx_image_t *img)
{
	uint32_t	i;
	uint32_t	j;

	if (img)
	{
		i = -1;
		while (++i < img->width)
		{
			j = -1;
			while (++j < img->height)
				mlx_put_pixel(img, j, i, 0);
		}
	}
}

void    display_view()
{

}
void render_projection(t_fdf *p_fdf)
{
   create_view(p_fdf);
   display_view(p_fdf->map_view); //display directement sur une win ou sur img ??

}