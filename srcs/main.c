/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanglade <hanglade@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:33:53 by hanglade          #+#    #+#             */
/*   Updated: 2023/12/05 17:23:54 by hanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/fdf.h"

int	is_error_args(int argc, char **argv)
{
	if (argc != 2)
		exit_error("Usage: ./fdf <map_path>\n", 2);
	if (is_error_filename(argv[1]))
		exit_error("Invalid filename.\n", 2);
	return (0);
}

int close_program(t_fdf *p_fdf, char *strerr)
{
	
	if (!p_fdf->mlx)
		exit_error(strerr);
	if(p_fdf->img_struct.img)
	{
		mlx_destroy_image(p_fdf->mlx, p_fdf->img_struct.img); //liberer ce qui a ete obtenu par getdataaddress ? 
		//free le reste de img ?
	}
	if (p_fdf->win) // une telle condition marche t elle ? 
	{
		mlx_destroy_window(p_fdf->mlx, p_fdf->win);
		//free le reste de win ?
	}
    free_map_elem2(p_fdf->map_view);
    free_map_elem2(p_fdf->map); // liberer + NULL t_map_elem
    mlx_destroy_display(p_fdf->mlx);
    free(p_fdf->mlx);
	if(strerr)
		exit_error(strerr);
    return(EXIT_SUCCESS);
}

int	init_s_fdf(char *filename, t_fdf *p_fdf)
{
	p_fdf->map = get_map(filename);//
	if (!p_fdf->map)
		close_program(p_fdf, "Error : get_map()");
	p_fdf->mlx = mlx_init();
	if (!p_fdf->mlx)
		close_program(p_fdf, "Error : mlx_init()");
	p_fdf->win = mlx_new_window(p_fdf->mlx, WIDTH, HEIGHT, "Fdf");
	if (!p_fdf->win)
		close_program(p_fdf, "Error : mlx_new_window()");
	p_fdf->img_struct.img = mlx_new_image(p_fdf->mlx, WIDTH, HEIGHT);
	if (!p_fdf->img_struct.img)
		close_program(p_fdf, "Error : mlx_new_image()");
	p_fdf->img_struct.p_img_pixels = mlx_get_data_addr(p_fdf->img_struct.img, &p_fdf->img_struct.bits_per_pixel, &p_fdf->img_struct.line_len, &p_fdf->img_struct.endian);
	if (mlx_put_image_to_window(p_fdf->mlx, p_fdf->win, p_fdf->img_struct.img, 0, 0) < 0)// test d' affichage image vide ? 
		close_program(p_fdf, "Error : mlx_put_image_to_window()");
	return (1);
}

init_s_projection(t_fdf *p_fdf)
{
	t_projection_utils p_utils;
	
	p_utils = p_fdf->p_utils;
	p_utils = (t_projection_utils) {get_map_borders(p_fdf, p_fdf->map), 1, 0, 0, 30, -30, 0, 0}; //initialiser des parametres de projection scale 1 + rotation isometrique
	create_view(p_fdf, p_fdf->map, p_fdf->map_view); //faire une premiere 
	//remettre a jour les parametres p_utils avec des valeurs adaptees a la vue iso creee
	p_utils.map_borders = get_map_borders(p_fdf, p_fdf->map_view);// on recherche les bordures de la map apres la 1re projection
	p_utils.scale =// define_scale(p_utils.map_borders); //modifier la struct dans la fonction directement
	define_offsets(p_utils.map_borders, p_utils.scale); //refaire la fonction pour modifier directement les offset sans struct
}

int main(int argc, char **argv)
{
	t_fdf	fdf;
	
	is_error_args(argc, argv);
	init_s_fdf(argv[1], &fdf);
	init_s_projection(&fdf);
	mlx_loop_hook(fdf.mlx, frame_hook, &fdf);
	mlx_loop(fdf.mlx);
	return (close_program(&fdf, NULL));
}