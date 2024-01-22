/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanglade <hanglade@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:01:21 by hanglade          #+#    #+#             */
/*   Updated: 2024/01/22 16:01:44 by hanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

size_t	char2len(char **char2)
{
	size_t	i;

	i = 0;
	while (char2[i])
		i++;
	return (i);
}

size_t	char3len(char ***char3)
{
	size_t	i;

	i = 0;
	while (char3[i])
		i++;
	return (i);
}
