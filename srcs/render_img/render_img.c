# include "../../includes/fdf.h"

int transform_base_map_el(t_map_elem *p_map_el, t_proj current, t_proj last)
{
    int    modif_flag;

    modif_flag = 0;
    if (current.depthfactor != last.depthfactor)
    {
        apply_depthmodif(p_map_el, current);
        modif_flag = 1;
    }
    if (current.rot_x != last.rot_x || current.rot_y != last.rot_y || current.rot_z != last.rot_z)
    {
        apply_rotation(p_map_el, current);
        modif_flag = 1;
    }
    return (modif_flag);
}

void    transform_projection_map_el(t_map_elem *p_map_el, t_proj current, t_proj last, int flag)
{
    if (flag || current.scale != last.scale)
        apply_scaling(p_map_el, current);
    if (flag || current.offset_x != last.offset_x || current.offset_y != last.offset_y)
        apply_offset(p_map_el, current);
}

void    transform_coor_in_proj_coor(t_fdf *p_fdf, t_map_elem *p_map_el)
{
	// printf("render_img : transform_map_in_view scale = %f offsetx = %d offsety = %d\n", p_fdf->proj.scale, p_fdf->proj.offset_x, p_fdf->proj.offset_y);//
    t_proj current; 
    t_proj  last;
    int    modif_flag;
    //t_map_data md;

    current = *(p_fdf->projs.current);
    last = *(p_fdf->projs.last);
    //md = p_fdf->map_data;
    modif_flag = transform_base_map_el(p_map_el, *current, *last);
    transform_projection_map_el(p_map_el, *current, *last, modif_flag);

    
}


// void    create_projection(t_fdf *p_fdf, t_map_elem **map)
// {
//     size_t  i; 
//     size_t  j;
//     static t_proj last_proj;

//     i = 0;
//     while (map[i])
//     {
//         j = 0;
//         while (map[i][j].valid)
//         {
//             //ft_printf("before transform map in view : coor line = %d col = %d\n", i, j);//
//             transform_coor_in_proj_coor(p_fdf->map_data, p_fdf->proj, last_proj, &map[i][j]);
//             j++;
//         }
//         i++;
//     }
//     ft_memcpy( &last_proj, &(p_fdf->proj), sizeof(t_proj));
// }
// on peut fusionner les deux si on supprime l' img precedente
void    put_view_in_img(t_fdf *p_fdf, t_imgstruct *p_img, t_map_elem **map)
{
    //on utilise les int car l'img s_img de mlx a des size_line .. en int ?
	// ft_printf("put_view_in_img : create_view\n");//
    size_t  i; 
    size_t  j;

    i = 0; 
    while (map[i])
    {
        j = 0; 
        while (map[i][j].valid)
        {
            transform_coor_in_proj_coor(p_fdf, &map[i][j]);
            if (map[i + 1][j].valid)
                plot_line(p_img, map[i][j], map[i + 1][j]);
            if (map[i][j + 1].valid)
                plot_line(p_img, map[i][j], map[i][j + 1]);
            if (map[i + 1][j + 1].valid)
                plot_line(p_img,map[i][j], map[i + 1][j + 1]);
            j++;
        }
        i++;
    }
    
}