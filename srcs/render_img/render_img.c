/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanglade <hanglade@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:14:33 by hanglade          #+#    #+#             */
/*   Updated: 2024/01/22 15:16:21 by hanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

void	transform_proj_mapelem(t_fdf *p_fdf, t_map_elem *p_map_el, int flag)
{
	t_proj	current;
	t_proj	last;

	current = p_fdf->projs.current;
	last = p_fdf->projs.last;
	apply_scaling(p_map_el, current);
	apply_rotation(p_map_el, current);
	apply_offset(p_map_el, current);
	flag = flag + 1;
	last = last;
}

void	init_proj_map(t_fdf *p_fdf, t_map_elem **map)
{
	size_t	i;
	size_t	j;
	int		modif_flag;

	modif_flag = 1;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j].valid)
		{
			transform_proj_mapelem(p_fdf, &map[i][j], modif_flag);
			j++;
		}
		i++;
	}
}

void	put_view_in_img(t_fdf *p_fdf, t_imgstruct *p_img, t_map_elem **map)
{
	size_t	i;
	size_t	j;

	p_fdf = p_fdf + 1;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j].valid)
		{
			if (map[i][j + 1].valid)
				plot_line(p_img, map[i][j], map[i][j + 1]);
			if (map[i + 1])
			{
				if (map[i + 1][j].valid)
					plot_line(p_img, map[i][j], map[i + 1][j]);
				if (map[i + 1][j + 1].valid)
					plot_line(p_img, map[i][j], map[i + 1][j + 1]);
			}
			j++;
		}
		i++;
	}
}
