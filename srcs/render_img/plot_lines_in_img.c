#include "../../includes/fdf.h"

void    put_pixel(t_imgstruct *p_img, int col, int line, int color) //il faut surement envoyer *p_img 
{
	ft_printf("plot_lines in img : put_pixel x = %d y = %d\n", col, line);//
    int offset;

    offset = (p_img->line_len * line) + (p_img->bits_per_pixel * col / 8);
    if (col >= 0 && col < WIDTH && line >= 0 && line < HEIGHT)
        *((int *)(p_img->p_img_pixels + offset)) = color; 
}

void    plot_low_slope(t_imgstruct *p_img, t_plot plt, t_map_elem p0, t_map_elem p1)
{
	ft_printf("plot_lines in img : plot_low_slope\n");//
    while (p0.x != p1.x)//erreur dans la condition ? 
    {
	    // ft_printf("want to put pixel in x = %d y = %d color = %d\n", p0.x, p0.y, p0.color);//
        if (p0.x >= 0 && p0.x < WIDTH && p0.y >= 0 && p0.y < HEIGHT) 
            put_pixel(p_img, p0.x, p0.y, p0.color); //vraie commande a garder
        p0.x += plt.x_step;
        if (plt.decision <= 0)
            plt.decision += 2 * plt.y_diff;
        else
        {
            p0.y += plt.y_step;
            plt.decision += 2 * (plt.y_diff - plt.x_diff);
        }
    }
}

void    plot_high_slope(t_imgstruct *p_img, t_plot plt, t_map_elem p0, t_map_elem p1)
{
	ft_printf("plot_lines in img : plot_high_slope\n");//
    while (p0.y != p1.y) // <= ne marche pas si on fait -1 
    {
	    // ft_printf("want to put pixel in x = %d y = %d color = %d\n", p0.x, p0.y, p0.color);//
        if (p0.x >= 0 && p0.x < WIDTH && p0.y >= 0 && p0.y < HEIGHT) //mettre ca dans put pixel
            put_pixel(p_img, p0.x, p0.y, p0.color);
        p0.y += plt.y_step;
        if (plt.decision <= 0)
            plt.decision += 2 * plt.x_diff;
        else
        {
            p0.x += plt.x_step;
            plt.decision += 2 * (plt.x_diff - plt.y_diff);
        }
    }
}

void    init_ploting_utils(t_plot *p_plt, t_map_elem p0, t_map_elem p1)
{
	// ft_printf("plot_lines in img : init_ploting_utils\n");//
    p_plt->x_diff = abs(p1.x - p0.x);
    p_plt->y_diff = abs(p1.y - p0.y);
    //methode peu optimisee car on se sert soit de x_step soit y_step mais en soit c'est plus clair comme ça 
    if (p1.x > p0.x)
        p_plt->x_step = 1;
    else
        p_plt->x_step = -1;
    if (p1.y > p0.y)
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
    // partie qu' il faudra revoir
    if (plt.x_diff > plt.y_diff)
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