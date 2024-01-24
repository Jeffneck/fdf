/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanglade <hanglade@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:33:53 by hanglade          #+#    #+#             */
/*   Updated: 2024/01/24 10:40:25 by hanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_imgstruct	init_new_img(t_fdf *p_fdf)
{
	t_imgstruct	img;

	ft_bzero(&(img), sizeof(t_imgstruct));
	img.img_mlx = mlx_new_image(p_fdf->mlx, WIDTH, HEIGHT);
	if (!img.img_mlx)
		close_program(p_fdf, "Error : mlx_new_image()\n");
	img.p_img_pixels = mlx_get_data_addr(img.img_mlx, &(img.bits_per_pixel),
			&(img.line_len), &(img.endian));
	if (!img.p_img_pixels)
		close_program(p_fdf, "Error : mlx_new_image()\n");
	return (img);
}

void	init_s_projections(t_fdf *p_fdf, t_projs *projs)
{
	define_scale(&(projs->current), p_fdf->map_data);
	define_offsets(&(projs->current), p_fdf->map_data, projs->current.scale);
	projs->current.rot_x = -0.52;
	projs->current.rot_y = 0.52;
	projs->current.rot_z = 0;
	projs->current.depthfactor = 1;
}

int	init_s_fdf(char *filename, t_fdf *p_fdf)
{
	p_fdf->map = get_map(filename);
	if (!p_fdf->map)
		close_program(p_fdf, "Error : get_map()\n");
	p_fdf->map_data = get_map_data(p_fdf->map);
	center_map(p_fdf->map_data, p_fdf->map);
	p_fdf->mlx = mlx_init();
	if (!p_fdf->mlx)
		close_program(p_fdf, "Error : mlx_init()");
	p_fdf->win = mlx_new_window(p_fdf->mlx, WIDTH, HEIGHT, "Fdf\n");
	if (!p_fdf->win)
		close_program(p_fdf, "Error : mlx_new_window()\n");
	p_fdf->s_new_img = init_new_img(p_fdf);
	if (mlx_put_image_to_window(p_fdf->mlx, p_fdf->win,
			p_fdf->s_new_img.img_mlx, 0, 0) < 0)
		close_program(p_fdf, "Error : mlx_put_image_to_window()\n");
	init_s_projections(p_fdf, &(p_fdf->projs));
	return (1);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;
	t_fdf	*p_fdf;

	ft_bzero(&fdf, sizeof(fdf));
	p_fdf = &fdf;
	is_error_args(argc, argv);
	init_s_fdf(argv[1], p_fdf);
	mlx_hook(p_fdf->win, 17, 0, close_hook, p_fdf);
	mlx_hook(p_fdf->win, 2, 1L << 0, manage_keyhook, p_fdf);
	mlx_loop_hook(p_fdf->mlx, frame_hook, p_fdf);
	mlx_loop(p_fdf->mlx);
	return (close_program(p_fdf, NULL));
}
