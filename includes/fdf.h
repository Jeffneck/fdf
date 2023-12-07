#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h" //pour les macros
// # include "../minilibx-test/mlx.h" //supprimer plus tard
// # include "../minilibx-test/mlx_int.h" //supprimer plus tard
# include <fcntl.h>
# include <math.h>
# include <stdint.h> // retirable si on utilise les unsigned int plutot que uint32_t ?

// MACROS
# ifndef WIDTH
#  define WIDTH 1024
# endif //WIDTH
# ifndef HEIGHT
#  define HEIGHT 1024
# endif //HEIGHT
# ifndef SCALE_FACTOR 
#  define SCALE_FACTOR 0.85
# endif //SCALE_FACTOR
# ifndef ENDIANESS
#  define ENDIANESS 0
# endif //ENDIANESS

// STRUCTURES
//	\_	vectors

typedef struct s_2d_vector
{
	int	x;
	int	y;
}	t_2d_vector;

// typedef struct s_3d_vector
// {
// 	double		x;
// 	double		y;
// 	double		z;
// 	uint32_t	color;
// }	t_3d_vector;

// // \_	matrix
// typedef struct s_3d_matrix
// {
// 	t_3d_vector	i;
// 	t_3d_vector	j;
// 	t_3d_vector	k;
// }	t_3d_matrix;

//	\_	map
typedef struct s_map_elem
{
	int				x;
	int				y;
	int				z;
	int				depth; //je ne comprend pas ce que c'est mais dans get_map => fill_map_elem c' est considere comme une copie de z (profondeur initiale)
	uint32_t		color;
	int				end;
}	t_map_elem;

typedef struct s_map_borders
{
	int			min_x;
	int			min_y; 
	int			max_x;
	int			max_y;
}	t_map_borders;

//	\_	line ploting
typedef struct s_plot_utils
{
	int	x_diff;
	int	y_diff;
	int	x_step;
	int	y_step;
	int	decision; //parametre utile dans algo bresenham
}	t_plot;

// \_	color
typedef struct s_color
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
	uint32_t	a;
}	t_color;

typedef struct s_projection_utils
{
	t_map_borders	map_borders;// mettre dans fdf ? 
	double			scale;
	int				offset_x;
	int				offset_y;
	double			rot_x; //horizontalite = num de colonne
	double			rot_y; //verticalite = chiffe aux coordonnees [z][x]
	double			rot_z; //profondeur = num de ligne 
	double			depth;
}	t_projection_utils;

//comme on ne peut pas directement dessiner sur l'img, 
//on obtient ses data avec mlx_get_data_adress()
//on dessine directement dans les donnees de l'img 
//comme on se deplace sur les pixels par octets 
//on aura besoin de connaitre la taille des pixels et la taille des lignes en bit
//pour dessiner aux coordonees souhaitees.
typedef struct s_imgstruct
{
	void	*img; //mlx_create_img
	//donnes obtenues grace a mlx_get_data_address();
	void	*p_img_pixels;
	int		bits_per_pixel;
	int		endian;
	int		line_len;
}	t_imgstruct;

// \_	fdf
typedef struct s_fdf
{
	void				*mlx;
	void				*win;
	t_imgstruct				img_struct;
	t_map_elem			**map;
	t_map_elem			**map_view;
	t_projection_utils		p_utils;
}	t_fdf;

//*****************MAIN
int	is_error_args(int argc, char **argv);//
int close_program(t_fdf *p_fdf, char *strerr);
int	init_s_fdf(char *filename, t_fdf *p_fdf);//
void	init_s_projection(t_fdf *p_fdf);//

//*****************HOOK
//hook_management
int	manage_keyhook(int keysym, t_fdf *p_fdf);
void	frame_hook(void *param);

//hook_functions
int close_hook(t_fdf *p_fdf);
void rotation_hook(int keysym, t_fdf *p_fdf);
void translation_hook(int keysym, t_fdf *p_fdf);
void scaling_hook(int keysym, t_fdf *p_fdf);
void depthmodif_hook(int keysym, t_fdf *p_fdf);

//*****************RENDER_IMG
//render_img
void    transform_map_in_view(t_fdf *p_fdf, t_map_elem *p_view_el, t_map_elem map_el);
void    create_view(t_fdf *p_fdf, t_map_elem **map, t_map_elem **view);
void    put_view_in_img(t_fdf *p_fdf, t_map_elem **view);

//clear_img
void    clear_img(t_fdf *p_fdf, t_imgstruct img_struct); // envoyer t_img * ?

//apply_transformations
void    apply_scaling(t_map_elem *p_view_el, t_projection_utils p_utils);
void    apply_offset(t_map_elem *p_view_el, t_projection_utils p_utils);
//++add apply_depthmodif

//apply_rotation
void    apply_rot_x(t_map_elem *p_view_el, double cos_a, double sin_a);
void	apply_rot_y(t_map_elem *p_view_el, double cos_a, double sin_a);
void	apply_rot_z(t_map_elem *p_view_el, double cos_a, double sin_a);
void    apply_rotation(t_map_elem *p_view_el, t_projection_utils p_utils);

//plot_lines_in_img
void    put_pixel(t_imgstruct img_struct, int i, int j, uint32_t color); 
void    plot_line_down(t_fdf *p_fdf, t_plot plt, t_map_elem p0, t_map_elem p1);//
void    plot_line_up(t_fdf *p_fdf, t_plot plt, t_map_elem p0, t_map_elem p1);//
void    init_ploting_utils(t_plot *p_plt, t_map_elem p0, t_map_elem p1);//
void    plot_line(t_fdf *p_fdf, t_map_elem p0, t_map_elem p1);

//*****************MAPS
//map_management
t_map_elem **get_map(char *filename);

//create_map
char	*get_map_in_char1(int map_fd);//
char	**get_map_in_char2(char *map_str);//
char	***get_map_in_char3(char **map_strs);//
t_map_elem	**fill_map_elem2(char ***map_char3, t_map_elem **map_elem2);//
t_map_elem	**create_map_elem2(char ***map_char3);

//*****************UTILS
//length_utils
size_t	char2len(char **char2);
size_t	char3len(char **char3);

//free_utils
void	free_char1(char **a_char1);
void	free_char2(char ***a_map_el2);
void	free_char3(char ****a_char3);
void	free_map_elem2(t_map_elem ***a_map_el2);

//error_utils
int exit_error(char *strerr);
int	is_error_filename(char	*file_name);

//projection_utils
t_map_borders	get_map_borders(t_fdf *p_fdf, t_map_elem **map);
void	define_scale(t_projection_utils *p_utils, t_map_borders mb);
void	define_offsets(t_projection_utils *p_utils, t_map_borders mb, double scale);

# endif