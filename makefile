NAME = fdf
CC = gcc
FLAGS = -Wall -Wextra -Werror
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
# srcs/colors/color_gradiant.c


OBJS = $(patsubst srcs/%.c,objs/%.o,$(SRCS))
#.SILENT ?

$(NAME) : $(OBJS) includes/fdf.h
	make -C libft/
# make -C minilibx-linux/
# $(CC) $(FLAGS) $(OBJS) -g3 -I includes/ -Llibft -lft -Lminilibx-linux/ -lmlx_Linux -o $(NAME) -lX11 -lXext -lm -lmlx
	make -C minilibx-test/
	$(CC) $(FLAGS) $(OBJS) -g -I includes/ -Llibft -lft -Lminilibx-test/ -lmlx_Linux -o $(NAME) -lX11 -lXext -lm -lmlx
#retirer g3 en version finale

objs/%.o : srcs/%.c
	mkdir -p $(dir $@)
	$(CC) $(FLAGS) -c $< -o $@

all : $(NAME)

clean :
	rm -rf objs/
	make -C libft/ clean

fclean : clean
	rm -f $(NAME)
	make -C libft/ fclean
re : fclean all
test : re
	./fdf
.PHONY : clean fclean re all test