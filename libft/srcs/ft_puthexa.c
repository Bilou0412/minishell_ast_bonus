/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 09:56:32 by bmoudach          #+#    #+#             */
/*   Updated: 2023/12/09 17:00:17 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	*ft_puthexa(unsigned int nb, char c, int *len)
{
	char		*base_lowcaps;
	char		*base_uppercase;

	base_lowcaps = "0123456789abcdef";
	base_uppercase = "0123456789ABCDEF";
	if (nb > 15)
	{
		ft_puthexa(nb / 16, c, len);
		ft_puthexa(nb % 16, c, len);
	}
	if (nb < 16)
	{
		if (c == 'x')
			*len += write(2, &base_lowcaps[nb], 1);
		else
		{
			*len += write(2, &base_uppercase[nb], 1);
		}
	}
	return (len);
}
