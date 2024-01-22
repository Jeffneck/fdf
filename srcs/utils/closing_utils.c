/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanglade <hanglade@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:04:06 by hanglade          #+#    #+#             */
/*   Updated: 2024/01/22 16:04:18 by hanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

int	close_program(t_fdf *p_fdf, char *strerr)
{
	if (!p_fdf->mlx)
		exit_error(strerr);
	clean_close_imgstruct(p_fdf, &(p_fdf->s_img_to_del));
	clean_close_imgstruct(p_fdf, &(p_fdf->s_new_img));
	if (&(p_fdf->win))
		mlx_destroy_window(p_fdf->mlx, p_fdf->win);
	free_map_elem2(&(p_fdf->map));
	mlx_destroy_display(p_fdf->mlx);
	free(p_fdf->mlx);
	if (strerr)
		exit_error(strerr);
	exit(EXIT_SUCCESS);
}

void	clean_close_imgstruct(t_fdf *p_fdf, t_imgstruct *p_img)
{
	if (p_img->img_mlx)
		mlx_destroy_image(p_fdf->mlx, p_img->img_mlx);
	p_img->img_mlx = NULL;
}
