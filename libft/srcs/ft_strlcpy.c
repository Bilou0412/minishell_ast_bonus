/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:48:33 by bmoudach          #+#    #+#             */
/*   Updated: 2023/10/25 17:42:59 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	char	*str;

	str = (char *)src;
	i = 0;
	while (i < size - 1 && str[i] != '\0' && size > 1)
	{
		dst[i] = str[i];
		i++;
	}
	if (size > 0)
		dst[i] = '\0';
	return (ft_strlen(src));
}

/*int	main()
{
	char dst[10];
	const char src[] = "perdu";
	
	printf("%ld\n",ft_strlcpy(dst,src,10));
	printf("%s",dst);

}*/
