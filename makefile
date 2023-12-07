NAME = fdf
CC = gcc
FLAGS = -Wall -Wextra -Werror
SRCS = 	srcs/main.c\
		srcs/hooks/hook_funct.c\
		srcs/hooks/hook_management.c\
		srcs/map/create_map.c\
		srcs/map/map_management.c\
		srcs/render_img/apply_rotation.c\
		srcs/render_img/apply_transformations.c\
		srcs/render_img/clear_img.c\
		srcs/render_img/plot_lines_in_img.c\
		srcs/render_img/render_img.c\
		srcs/utils/error_utils.c\
		srcs/utils/free_utils.c\
		srcs/utils/length_utils.c\
		srcs/utils/projection_utils.c

OBJS = $(patsubst srcs/%.c,objs/%.o,$(SRCS))
#.SILENT ?

$(NAME) : $(OBJS) includes/fdf.h
	$(CC) $(FLAGS) -I includes/ -I libft/ -L minilibx-linux/ -L libft/ -lft -lmlx-linux -lX11 -lXext $(SRCS) -o $(NAME)	
#$(CC) $(FLAGS) -I includes/ -L minilibx-linux/ -L libft/  -lft -lmlx-linux -lX11 -lXext $(OBJS) -o $(NAME)

objs/%.o : srcs/%.c
	mkdir -p $(dir $@)
	$(CC) $(FLAGS) -c $< -o $@

# objs/%.o : srcs/%.c
# 	mkdir -p objs
# 	mkdir -p objs/hooks
# 	mkdir -p objs/map
# 	mkdir -p objs/render_img
# 	mkdir -p objs/utils
# 	$(CC) $(FLAGS) -c $< -o $@

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