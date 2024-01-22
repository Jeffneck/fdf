/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_transformations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanglade <hanglade@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:22:38 by hanglade          #+#    #+#             */
/*   Updated: 2024/01/22 15:23:15 by hanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

void	apply_scaling(t_map_elem *p_map_el, t_proj current)
{
	p_map_el->proj_x = p_map_el->x * ceil(current.scale);
	p_map_el->proj_y = p_map_el->y * ceil(current.scale);
	p_map_el->temp_z = p_map_el->z * 0.15 * current.scale * current.depthfactor;
}

void	apply_offset(t_map_elem *p_map_el, t_proj current)
{
	p_map_el->proj_x = p_map_el->proj_x + current.offset_x;
	p_map_el->proj_y = p_map_el->proj_y + current.offset_y;
}
