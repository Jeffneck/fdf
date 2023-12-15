#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
//# include "../minilibx-linux/mlx.h"
//# include "../minilibx-linux/mlx_int.h" //pour les macros
# include "../minilibx-test/mlx.h" //supprimer plus tard
# include "../minilibx-test/mlx_int.h" //supprimer plus tard
# include <fcntl.h>
# include <math.h>
# include <stdint.h> // retirable si on utilise les unsigned int plutot que uint32_t ?

// MACROS
# ifndef WIDTH
#  define WIDTH 1000
# endif //WIDTH
# ifndef HEIGHT
#  define HEIGHT 1000
# endif //HEIGHT
# ifndef SCALE_FACTOR 
#  define SCALE_FACTOR 0.85 //remplacer par 0.85
# endif //SCALE_FACTOR
# ifndef ENDIANESS
#  define ENDIANESS 0
# endif //ENDIANESS

// STRUCTURES
//	\_	vectors

// typedef struct s_2d_vector
// {
// 	int	x;
// 	int	y;
// }	t_2d_vector;

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
	int				proj_x;
	int				proj_y;
	int				temp_z;
	int				color;
	int				valid;
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
	int	decision;
}	t_plot;

// \_	color
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	a;
}	t_color;

typedef struct s_map_data
{
	int	width;
	int	height;
	int	center_x;
	int	center_y;
	t_map_borders		borders; 
}	t_map_data;



typedef struct s_proj
{
	t_map_borders	proj_borders; //
	double			scale;
	int				offset_x;
	int				offset_y;
	double			rot_x;
	double			rot_y;
	double			rot_z;
	double			depthfactor;
}	t_proj;

typedef struct s_projs
{
	t_proj	current;
	t_proj	last;
}	t_projs;


typedef struct s_imgstruct
{
	void	*img_mlx; 
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
	t_imgstruct			s_img_to_del;//retirer le pointeur ??
	t_imgstruct			s_new_img;
	t_map_elem			**map;
	t_map_data			map_data;
	t_projs				projs;
}	t_fdf;

//*****************COLORS
//color.c
int		strhexa_to_colorint(char *strhexa);

//*****************MAIN
int		is_error_args(int argc, char **argv);//
t_imgstruct	*init_new_img(t_fdf *p_fdf);
int		init_s_fdf(char *filename, t_fdf *p_fdf);//
void	init_s_projections(t_fdf *p_fdf, t_projs* projs);

//*****************HOOK
//hook_management
int		manage_keyhook(int keysym, t_fdf *p_fdf);
int		frame_hook(t_fdf *p_fdf);

//hook_functions
int		close_hook(t_fdf *p_fdf);
void	rotation_hook(int keysym, t_fdf *p_fdf);
void	translation_hook(int keysym, t_fdf *p_fdf);
void	scaling_hook(int keysym, t_fdf *p_fdf);
void	depthmodif_hook(int keysym, t_fdf *p_fdf);

//*****************RENDER_IMG
//render_img
void    transform_proj_mapelem(t_fdf *p_fdf, t_map_elem *p_map_el, int flag);
int     transform_base_mapelem(t_fdf *p_fdf, t_map_elem *p_map_el);
void    put_view_in_img(t_fdf *p_fdf, t_imgstruct *p_img, t_map_elem **map); 

//apply_transformations
void	apply_scaling(t_map_elem *p_map_el, t_proj proj);
void	apply_offset(t_map_elem *p_map_el, t_proj proj);
void	apply_depthmodif(t_map_elem *p_map_el, t_proj proj);

//apply_rotation
void    apply_rot_x(t_map_elem *p_map_el, double cos_a, double sin_a);
void	apply_rot_y(t_map_elem *p_map_el, double cos_a, double sin_a);
void	apply_rot_z(t_map_elem *p_view_el, double cos_a, double sin_a);
void    apply_rotation(t_map_elem *p_map_el, t_proj proj);

//plot_lines_in_img
void    put_pixel(t_imgstruct *p_img, int col, int line, int color); 
void    plot_low_slope(t_imgstruct *p_img, t_plot plt, t_map_elem p0, t_map_elem p1);
void    plot_high_slope(t_imgstruct *p_img, t_plot plt, t_map_elem p0, t_map_elem p1);
void    init_ploting_utils(t_plot *p_plt, t_map_elem p0, t_map_elem p1);
void    plot_line(t_imgstruct *p_img, t_map_elem p0, t_map_elem p1);

//*****************MAPS

//center_map
void    center_map(t_map_data md, t_map_elem **map);

//get_map
t_map_elem	**fill_map_elem2(char ***map_char3, t_map_elem **map_elem2);//penser a terminer chaque ligne par un NULL
t_map_elem	**create_map_elem2(char ***map_char3);
t_map_elem **get_map(char *filename);


//file_to_charmap
char	*get_map_in_char1(int map_fd);//
char	**get_map_in_char2(char *map_str);//
char	***get_map_in_char3(char **map_strs);//


//*****************UTILS
//length_utils
size_t	char2len(char **char2);
size_t	char3len(char ***char3);

//free_utils
void	free_char1(char **a_char1);
void	free_char2(char ***a_map_el2);
void	free_char3(char ****a_char3);
void	free_map_elem2(t_map_elem ***a_map_el2);

//error_utils
int exit_error(char *strerr);
int	is_error_filename(char	*file_name);

//projection_utils
t_map_data	get_map_data(t_map_elem **map);
void	define_scale(t_proj *p_proj, t_map_data md);
void	define_offsets(t_proj *p_proj, t_map_data mb, double scale);
void	init_proj_map(t_fdf *p_fdf, t_map_elem **map); //dans le main pour le moment

//closing_utils
int		close_program(t_fdf *p_fdf, char *strerr);
void	clean_close_imgstruct(t_fdf *p_fdf, t_imgstruct *p_imgtoclear);
void	clean_close_window(t_fdf *p_fdf, void *p_win);

# endif
