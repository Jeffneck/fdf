#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdint.h> // retirable si on utilise les unsigned int plutot que uint32_t ?

// MACROS
# define WIDTH 1024
# define HEIGHT 1024
# ifndef ENDIANESS
#  define ENDIANESS 0 //0: little, 1: big
# endif

// STRUCTURES
//	\_	vectors

typedef struct s_2d_vector
{
	int	x;
	int	y;
}	t_2d_vector;

typedef struct s_3d_vector
{
	double		x;
	double		y;
	double		z;
	uint32_t	color;
}	t_3d_vector;

// \_	matrix
typedef struct s_3d_matrix
{
	t_3d_vector	i;
	t_3d_vector	j;
	t_3d_vector	k;
}	t_3d_matrix;

//	\_	map
typedef struct s_map_elem
{
	int				x;
	int				y;
	int				z;
	int				original_depth;
	uint32_t		color;
	int				end;
}	t_map_elem;

typedef struct s_map_borders
{
	t_2d_vector	min;
	t_2d_vector	max;
}	t_map_borders;

//	\_	offset
typedef struct s_offset
{
	int	x;
	int	y;
}	t_offset;

//	\_	line ploting
typedef struct s_plot_utils
{
	int	dx;
	int	dy;
	int	xi;
	int	yi;
	int	d;
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
	t_map_borders	map_borders;// utile ?
	double			scale;
	t_offset		offset;
	double			rot_x; //horizontalite = num de colonne
	double			rot_y; //verticalite = chiffe aux coordonnees [z][x]
	double			rot_z; //profondeur = num de ligne 
	double			depth;
}	t_projection_utils;

// \_	fdf
typedef struct s_fdf
{
	void				*mlx;
	void				*win;
	void				*img;
	t_map_elem			**map;
	t_map_elem			**map_view;
	t_projection_utils		p_utils;
}	t_fdf;

	// on ne met pas t_map_elem		**proj_map; pour limiter les allocations memoire
# endif