/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_rotation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanglade <hanglade@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:23:22 by hanglade          #+#    #+#             */
/*   Updated: 2024/01/22 15:25:46 by hanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

void	apply_rot_x(t_map_elem *p_map_el, double cos_a, double sin_a)
{
	int	old_y;
	int	old_z;

	old_y = p_map_el->proj_y;
	old_z = p_map_el->temp_z;
	p_map_el->proj_y = old_y * cos_a + old_z * sin_a;
	p_map_el->temp_z = old_y * (-sin_a) + old_z * cos_a;
}

void	apply_rot_y(t_map_elem *p_map_el, double cos_a, double sin_a)
{
	int	old_x;
	int	old_z;

	old_x = p_map_el->proj_x;
	old_z = p_map_el->temp_z;
	p_map_el->proj_x = old_x * cos_a + old_z * (-sin_a);
	p_map_el->temp_z = old_x * sin_a + old_z * cos_a;
}

void	apply_rot_z(t_map_elem *p_map_el, double cos_a, double sin_a)
{
	int	old_x;
	int	old_y;

	old_x = p_map_el->proj_x;
	old_y = p_map_el->proj_y;
	p_map_el->proj_x = old_x * cos_a + old_y * sin_a;
	p_map_el->proj_y = old_x * (-sin_a) + old_y * cos_a;
}

void	apply_rotation(t_map_elem *p_map_el, t_proj proj)
{
	apply_rot_x(p_map_el, (double)cos(proj.rot_x), (double)sin(proj.rot_x));
	apply_rot_y(p_map_el, (double)cos(proj.rot_y), (double)sin(proj.rot_y));
	apply_rot_z(p_map_el, (double)cos(proj.rot_z), (double)sin(proj.rot_z));
}
