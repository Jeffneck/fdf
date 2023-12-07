# include "../../includes/fdf.h"

void    clear_img(t_imgstruct img_struct)
{
    size_t  line;
    size_t  col;

    line = 0; 
    while (line < HEIGHT)
    {
        col = 0; 
        while (col < WIDTH)
        {
            put_pixel(img_struct, col, line, 0);
            col++;
        }
        line++;
    }
}