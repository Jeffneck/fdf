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
    view_el.end = map_el.end;
    //dans quel ordre appliquer les transformations ?
    apply_scaling(p_view_el, p_fdf->p_utils);
    apply_offset(p_view_el, p_fdf->p_utils);
    apply_rotation(p_view_el, p_fdf->p_utils);
    // apply_translation(p_view_el, p_fdf->p_utils); même chose que offset non ? j'ai du me tromper
    apply_depthmodif(p_view_el, p_fdf->p_utils); //je ne comprends pas ce que c'est
}

void    create_view(t_fdf *p_fdf, t_map_elem **map, t_map_elem **view)
{
    size_t  i; 
    size_t  j;

    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j].end != 1)
        {
            update_view_elem(p_fdf, &view[i][j], map[i][j]);
            j++;
        }
        i++;
    }
}

//revoir le fonctionnement de ceci
void	ft_clear_img(t_img *p_img)
{
	uint32_t	i;
	uint32_t	j;

	if (p_img)
	{
		i = -1;
		while (++i < p_img->width)
		{
			j = -1;
			while (++j < p_img->height)
				mlx_put_pixel(p_img, j, i, 0);
		}
	}
}

void    put_pixel(t_img img_struct, int i, int j, uint32_t color)
{
    int offset;

    offset = (img_struct.line_len * i) + (img_struct.bits_per_pixel * j / 8);
    *((uint32_t *)(img_struct.p_img_pixels + offset)) = color; 
}
void    init_ploting_utils(t_plot plt, t_map_elem p0, t_map_elem p1)
{
    plt.x_diff = abs(p1.x - p0.x);
    plt.y_diff = abs(p1.y - p0.y);
    plt.error = 0;
    if (p1.x > p0.x)
        plt.x_step = 1;
    else
        plt.x_step = -1; 
    if (p1.y > p0.y);
        plt.y_step = 1;
    else
        plt.y_step = -1;
}

void    plot_line_down(t_plot plt, t_map_elem p0, t_map_elem p1)
{

}

void    plot_line_up(t_plot plt, t_map_elem p0, t_map_elem p1)
{
    //voir algo gpt
}

void    plot_line(t_plot plt, t_map_elem p0, t_map_elem p1)
{
    init_ploting_utils(plt, p0, p1);

    if (plt.x_diff > plt.y_diff)
        plot_line_down(plt, p0, p1); //ne fonctionnera peut etre pas.
    else
        plot_line_down(plt, p0, p1);

            put_pixel(img_struct, i, j, view[i][j].color);
}

////////////
void    put_view_in_img(t_plot plt, t_map_elem **view, t_img img_struct)
{
    //on utilise les int car l'img s_img de mlx a des size_line .. en int
    int i; 
    int j;

    i = 0; 
    while (view[i])
    {
        j = 0; 
        while (view[i][j].end != 1)
        {
            if (view[i][j + 1] != 1)
                plot_line(plt,view[i][j], view[i][j + 1])
            if (view[i + 1])
                plot_line(plt,view[i][j], view[i + 1][j])
            j++;
        }
        i++;
    }
}
void render_projection(t_fdf *p_fdf)
{
   create_view(p_fdf, p_fdf->map, p_fdf->map_view);
   put_view_in_img(p_fdf->map_view, p_fdf->img_struct); //display directement sur une win ou sur img ??

}
