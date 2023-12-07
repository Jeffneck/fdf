/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanglade <hanglade@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:25:57 by hanglade          #+#    #+#             */
/*   Updated: 2023/11/28 14:50:47 by hanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_pf(char c, size_t *count_char)
{
	write(1, &c, 1);
	(*count_char)++;
}

void	ft_putstr_pf(char *s, size_t *count_char)
{
	size_t	i;

	if (!s)
		s = "(null)";
	i = 0;
	while (s[i])
	{
		ft_putchar_pf(s[i], count_char);
		i++;
	}
}

void	ft_putptrhexa_pf(void *ptr, size_t *count_char)
{
	unsigned long	addr;
	char			addr_str[16];
	int				i;

	if (!ptr)
	{
		ft_putstr_pf("(nil)", count_char);
		return ;
	}
	addr = (unsigned long)ptr;
	ft_putstr_pf("0x", count_char);
	i = 0;
	while (addr)
	{
		addr_str[i++] = "0123456789abcdef"[addr % 16];
		addr = addr / 16;
	}
	while (i > 0)
		ft_putchar_pf(addr_str[--i], count_char);
}