#include "../../includes/fdf.h"

void    put_pixel(t_imgstruct *p_img, int col, int line, int color) //il faut surement envoyer *p_img 
{
	// ft_printf("plot_lines in img : put_pixel x = %d y = %d\n", col, line);//
    int offset;

    offset = (p_img->line_len * line) + (p_img->bits_per_pixel * col / 8);
    if (col >= 0 && col < WIDTH && line >= 0 && line < HEIGHT)
        *((int *)(p_img->p_img_pixels + offset)) = color; 
}

void    plot_low_slope(t_imgstruct *p_img, t_plot plt, t_map_elem p0, t_map_elem p1)
{
	// ft_printf("plot_lines in img : plot_low_slope\n");//
    while (p0.proj_x != p1.proj_x)//erreur dans la condition ? 
    {
	    // ft_printf("want to put pixel in proj_x = %d projy = %d color = %d\n", p0.proj_x, p0.proj_y, p0.color);//
        if (p0.proj_x >= 0 && p0.proj_x < WIDTH && p0.proj_y >= 0 && p0.proj_y < HEIGHT) 
            put_pixel(p_img, p0.proj_x, p0.proj_y, p0.color); //vraie commande a garder
        p0.proj_x += plt.x_step;
        if (plt.decision <= 0)
            plt.decision += 2 * plt.y_diff;
        else
        {
            p0.proj_y += plt.y_step;
            plt.decision += 2 * (plt.y_diff - plt.x_diff);
        }
    }
}

void    plot_high_slope(t_imgstruct *p_img, t_plot plt, t_map_elem p0, t_map_elem p1)
{
	// ft_printf("plot_lines in img : plot_high_slope\n");//
	// ft_printf("AAAAAAAp0 projx %d p0 projy %d p1 projx %d p1 projy %d \n", p0.proj_x, p0.proj_y, p1.proj_x, p1.proj_y);//
    int gradient; 

    while (p0.proj_y != p1.proj_y) // <= ne marche pas si on fait -1 
    {
        gradient = create_color_gradient(abs(p0.proj_y - p1.proj_y), plt.y_diff, p0.color, p1.color);
        // ft_printf("want to put pixel in proj x = %d proj_y = %d color = %d\n", p0.proj_x, p0.proj_y, p0.color);//
        if (p0.proj_x >= 0 && p0.proj_x < WIDTH && p0.proj_y >= 0 && p0.proj_y < HEIGHT) //mettre ca dans put pixel
            put_pixel(p_img, p0.proj_x, p0.proj_y, gradient);
        p0.proj_y += plt.y_step;
        if (plt.decision <= 0)
            plt.decision += 2 * plt.x_diff;
        else
        {
            p0.proj_x += plt.x_step;
            plt.decision += 2 * (plt.x_diff - plt.y_diff);
        }
    }
}

void    init_ploting_utils(t_plot *p_plt, t_map_elem p0, t_map_elem p1)
{
	// ft_printf("plot_lines in img : init_ploting_utils\n");//
    p_plt->x_diff = abs(p1.proj_x - p0.proj_x);
    p_plt->y_diff = abs(p1.proj_y - p0.proj_y);
    //methode peu optimisee car on se sert soit de x_step soit y_step mais en soit c'est plus clair comme ça 
    if (p1.proj_x > p0.proj_x)
        p_plt->x_step = 1;
    else
        p_plt->x_step = -1;
    if (p1.proj_y > p0.proj_y)
        p_plt->y_step = 1;
    else
        p_plt->y_step = -1;
}
void    plot_line(t_imgstruct *p_img, t_map_elem p0, t_map_elem p1)
{
//cas d'une ligne droite?
	// ft_printf("plot_lines in p_img : plot_line\n");//
    t_plot plt;

    init_ploting_utils(&plt, p0, p1);
    // ft_printf("ZZZZZZZZZp0 projx %d p0 projy %d p1 projx %d p1 projy %d \n", p0.proj_x, p0.proj_y, p1.proj_x, p1.proj_y);//
    // plot_high_slope(p_img, plt, p0, p1); // test
    // partie qu' il faudra revoir
    if (plt.x_diff >= plt.y_diff)
    {
        plt.decision = 2 * plt.y_diff - plt.x_diff;
        plot_low_slope(p_img, plt, p0, p1);
    }
    else
    {
        plt.decision = 2 * plt.x_diff - plt.y_diff;
        plot_high_slope(p_img, plt, p0, p1);   
    }
    //mlx_put_image_to_window(p_fdf->mlx, p_fdf->win, p_fdf->img_struct.img, 0, 0); // test a retirer plus tard !!
    //sleep(1); //pour voir ce qu' il se passe
}