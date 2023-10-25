/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:39:34 by bmoudach          #+#    #+#             */
/*   Updated: 2023/10/25 17:41:21 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t num)
{
	size_t	i;

	i = 0;
	if (!dst && !src)
		return (0);
	while (i < num)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}

/*int	main(void)
{	
	char dst[10];
	char src[] = "frfrf"; 


	
	printf("%p\n",ft_memcpy(dst,src,5));
	printf("%s",dst);



}*/
