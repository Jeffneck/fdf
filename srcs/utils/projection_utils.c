#include "../../includes/fdf.h"

// void	*min_bytewise(const void *a, const void *b, size_t size)
// {
// 	const unsigned char		*byte_a;
// 	const unsigned char		*byte_b;
// 	size_t						i;

// 	byte_a = (const unsigned char *)a;
// 	byte_b = (const unsigned char *)b;
// 	i = 0; 
// 	while (i < size)
// 	{
// 		if (byte_a[i] < byte_b[i])
// 			return (void *)a;
// 		else if (byte_b[i] < byte_a[i])
// 			return (void *)b;
// 		i++;
// 	}
// 	return (void *)a;
// }

t_map_borders	get_map_borders(t_map_elem **map)
{
	ft_printf("utils : projection_utils\n");//
	size_t			i; 
	size_t			j;
	t_map_borders	borders;

	i = 0;
	borders = (t_map_borders) {map[0][0].x, map[0][0].x, map[0][0].y, map[0][0].y};
	while(map[i])
	{
		j = 0; 
		while (map[i][j].end != 1)
		{
			if ((int) floor(map[i][j].x) < borders.min_x)
				borders.min_x = (int) floor(map[i][j].x);
			else if ((int) ceil(map[i][j].x) > borders.max_x)
				borders.max_x = (int) ceil(map[i][j].x);
			if ((int) floor(map[i][j].y) < borders.min_y)
				borders.min_y = (int) floor(map[i][j].y);
			else if ((int) ceil(map[i][j].y) > borders.max_y)
				borders.max_y = (int) ceil(map[i][j].y);
			j++;
		}
		i++;
	}
	return (borders);
}

void	define_scale(t_projection_utils *p_utils, t_map_borders mb) 
{
	ft_printf("utils : define_scale\n");//
	double scale_x;
	double scale_y;

	scale_x = SCALE_FACTOR * WIDTH / (mb.max_x - mb.min_x);
	scale_y = SCALE_FACTOR * HEIGHT / (mb.max_y - mb.min_y);
	if (scale_x < scale_y)
		p_utils->scale = scale_x;
	else
		p_utils->scale = scale_y;
	// p_utils->scale = *((double *)(min_bytewise(&scale_x, &scale_y, sizeof(double)))); // meme chose mais plus complexe
}

void	define_offsets(t_projection_utils *p_utils, t_map_borders mb, double scale)
{
	ft_printf("utils : define_offsets\n");//
	p_utils->offset_x = round((WIDTH - scale * (mb.max_x - mb.min_x)) / 2);
	p_utils->offset_y = round((HEIGHT - scale * (mb.max_y - mb.min_y)) / 2);
	if(mb.min_x < 0)
		p_utils->offset_x += (- mb.min_x);
	if(mb.min_y < 0)
		p_utils->offset_y += (- mb.min_y);
}