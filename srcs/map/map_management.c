#include "../../includes/fdf.h"

t_map_borders	get_map_borders(t_fdf *p_fdf, t_map_elem **map)
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
	return (borders);
}

t_map_elem **get_map(char *filename)
{	
	int			fd;
	char		***map_char3;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Afficher un message d'erreur pour open ?\n", 2), NULL);
	map_char3 = get_map_in_char3(get_map_in_char2(get_map_in_char1(fd)));
	return (create_map_elem2(map_char3));

}


//astuce : toutes les allocations memoire sont faites avec calloc ce qui garantit le null terminal en 1 ligne et facilite les free. 