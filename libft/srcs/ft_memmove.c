/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:13:39 by bmoudach          #+#    #+#             */
/*   Updated: 2023/10/25 17:41:28 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t num)
{
	int	i;

	i = (int) num;
	if (dst > src)
	{
		while (i > 0)
		{
			i--;
			((unsigned char *)dst)[i] = ((unsigned char *) src)[i];
		}
	}
	else
	{
		ft_memcpy(dst, src, num);
	}
	return (dst);
}
/*
#include <stdio.h>
#include <string.h>

int main ()
{
  char str[] = "memmove can be very useful......";
  ft_memmove (str+20,str+15,11);
  puts (str);
  return 0;
}*/
