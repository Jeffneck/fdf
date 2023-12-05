#include "../../includes/fdf.h"

void    put_pixel(t_img img_struct, int i, int j, uint32_t color)
{
    int offset;

    offset = (img_struct.line_len * i) + (img_struct.bits_per_pixel * j / 8);
    *((uint32_t *)(img_struct.p_img_pixels + offset)) = color; 
}

void    plot_line_down(t_fdf *p_fdf, t_plot plt, t_map_elem p0, t_map_elem p1)
{
    //meme fonction que plot line up pour le moment mais il faut surement apporter des modifications
    while (p0.x <= p1.x)
    {
        put_pixel(p_fdf->img_struct, p0.x, p0.y, p0.color);
        p0.x += plt.x_step;
        plt.e += plt.y_diff;
        if (plt.e > plt.x_diff)
        {
            p0.y += plt.y_step;
            plt.e -= plt.x_diff;
        }
    }
}

void    plot_line_up(t_fdf *p_fdf, t_plot plt, t_map_elem p0, t_map_elem p1)
{
    while (p0.x <= p1.x)
    {
        put_pixel(p_fdf->img_struct, p0.x, p0.y, p0.color);
        p0.x += plt.x_step;
        plt.e += plt.y_diff;
        if (plt.e > plt.x_diff)
        {
            p0.y += plt.y_step;
            plt.e -= plt.x_diff;
        }
    }
}

void    init_ploting_utils(t_plot *plt, t_map_elem p0, t_map_elem p1)
{
    plt->x_diff = abs(p1.x - p0.x);
    plt->y_diff = abs(p1.y - p0.y);
    plt->e = 0;
    if (p1.x > p0.x)
        plt->x_step = 1;
    else
        plt->x_step = -1; 
    if (p1.y > p0.y)
        plt->y_step = 1;
    else
        plt->y_step = -1;
}

void    plot_line(t_fdf *p_fdf, t_map_elem p0, t_map_elem p1)
{
    t_plot plt;
    init_ploting_utils(&plt, p0, p1);
    // partie qu' il faudra revoir
    if (plt.x_diff > plt.y_diff)
        plot_line_down(p_fdf, plt, p0, p1);
    else
        plot_line_up(p_fdf, plt, p0, p1);
}