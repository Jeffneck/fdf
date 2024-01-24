/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanglade <hanglade@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:01:55 by hanglade          #+#    #+#             */
/*   Updated: 2024/01/24 10:30:49 by hanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

int	is_error_args(int argc, char **argv)
{
	if (argc != 2)
		exit_error("Usage: ./fdf <map_path>\n");
	if (is_error_filename(argv[1]))
		exit_error("Invalid filename.\n");
	return (0);
}

int	exit_error(char *strerr)
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
