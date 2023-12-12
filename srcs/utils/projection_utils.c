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
	printf(" projection_utils : get map border => min x = %d max x = %d min y = %d max y = %d\n", borders.min_x, borders.max_x, borders.min_y, borders.max_y);//
	return (borders);
}

void	define_scale(t_projection_utils *p_utils, t_map_borders mb) 
{
	printf("utils : define_scale => scale init = %f\n", p_utils->scale );//
	double scale_x;
	double scale_y;

	scale_x = SCALE_FACTOR * WIDTH / (mb.max_x - mb.min_x);
	scale_y = SCALE_FACTOR * HEIGHT / (mb.max_y - mb.min_y);
	if (scale_x < scale_y)
		p_utils->scale = scale_x;
	else
		p_utils->scale = scale_y;
	// p_utils->scale = *((double *)(min_bytewise(&scale_x, &scale_y, sizeof(double)))); // meme chose mais plus complexe
	printf("utils : define_scale => scale final = %f and min x = %f max x = %f min y = %f max y = %f\n", p_utils->scale, mb.min_x * p_utils->scale, mb.max_x * p_utils->scale, mb.min_y * p_utils->scale, mb.max_y * p_utils->scale);//

}

void	define_offsets(t_projection_utils *p_utils, t_map_borders mb, double scale)
{
	
	//scale = 6.4; //RETIRER ABSOLUMENT
	p_utils->offset_x = round((WIDTH - (scale * abs(mb.max_x - mb.min_x))) / 2);
	p_utils->offset_y = round((HEIGHT - (scale * abs(mb.max_y - mb.min_y))) / 2);
	if(mb.min_x < 0)
		p_utils->offset_x += abs((int)(round(mb.min_x) * scale)); // juste (- mb.min_x a l' air de marcher)
	if(mb.min_y < 0)
	{
		p_utils->offset_y += abs((int)(round(mb.min_y) * scale));
	}
	printf("utils : define_offsets => scale received = %f width map = %f, height map = %f = offset x = %d offset y = %d\n", (float)round(scale), (float)round(scale * abs(mb.max_x - mb.min_x)), (float)round(6.4 * abs(mb.max_y - mb.min_y)), p_utils->offset_x, p_utils->offset_y);//
	ft_printf(" after scale offset min x = %d  max x = %d min y = %d max_y = %d", (int)(p_utils->offset_x + scale * mb.min_x), (int)(p_utils->offset_x + scale * mb.max_x), (int)(p_utils->offset_y + scale * mb.min_y), (int)(p_utils->offset_y + scale * mb.max_y)); 
	printf("aaaaa");
	//scale = scale + 0; // pour eviter message erreur
}