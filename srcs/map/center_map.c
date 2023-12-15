#include "../../includes/fdf.h"

void    center_map(t_map_data md, t_map_elem **map)
{
    size_t  i;
    size_t  j;

    i = 0;
    while(map[i])
    {
        j = 0;
        while(map[i][j].valid)
        {
            map[i][j].x -= md.center_x;
            map[i][j].y -= md.center_y;
            j++;
        }
        i++;
    }
    ft_printf("center map : center_map offset center x = %d offset center y = %d\n", md.center_x, md.center_y);//
}