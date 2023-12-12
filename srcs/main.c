/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanglade <hanglade@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:33:53 by hanglade          #+#    #+#             */
/*   Updated: 2023/12/08 16:43:43 by hanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/fdf.h"

int	is_error_args(int argc, char **argv)
{
	ft_printf("main : is_error_args\n");//
	if (argc != 2)
		exit_error("Usage: ./fdf <map_path>\n");
	if (is_error_filename(argv[1]))
		exit_error("Invalid filename.\n");
	return (0);
}

int close_program(t_fdf *p_fdf, char *strerr)
{
	ft_printf("main : close_program\n");//
	
	if (!p_fdf->mlx)
		exit_error(strerr);
	if(p_fdf->img_struct.img)//////////
	{
		mlx_destroy_image(p_fdf->mlx, p_fdf->img_struct.img); //liberer ce qui a ete obtenu par getdataaddress ? 
		//free le reste de img ?
	}
	if (p_fdf->win) // une telle condition marche t elle ? 
	{
		mlx_destroy_window(p_fdf->mlx, p_fdf->win);
		//free le reste de win ?
	}
    free_map_elem2(&(p_fdf->map_view));
    free_map_elem2(&(p_fdf->map)); // liberer + NULL t_map_elem
    mlx_destroy_display(p_fdf->mlx);
    free(p_fdf->mlx);
	if(strerr)
		exit_error(strerr);
    return(EXIT_SUCCESS);
}

int	init_s_fdf(char *filename, t_fdf *p_fdf)
{
	ft_printf("main : init_s_fdf\n");//
	p_fdf->map = get_map(filename);
	if (!p_fdf->map)
		close_program(p_fdf, "Error : get_map()");
	p_fdf->map_view = get_map(filename);//view est cree de la meme maniere que get map pour le 1er appel (il serait possible de faire un genre de memdup ou calloc de la bonne taille ?)
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
	// if (mlx_put_image_to_window(p_fdf->mlx, p_fdf->win, p_fdf->img_struct.img, 0, 0) < 0)// test d' affichage image vide ? //code a garder
	// 	close_program(p_fdf, "Error : mlx_put_image_to_window()");
	return (1);
}

void	init_s_projection(t_fdf *p_fdf)
{
	ft_printf("main : init_s_projection\n");//
	t_projection_utils *p_utils;
	
	p_utils = &(p_fdf->p_utils);
	*p_utils = (t_projection_utils) {get_map_borders(p_fdf->map), 1, 0, 0, 0.52, 0, 0, 0}; //initialiser des parametres de projection scale 1 + rotation isometrique 0, 30, -30
	//remettre a jour les parametres p_utils avec des valeurs adaptees a la vue iso creee
	
	//p_utils->map_borders = get_map_borders(p_fdf->map);// test, la ligne du dessous est la bonne
	//p_utils.scale = define_scale(p_utils.map_borders); //modifier la struct dans la fonction directement
	create_view(p_fdf, p_fdf->map, p_fdf->map_view); //faire une premiere vue avec sans la mise a l'echelle et offset 
	p_utils->map_borders = get_map_borders(p_fdf->map_view);// on recherche les bordures de la map apres la 1re projection
	define_scale(p_utils, p_utils->map_borders);
	// create_view(p_fdf, p_fdf->map, p_fdf->map_view); //faire une premiere vue avec sans la mise a l'echelle et offset 
	//p_utils->map_borders = get_map_borders(p_fdf->map_view);// on recherche les bordures de la map apres la 1re projection
	define_offsets(p_utils, p_utils->map_borders, p_utils->scale);
	create_view(p_fdf, p_fdf->map, p_fdf->map_view); //faire une premiere vue avec sans la mise a l'echelle et offset 
}

int main(int argc, char **argv)
{
	t_fdf	fdf;
	
	//fdf = (t_fdf) {0, 0, 0, 0, 0, 0}; //inutile ?
	is_error_args(argc, argv);
	init_s_fdf(argv[1], &fdf);
	init_s_projection(&fdf);
	// mlx_key_hook(fdf.win, manage_keyhook, &fdf);// test
	//mlx_key_hook(fdf.win, close_hook, &fdf); //test
	mlx_hook(fdf.win, 2, 1L<<0, manage_keyhook, &fdf);
	//mlx_loop_hook(fdf.mlx, frame_hook, &fdf); // vraie version 
	mlx_loop(fdf.mlx);
	return (close_program(&fdf, NULL));
}