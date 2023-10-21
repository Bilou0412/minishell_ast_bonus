/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:01:17 by bmoudach          #+#    #+#             */
/*   Updated: 2023/08/25 22:35:21 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	convert_ptr(unsigned long nb, int *len)
{
	char		*base_lowcaps;

	base_lowcaps = "0123456789abcdef";
	if (nb > 15)
	{
		convert_ptr(nb / 16, len);
		convert_ptr(nb % 16, len);
	}
	else
		*len += write(1, &base_lowcaps[nb], 1);
	return ;
}

int	ft_putptr(unsigned long nb, int *len)
{
	if (nb == 0)
		*len += write(1, "(nil)", 5);
	else
	{
		*len += write(1, "0x", 2);
		convert_ptr(nb, len);
	}
	return (0);
}
