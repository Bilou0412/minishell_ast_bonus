/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:34:37 by bmoudach          #+#    #+#             */
/*   Updated: 2023/10/25 17:41:16 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_memcmp( const void *pointer1, const void *pointer2, size_t size)
{
	unsigned char	*p1;
	unsigned char	*p2;
	size_t			i;

	i = 0;
	p1 = (unsigned char *)pointer1;
	p2 = (unsigned char *)pointer2;
	while (i < size)
	{
		if (p1[i] > p2[i])
			return (1);
		if (p1[i] < p2[i])
			return (-1);
		i++;
	}
	return (0);
}
