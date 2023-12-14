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

// t_map_borders	get_map_borders(t_map_elem **map)
// {
// 	size_t			i; 
// 	size_t			j;
// 	t_map_borders	borders;

// 	i = 0;
// 	borders = (t_map_borders) {map[0][0].x, map[0][0].x, map[0][0].y, map[0][0].y};
// 	while(map[i])
// 	{
// 		j = 0; 
// 		while (map[i][j].valid)
// 		{
// 			if ((int) floor(map[i][j].x) < borders.min_x)
// 				borders.min_x = (int) floor(map[i][j].x);
// 			else if ((int) ceil(map[i][j].x) > borders.max_x)
// 				borders.max_x = (int) ceil(map[i][j].x);
// 			if ((int) floor(map[i][j].y) < borders.min_y)
// 				borders.min_y = (int) floor(map[i][j].y);
// 			else if ((int) ceil(map[i][j].y) > borders.max_y)
// 				borders.max_y = (int) ceil(map[i][j].y);
// 			j++;
// 		}
// 		i++;
// 	}
// 	//printf(" projection_utils : get map border => min x = %d max x = %d min y = %d max y = %d\n", borders.min_x, borders.max_x, borders.min_y, borders.max_y);//
// 	return (borders);
// }

t_map_data	get_map_data(t_map_elem **map)
{
	size_t			i; 
	size_t			j;
	t_map_data		md;

	i = 0;
	md.borders = (t_map_borders) {map[0][0].x, map[0][0].x, map[0][0].y, map[0][0].y};
	while(map[i])
	{
		j = 0; 
		while (map[i][j].valid)
		{
			if ((int) floor(map[i][j].x) < md.borders.min_x)
				md.borders.min_x = (int) floor(map[i][j].x);
			else if ((int) ceil(map[i][j].x) > md.borders.max_x)
				md.borders.max_x = (int) ceil(map[i][j].x);
			if ((int) floor(map[i][j].y) < md.borders.min_y)
				md.borders.min_y = (int) floor(map[i][j].y);
			else if ((int) ceil(map[i][j].y) > md.borders.max_y)
				md.borders.max_y = (int) ceil(map[i][j].y);
			j++;
		}
		i++;
	}
	md.width = j; //+1 ou -1 ??
	md.height = i; //+1 ou -1 ??
	md.center_x = md.width / 2;
    md.center_y = md.height / 2;
	//printf(" projection_utils : get map border => min x = %d max x = %d min y = %d max y = %d\n", borders.min_x, borders.max_x, borders.min_y, borders.max_y);//
	return (md);
}

// t_map_borders	get_projection_borders(t_map_elem **map) // ne peut pas etre replace par getmapdata ??
// {
// 	size_t			i; 
// 	size_t			j;
// 	t_map_borders	borders;

// 	i = 0;
// 	borders = (t_map_borders) {map[0][0].proj_x, map[0][0].proj_x, map[0][0].proj_y, map[0][0].proj_y};
// 	while(map[i])
// 	{
// 		j = 0; 
// 		while (map[i][j].valid)
// 		{
// 			if ((int) floor(map[i][j].proj_x) < borders.min_x)
// 				borders.min_x = (int) floor(map[i][j].proj_x);
// 			else if ((int) ceil(map[i][j].proj_x) > borders.max_x)
// 				borders.max_x = (int) ceil(map[i][j].proj_x);
// 			if ((int) floor(map[i][j].proj_y) < borders.min_y)
// 				borders.min_y = (int) floor(map[i][j].proj_y);
// 			else if ((int) ceil(map[i][j].proj_y) > borders.max_y)
// 				borders.max_y = (int) ceil(map[i][j].proj_y);
// 			j++;
// 		}
// 		i++;
// 	}
// 	//printf(" projection_utils : get map border => min proj_x = %d max proj_x = %d min proj_y = %d max proj_y = %d\n", borders.min_x, borders.max_x, borders.min_y, borders.max_y);//
// 	return (borders);
// }

void	define_scale(t_proj *p_proj, t_map_data	md) 
{
	// printf("utils : define_scale => scale init = %f\n", p_proj->scale );//
	double scale_x;
	double scale_y;

	scale_x = SCALE_FACTOR * WIDTH / (md.width);
	scale_y = SCALE_FACTOR * HEIGHT / (md.height);
	if (scale_x < scale_y)
		p_proj->scale = scale_x;
	else
		p_proj->scale = scale_y;
	// p_proj->scale = *((double *)(min_bytewise(&scale_x, &scale_y, sizeof(double)))); // meme chose mais plus complexe
	printf("utils : define_scale => scale finale = %f\n", p_proj->scale);//

}

void	define_offsets(t_proj *p_proj, t_map_data md, double scale)
{
	printf("utils : define_offsets\n");//
	p_proj->offset_x = md.center_x + round((WIDTH - (scale * md.width)) / 2);
	p_proj->offset_y = md.center_y + round((HEIGHT - (scale * md.height)) / 2);
	
	// printf("utils : define_offsets => scale received = %f width map = %f, height map = %f = offset x = %d offset y = %d\n", (float)round(scale), (float)round(scale * abs(mb.max_x - mb.min_x)), (float)round(6.4 * abs(mb.max_y - mb.min_y)), p_proj->offset_x, p_proj->offset_y);//
	// ft_printf(" after scale offset min x = %d  max x = %d min y = %d max_y = %d", (int)(p_proj->offset_x + scale * mb.min_x), (int)(p_proj->offset_x + scale * mb.max_x), (int)(p_proj->offset_y + scale * mb.min_y), (int)(p_proj->offset_y + scale * mb.max_y));
	ft_printf("offsetx = %d offsety = %d", p_proj->offset_x, p_proj->offset_x);
	//scale = scale + 0; // pour eviter message erreur
}