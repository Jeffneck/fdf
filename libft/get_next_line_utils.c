/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanglade <hanglade@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:57:18 by hanglade          #+#    #+#             */
/*   Updated: 2023/11/28 15:13:48 by hanglade         ###   ########.fr       */
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

size_t	ft_strlen(const char *str)
{
	size_t	length;

	length = 0;
	while (str[length] != '\0')
		length++;
	return (length);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	destlen;
	size_t	srclen;
	size_t	i;

	destlen = 0;
	srclen = 0;
	i = 0;
	while (dst[destlen] != '\0' && destlen < size)
		destlen++;
	while (src[srclen] != '\0')
		srclen++;
	if (size == 0 || destlen == size)
		return (size + srclen);
	while (src[i] != '\0' && destlen + i < size - 1)
	{
		dst[destlen + i] = src[i];
		i++;
	}
	dst[destlen + i] = '\0';
	return (destlen + srclen);
}

char	*ft_strdup(const char *str)
{
	char	*result;
	size_t	length;

	length = ft_strlen(str);
	result = (char *)malloc((length + 1) * sizeof(char));
	if (!result)
		return (NULL);
	length = 0;
	while (str[length] != '\0')
	{
		result[length] = str[length];
		length++;
	}
	result[length] = '\0';
	return (result);
}
