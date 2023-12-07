#include "../../includes/fdf.h"

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