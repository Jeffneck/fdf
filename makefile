# Nom de l'exécutable
NAME = fdf

# Fichiers d'en-tête
INC = includes/fdf.h

INCFLAGS = -I includes

# Bibliothèque
LIB = libft/libft.a minilibx-linux/libmlx_Linux.a minilibx-linux/libmlx.a 

LDFLAGS = -Llibft -lft -Lminilibx-linux -lmlx_Linux -lX11 -lXext -lm -lmlx

# Compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall -Wextra -Werror -O3 $(INC)

# Répertoires source
SRCDIR = srcs
OBJDIR = objs

# Liste des fichiers source
SRCS =	main.c \
		colors/color.c \
		hooks/hook_funct.c \
		hooks/hook_management.c \
		map/center_map.c \
		map/file_to_charmap.c \
		map/get_map.c \
		render_img/apply_rotation.c \
		render_img/apply_transformations.c \
		render_img/plot_lines_in_img.c \
		render_img/render_img.c \
		utils/closing_utils.c \
		utils/error_utils.c \
		utils/free_utils.c \
		utils/length_utils.c \
		utils/projection_utils.c

# Chemin complet des fichiers source et objets
SRCFILES = $(addprefix $(SRCDIR)/,$(SRCS))
OBJFILES = $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))


# Règles de construction des objets
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INC)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) $(DEPFLAGS) -c $< -o $@

# Règles de construction de l'executable
$(NAME): $(OBJFILES) $(LIB) $(INC)
	$(CC) $(CFLAGS) $(OBJFILES) $(INCLUDES) $(LDFLAGS) -o $(NAME)


$(LIB): force
	make -C libft
	make -C minilibx-linux

# Règles supplémentaires
force:

all: $(NAME)

clean:
	rm -rf $(OBJDIR)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re force