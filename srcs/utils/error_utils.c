#include "../../includes/fdf.h"



int exit_error(char *strerr)
{
	ft_putstr_fd(strerr, 2);
	exit(EXIT_FAILURE);
}

int	is_error_filename(char	*file_name)
{
	size_t	file_name_len;

	file_name_len = ft_strlen(file_name);
	if (file_name_len < 4)
		return (1);
	if (ft_strncmp(&file_name[file_name_len - 4], ".fdf", 4))
		return (1);
	return (0);
}