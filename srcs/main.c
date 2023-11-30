/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanglade <hanglade@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:33:53 by hanglade          #+#    #+#             */
/*   Updated: 2023/11/28 17:35:40 by hanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/fdf.h"

int	check_args_errors(int argc, char **argv)
{
	if (argc != 2)
		return (ft_putstr_fd("Usage: ./fdf <map_path>\n", 2), 1);
	if (check_file_name_error(argv[1]))
		return (ft_putstr_fd("Invalid filename.\n", 2), 1);
}

int	init_s_fdf(char *filename, t_fdf *p_fdf)
{
	p_fdf->map = get_map(filename);//
	if (!p_fdf->map)
		return (0);
	p_fdf->mlx = mlx_init();
	if (!p_fdf->mlx)
		return (manage_errors(), 0);// ou juste manage_errors() si je met un exit (Failure)
	p_fdf->win = mlx_new_window(p_fdf->mlx, WIDTH, HEIGHT, "Fdf");
	if (!p_fdf->win)
		return (manage_errors(), 0);
	p_fdf->img_struct.img = mlx_new_image(p_fdf->mlx, WIDTH, HEIGHT);
	if (!p_fdf->img)
		return (manage_errors(), 0);
	p_fdf->img_struct.p_img_pixels = mlx_get_data_addr(p_fdf->img_struct.img, &p_fdf->img_struct.bits_per_pixel, &p_fdf->img_struct.line_len, &p_fdf->img_struct.endian)
	if (mlx_put_image_to_window(p_fdf->mlx, p_fdf->win, p_fdf->img_struct.img, 0, 0) < 0)// test d' affichage image vide ? 
		return (manage_errors(), 0);
	return (1);
}

init_s_projection(t_fdf *p_fdf)
{
	t_projection_utils p_utils;
	
	p_utils = p_fdf->p_utils;
	p_utils.map_borders = get_map_borders(p_fdf->map);//
	p_utils.scale = define_scale(p_utils.map_borders); //
	p_utils.offset = define_offset(p_utils.map_borders, p_utils.scale);
	p_utils.depth = 0;
	//on se place directement en vue isometrique
	p_utils.rot_x = 30;
	p_utils.rot_y = -30;
	p_utils.rot_z = 0;
	
	
}

int main(int argc, char **argv)
{
	t_fdf	fdf;
	
	if (!check_args_errors(argc, argv) || !init_s_fdf(argv[1], &fdf))
		return (1);
	init_s_projection(&fdf);
	mlx_loop_hook(fdf.mlx, frame_hooks, &fdf);
	mlx_loop(fdf.mlx);
	
}