/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:28:04 by bmoudach          #+#    #+#             */
/*   Updated: 2023/08/25 22:35:04 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	*ft_putnbr(int n, int *len)
{
	long int	nb;

	nb = (long int)n;
	if (nb < 0)
	{
		nb = nb * -1;
		*len += write(1, "-", 1);
	}
	if (nb > 9)
	{
		ft_putnbr(nb / 10, len);
		ft_putnbr(nb % 10, len);
	}
	if (nb <= 9)
	{
		*len += ft_putchar(nb + '0');
	}
	return (len);
}
