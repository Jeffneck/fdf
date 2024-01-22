/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanglade <hanglade@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:07:32 by hanglade          #+#    #+#             */
/*   Updated: 2024/01/22 15:35:00 by hanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

t_map_elem	**fill_map_elem2(char ***map_char3, t_map_elem **map_elem2)
{
	size_t	i;
	size_t	j;
	char	**el_split;

	i = 0;
	el_split = NULL;
	while (map_char3[i])
	{
		j = 0;
		while (map_char3[i][j])
		{
			el_split = ft_split(map_char3[i][j], ',');
			if (!el_split)
				return (free_char3(&map_char3), free_map_elem2(&map_elem2),
					NULL);
			map_elem2[i][j] = (t_map_elem){j, i, ft_atoi(el_split[0]), 0, 0,
				ft_atoi(el_split[0]), strhexa_to_colorint(el_split[1]), 1};
			free_char2(&el_split);
			j++;
		}
		map_elem2[i][j].valid = 0;
		i++;
	}
	return (free_char3(&map_char3), map_elem2);
}

t_map_elem	**create_map_elem2(char ***map_char3)
{
	size_t		i;
	t_map_elem	**map_elem2;

	i = 0;
	if (!map_char3)
		return (NULL);
	map_elem2 = (t_map_elem **) ft_calloc(char3len(map_char3) + 1,
			sizeof(t_map_elem *));
	if (!map_elem2)
		return (free_char3(&map_char3), NULL);
	while (map_char3[i])
	{
		map_elem2[i] = (t_map_elem *) ft_calloc(char2len(map_char3[i]) + 1,
				sizeof(t_map_elem));
		if (!map_elem2[i])
			return (free_map_elem2(&map_elem2), free_char3(&map_char3), NULL);
		i++;
	}
	return (fill_map_elem2(map_char3, map_elem2));
}

t_map_elem	**get_map(char *filename)
{
	int		fd;
	char	***map_char3;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_printf("%s can't be opened\n", filename), NULL);
	map_char3 = get_map_in_char3(get_map_in_char2(get_map_in_char1(fd)));
	return (create_map_elem2(map_char3));
}
