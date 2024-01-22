NAME = fdf

CC = gcc

FLAGS = -Wall -Wextra -Werror 

LIB	= libft/libft.a

SRCS = 	srcs/main.c\
		srcs/colors/color.c\
		srcs/hooks/hook_funct.c\
		srcs/hooks/hook_management.c\
		srcs/map/center_map.c\
		srcs/map/file_to_charmap.c\
		srcs/map/get_map.c\
		srcs/render_img/apply_rotation.c\
		srcs/render_img/apply_transformations.c\
		srcs/render_img/plot_lines_in_img.c\
		srcs/render_img/render_img.c\
		srcs/utils/closing_utils.c\
		srcs/utils/error_utils.c\
		srcs/utils/free_utils.c\
		srcs/utils/length_utils.c\
		srcs/utils/projection_utils.c\


OBJS = $(patsubst srcs/%.c,objs/%.o,$(SRCS))


$(NAME) : $(OBJS) $(LIB) includes/fdf.h
	make -C minilibx-test/
	$(CC) $(FLAGS) $(OBJS) -I includes/ -Llibft -lft -Lminilibx-test/ -lmlx_Linux -o $(NAME) -lX11 -lXext -lm -lmlx

objs/%.o : srcs/%.c
	mkdir -p $(dir $@)
	$(CC) $(FLAGS) -c $< -o $@

$(LIB) :	force
	make -C libft

force :

all : $(NAME)

clean :
	rm -rf objs/
	make -C libft/ clean

fclean : clean
	rm -f $(NAME)
	make -C libft/ fclean

re : fclean all

.PHONY : clean fclean re all test force