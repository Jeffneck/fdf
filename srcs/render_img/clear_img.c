# include "../includes/fdf.h"

void    clear_img(t_fdf *p_fdf, t_imgstruct img_struct)
{
    size_t  line;
    size_t  col;
    

    line = 0; 
    while (view[line])
    {
        j = 0; 
        while (view[line][col].end != 1)
        {
            put_pixel(img_struct, col, line, 0); // peut etre faut il donner un pointeur vers img struct
            j++;
        }
        i++;
    }
}