/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanglade <hanglade@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:26:13 by hanglade          #+#    #+#             */
/*   Updated: 2024/01/22 16:01:13 by hanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

t_map_data	get_map_data2(t_map_data md, size_t i, size_t j)
{
	md.width = j;
	md.height = i;
	md.center_x = md.width / 2;
	md.center_y = md.height / 2;
	return (md);
}

t_map_data	get_map_data(t_map_elem **map)
{
	size_t		i;
	size_t		j;
	t_map_data	md;

	i = 0;
	md.borders = (t_map_borders){map[0][0].x, map[0][0].x,
		map[0][0].y, map[0][0].y};
	while (map[i])
	{
		j = 0;
		while (map[i][j].valid != 0)
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
	return (get_map_data2(md, i, j));
}

void	define_scale(t_proj *p_proj, t_map_data	md)
{
	double	scale_x;
	double	scale_y;

	scale_x = SCALE_FACTOR * WIDTH / (md.width);
	scale_y = SCALE_FACTOR * HEIGHT / (md.height);
	if (scale_x < scale_y)
		p_proj->scale = scale_x;
	else
		p_proj->scale = scale_y;
}

void	define_offsets(t_proj *p_proj, t_map_data md, double scale)
{
	p_proj->offset_x = md.center_x * scale
		+ round((WIDTH - (scale * md.width)) / 2);
	p_proj->offset_y = md.center_y * scale
		+ round((HEIGHT - (scale * md.height)) / 2);
}
