/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanglade <hanglade@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:57:18 by hanglade          #+#    #+#             */
/*   Updated: 2023/12/07 15:04:33 by hanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*init_buffer(int fd, t_fd *fd_buffs)
{
	int	i;

	i = 0;
	fd++;
	while (i < MAX_FD && fd_buffs[i].init_flag != 0 && fd_buffs[i].fd != fd)
		i++;
	if (i == MAX_FD)
		return (NULL);
	fd_buffs[i].init_flag = 1;
	fd_buffs[i].fd = fd;
	return (fd_buffs[i].buffer);
}
