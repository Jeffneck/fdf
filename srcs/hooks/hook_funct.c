/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_funct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanglade <hanglade@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:59:14 by hanglade          #+#    #+#             */
/*   Updated: 2024/01/22 15:56:02 by hanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

int	close_hook(t_fdf *p_fdf)
{
	close_program(p_fdf, NULL);
	return (0);
}

void	rotation_hook(int keysym, t_fdf *p_fdf)
{
	t_proj	*proj;

	proj = &(p_fdf->projs.current);
	if (keysym == XK_Up)
		proj->rot_x += 0.05;
	else if (keysym == XK_Down)
		proj->rot_x -= 0.05;
	else if (keysym == XK_Left)
		proj->rot_y += 0.05;
	else if (keysym == XK_Right)
		proj->rot_y -= 0.05;
}

void	translation_hook(int keysym, t_fdf *p_fdf)
{
	t_proj	*proj;

	proj = &(p_fdf->projs.current);
	if (keysym == XK_w)
		proj->offset_y += proj->scale / 3;
	else if (keysym == XK_s)
		proj->offset_y -= proj->scale / 3;
	else if (keysym == XK_a)
		proj->offset_x += proj->scale / 3;
	else if (keysym == XK_d)
		proj->offset_x -= proj->scale / 3;
}

void	scaling_hook(int keysym, t_fdf *p_fdf)
{
	t_proj	*proj;

	proj = &(p_fdf->projs.current);
	if (keysym == XK_KP_Add)
	{
		if (proj->scale < 1000)
			proj->scale += 1;
	}
	else if (keysym == XK_KP_Subtract)
	{
		if (proj->scale > 2)
			proj->scale -= 1;
	}
}

void	depthmodif_hook(int keysym, t_fdf *p_fdf)
{
	t_proj	*proj;

	proj = &(p_fdf->projs.current);
	if (keysym == XK_1)
		proj->depthfactor -= 0.05;
	if (keysym == XK_2)
		proj->depthfactor += 0.05;
}
