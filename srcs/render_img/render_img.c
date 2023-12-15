# include "../../includes/fdf.h"

void    transform_proj_mapelem(t_fdf *p_fdf, t_map_elem *p_map_el, int flag)
{
	// printf("render_img : transform_map_in_view scale = %f offsetx = %d offsety = %d\n", p_fdf->proj.scale, p_fdf->proj.offset_x, p_fdf->proj.offset_y);//
    t_proj current; 
    t_proj  last;

    current = p_fdf->projs.current;
    last = p_fdf->projs.last;
    ft_printf("coor centered x = %d y = %d \n", p_map_el->x, p_map_el->y);
    // if (flag || current.scale != last.scale)
    apply_scaling(p_map_el, current);
    // apply_rotation(p_map_el, current);//test
    ft_printf("coor after scaling proj_x = %d proj_y = %d\n", p_map_el->proj_x, p_map_el->proj_y);
    // if (flag || current.offset_x != last.offset_x || current.offset_y != last.offset_y)
    apply_offset(p_map_el, current);
    ft_printf("coor after scaling and offset proj_x = %d proj_y = %d\n", p_map_el->proj_x, p_map_el->proj_y);
    flag = flag + 1; //test
    last = last; //test
    
}

// int     transform_base_mapelem(t_fdf *p_fdf, t_map_elem *p_map_el)
// {
//     t_proj current; 
//     t_proj  last;
//     int modif_flag;

//     current = p_fdf->projs.current;
//     last = p_fdf->projs.last;
//     modif_flag = 0;
//     if (current.depthfactor != last.depthfactor)
//     {
//         // apply_depthmodif(p_map_el, current); //la modif de dept est pris en compte au moment de la rotation
//         modif_flag = 1; //garder le flage de modif pour la detection
//     }
//     if (modif_flag || current.rot_x != last.rot_x || current.rot_y != last.rot_y || current.rot_z != last.rot_z)
//     {
//         apply_rotation(p_map_el, current);
//         p_map_el = p_map_el; //desactiver erreur 
//         modif_flag = 1; 
//     }
//     return (modif_flag);
// }

void    init_proj_map(t_fdf *p_fdf, t_map_elem **map)
{
	ft_printf("main: init proj map\n");//
    size_t  i; 
    size_t  j;
    int     modif_flag;
    //ft_printf("elem qui segfault = %d\n", map[1][2].valid); //test
    modif_flag = 1; //toujours active
    i = 0;
    while (map[i])
    {
        j = 0; 
        while (map[i][j].valid)
        {
            // transform_base_mapelem(p_fdf, &map[i][j]);
            transform_proj_mapelem(p_fdf, &map[i][j], modif_flag); 
            j++;
        }
        i++;
    }
//    printf("sortie %p %p %d\n", p_fdf, p_img, modif_flag);//
}

void    put_view_in_img(t_fdf *p_fdf, t_imgstruct *p_img, t_map_elem **map)
{
    //on utilise les int car l'img s_img de mlx a des size_line .. en int ?
	ft_printf("render_img : put_view_in_img\n");//
    size_t  i; 
    size_t  j;
    int     modif_flag;
    //ft_printf("elem qui segfault = %d\n", map[1][2].valid); //test
    modif_flag = 0;//
    modif_flag = modif_flag + 1;// TEST
    p_fdf = p_fdf + 1; //test
    i = 0;
    while (map[i])
    {
        j = 0; 
        while (map[i][j].valid)
        {
            // modif_flag = transform_base_mapelem(p_fdf, &map[i][j]); // faire le 1ere img
            // transform_proj_mapelem(p_fdf, &map[i][j], modif_flag); 
            // put_pixel(p_img, map[i][j + 1].proj_x, map[i][j + 1].proj_y, 300000);// test
            // ft_printf("p0 projx %d p0 projy %d p1 projx %d p1 projy %d \n", map[i][j].proj_x, map[i][j].proj_y, map[i][j + 1].proj_x, map[i][j + 1].proj_y);// test
            if (map[i][j + 1].valid)
                plot_line(p_img, map[i][j], map[i][j + 1]);
            if (map[i + 1])
            {
                ft_printf("aaa");
                if (map[i + 1][j].valid)
                    plot_line(p_img, map[i][j], map[i + 1][j]);
                if(map[i + 1][j + 1].valid)
                    plot_line(p_img,map[i][j], map[i + 1][j + 1]);
            }
            j++;
        }
        i++;
    }

//    printf("sortie %p %p %d\n", p_fdf, p_img, modif_flag);//
}