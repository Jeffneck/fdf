#include "../../includes/fdf.h"

void    put_pixel(t_img img_struct, size_t col, size_t line, uint32_t color)
{
    int offset;

    offset = (img_struct.line_len * line) + (img_struct.bits_per_pixel * col / 8);
    *((uint32_t *)(img_struct.p_img_pixels + offset)) = color; 
}

void    plot_low_slope(t_fdf *p_fdf, t_plot plt, t_map_elem p0, t_map_elem p1)
{
    while (p0.x <= p1.x)
    {
        put_pixel(p_fdf->img_struct, p0.x, p0.y, p0.color);
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

void    plot_high_slope(t_fdf *p_fdf, t_plot plt, t_map_elem p0, t_map_elem p1)
{
    while (p0.y <= p1.y)
    {
        put_pixel(p_fdf->img_struct, p0.x, p0.y, p0.color);
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
void    plot_line(t_fdf *p_fdf, t_map_elem p0, t_map_elem p1)
//cas d'une ligne droite?
{
    t_plot plt;

    plt = p_fdf->p_utils;
    init_ploting_utils(&plt, p0, p1);
    // partie qu' il faudra revoir
    if (plt.x_diff > plt.y_diff)
    {
        plt.decision = 2 * plt.y_diff - plt.x_diff;
        plot_low_slope(p_fdf, plt, p0, p1);
    }
    else
    {
        plt.decision = 2 * plt.x_diff - plt.y_diff;
        plot_high_slope(p_fdf, plt, p0, p1);   
    }
}