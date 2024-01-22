/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanglade <hanglade@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:55:54 by hanglade          #+#    #+#             */
/*   Updated: 2024/01/22 15:57:35 by hanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

void	modify_projection_hook(int keysym, t_fdf *p_fdf)
{
	t_proj	*proj;

	proj = &(p_fdf->projs.current);
	if (keysym == XK_0)
	{
		proj->rot_y = 0;
		proj->rot_x = 0;
		proj->rot_z = 0;
		proj->depthfactor = 0;
	}
	else if (keysym == XK_9)
	{
		proj->rot_x = -0.52;
		proj->rot_y = 0.52;
		proj->rot_z = 0;
		proj->depthfactor = 1;
	}
	else if (keysym == XK_8)
	{
		proj->rot_x = -1;
		proj->rot_y = 0;
		proj->rot_z = 0;
		proj->depthfactor = 1;
	}
}

int	manage_keyhook(int keysym, t_fdf *p_fdf)
{
	if (keysym == XK_Escape)
		close_hook(p_fdf);
	else if (keysym == XK_Left || keysym == XK_Right
		|| keysym == XK_Up || keysym == XK_Down)
		rotation_hook(keysym, p_fdf);
	else if (keysym == XK_0 || keysym == XK_9 || keysym == XK_8)
		modify_projection_hook(keysym, p_fdf);
	else if (keysym == XK_w || keysym == XK_d
		|| keysym == XK_s || keysym == XK_a)
		translation_hook(keysym, p_fdf);
	else if (keysym == XK_KP_Add || keysym == XK_KP_Subtract)
		scaling_hook(keysym, p_fdf);
	else if (keysym == XK_1 || keysym == XK_2)
		depthmodif_hook(keysym, p_fdf);
	return (1);
}

int	frame_hook(t_fdf *p_fdf)
{
	if (ft_memcmp(&(p_fdf->projs.current), &(p_fdf->projs.last),
			sizeof(t_proj)) == 0)
		return (0);
	ft_memmove(&(p_fdf->s_img_to_del), &(p_fdf->s_new_img), sizeof(t_proj));
	p_fdf->s_new_img = init_new_img(p_fdf);
	init_proj_map(p_fdf, p_fdf->map);
	put_view_in_img(p_fdf, &(p_fdf->s_new_img), p_fdf->map);
	ft_memmove(&(p_fdf->projs.last), &(p_fdf->projs.current), sizeof(t_proj));
	mlx_put_image_to_window(p_fdf->mlx, p_fdf->win,
		p_fdf->s_new_img.img_mlx, 0, 0);
	clean_close_imgstruct(p_fdf, &(p_fdf->s_img_to_del));
	return (1);
}
