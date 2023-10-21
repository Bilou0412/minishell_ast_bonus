/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 20:12:35 by bmoudach          #+#    #+#             */
/*   Updated: 2023/05/07 17:52:36 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (n == 0)
		return (ft_strlen(src));
	while (dst[i] != '\0' && i < n)
		i++;
	j = i;
	while (src[i - j] != '\0' && i < n - 1)
	{
		dst[i] = src[i - j];
		i++;
	}
	if (j < n)
		dst[i] = '\0';
	return (j + ft_strlen(src));
}

/*{
	size_t	len_dst;
	size_t	i;
	size_t 	len_src;

	i = 0;
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if(size == 0)
		return (len_src);
	while(len_dst + i < size - 1 && src[i] != '\0')
	{
		dst[len_dst + i] = src[i];
		i++;
	}
	if(size <= len_dst)
	{
		dst[size] = '\0';
		return(size);
	}
	if(size > 0 )
		dst[len_dst + i] = '\0';
	return(len_dst + len_src);
}
int main(void)
{
	char	dst[30];
	memset(dst, 'B', 4);
	const	char src[] = "AAAAAAAAA";
	char	dst1[30] ;
	memset(dst1, 'B', 4);
	const	char src1[] = "AAAAAAAAA";
	printf("%ld\n",strlcat(dst1,src1,3));
	printf("%ld\n",ft_strlcat(dst,src,3));
	printf("%s\n",dst1);
	printf("%s",dst);
}*/
