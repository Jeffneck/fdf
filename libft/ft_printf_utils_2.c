/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanglade <hanglade@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:25:48 by hanglade          #+#    #+#             */
/*   Updated: 2023/11/28 14:52:32 by hanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puthexa_upper_pf(unsigned int nbr, size_t *count_char)
{
	if (nbr > 15)
		ft_puthexa_upper_pf(nbr / 16, count_char);
	ft_putchar_pf("0123456789ABCDEF"[nbr % 16], count_char);
}

void	ft_puthexa_lower_pf(unsigned int nbr, size_t *count_char)
{
	if (nbr > 15)
		ft_puthexa_lower_pf(nbr / 16, count_char);
	ft_putchar_pf("0123456789abcdef"[nbr % 16], count_char);
}

void	ft_putnbr_pf(int nbr, size_t *count_char)
{
	if (nbr == -2147483648)
	{
		ft_putstr_pf("-2147483648", count_char);
		return ;
	}
	if (nbr < 0)
	{
		nbr *= -1;
		ft_putchar_pf('-', count_char);
	}
	if (nbr >= 0 && nbr <= 9)
	{
		ft_putchar_pf(nbr + 48, count_char);
	}
	else
	{
		ft_putnbr_pf(nbr / 10, count_char);
		ft_putnbr_pf(nbr % 10, count_char);
	}
}

void	ft_putnbr_unsigned_pf(unsigned int nbr, size_t *count_char)
{
	if (nbr > 9)
	{
		ft_putnbr_unsigned_pf(nbr / 10, count_char);
		ft_putnbr_unsigned_pf(nbr % 10, count_char);
	}
	else
		ft_putchar_pf(nbr + 48, count_char);
}