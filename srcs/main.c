/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanglade <hanglade@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:33:53 by hanglade          #+#    #+#             */
/*   Updated: 2023/12/19 16:22:12 by hanglade         ###   ########.fr       */
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

t_imgstruct	*init_new_img(t_fdf *p_fdf)
{
	t_imgstruct *img;

	img = ft_calloc(1, sizeof(t_imgstruct));
	img->img_mlx = mlx_new_image(p_fdf->mlx, WIDTH, HEIGHT); 
	if (!img->img_mlx)
		close_program(p_fdf, "Error : mlx_new_image()");//bien fermer la seconde image lors de close
	//img->valid = 1; utile pour free ou pas ??
	img->p_img_pixels = mlx_get_data_addr(img->img_mlx, &(img->bits_per_pixel), &(img->line_len), &(img->endian));
	if (!img->p_img_pixels) ////si get data address ne produit pas d'erreurs cette verif est inutile
		close_program(p_fdf, "Error : mlx_new_image()");
	return (img);
}

void	init_s_projections(t_fdf *p_fdf, t_projs* projs)
{
	ft_printf("main : init_s_projection\n");//
	
	//projs->last = NULL; //deja mis a 0 car fdf le contenait
	// if (p_fdf->map_data.width >= WIDTH || p_fdf->map_data.height >= HEIGHT) //inutil + bloque des maps legit
	// 	close_program(p_fdf, "Error : window too small");
	ft_printf("main : init_s_projection\n");//
	define_scale(&(projs->current), p_fdf->map_data);
	ft_printf("main : init_s_projection\n");//
	define_offsets(&(projs->current), p_fdf->map_data, projs->current.scale);
	projs->current.rot_x = -0.52;//verifier les valeurs de rot
	projs->current.rot_y = 0.52; 
	projs->current.rot_z = 0;
	projs->current.depthfactor = 1;
	ft_printf("main : init_s_projection\n");//
}

int	init_s_fdf(char *filename, t_fdf *p_fdf)
{
	ft_printf("main : init_s_fdf\n");//
	p_fdf->map = get_map(filename);
	if (!p_fdf->map)
		close_program(p_fdf, "Error : get_map()");
	p_fdf->map_data = get_map_data(p_fdf->map);
	center_map(p_fdf->map_data, p_fdf->map);
	p_fdf->mlx = mlx_init();
	if (!p_fdf->mlx)
		close_program(p_fdf, "Error : mlx_init()");
	p_fdf->win = mlx_new_window(p_fdf->mlx, WIDTH, HEIGHT, "Fdf");
	if (!p_fdf->win)
		close_program(p_fdf, "Error : mlx_new_window()");
	p_fdf->s_new_img = *init_new_img(p_fdf);
	if (mlx_put_image_to_window(p_fdf->mlx, p_fdf->win, p_fdf->s_new_img.img_mlx, 0, 0) < 0)// test d' affichage image vide ?
		close_program(p_fdf, "Error : mlx_put_image_to_window()");
	init_s_projections(p_fdf, &(p_fdf->projs));
	// init_proj_map(p_fdf, p_fdf->map); //semble inutile ? 
	// put_view_in_img(p_fdf, &(p_fdf->s_new_img), p_fdf->map);// semble inutile ?
	return (1);
}

int main(int argc, char **argv)
{
	t_fdf	*p_fdf;

	p_fdf = ft_calloc(1, sizeof(t_fdf));
	// ft_memset(&fdf, 0, sizeof(t_fdf));
	
	// fdf = (t_fdf){
    // .mlx = NULL, // Initialisez mlx avec la valeur appropriée
    // .win = NULL, // Initialisez win avec la valeur appropriée
    // .s_img_to_del = NULL, // Initialisez s_imgtoclean avec la valeur appropriée
    // .s_new_img = NULL, // Initialisez s_new_img avec la valeur appropriée
    // .map = NULL, // Initialisez map avec la valeur appropriée
    // .map_data = (t_map_data) {0, 0, 0, 0, (t_map_borders) {0, 0, 0, 0}}, // Initialisez map_data avec les valeurs appropriées
    // .projs = (t_projs) {NULL, NULL}, // Initialisez projs avec les valeurs appropriées
	// };
	is_error_args(argc, argv);
	init_s_fdf(argv[1], p_fdf);
    mlx_hook(p_fdf->win, 17, 0, close_hook, p_fdf); //bouton fermeture fenetre
	mlx_hook(p_fdf->win, 2, 1L<<0, manage_keyhook, p_fdf);
	mlx_loop_hook(p_fdf->mlx, frame_hook, p_fdf); // vraie version 
	mlx_loop(p_fdf->mlx);//remettre
	return (close_program(p_fdf, NULL));
}