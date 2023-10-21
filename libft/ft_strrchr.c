/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:07:01 by bmoudach          #+#    #+#             */
/*   Updated: 2023/05/13 15:17:56 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;	

	i = ft_strlen(s);
	if (!s)
		return (0);
	while (i >= 0)
	{		
		if (s[i] == (char)c)
		{
			return ((char *)s + i);
		}
		i--;
	}
	return (0);
}
/*int	main(void)
{

	const char	str[] = "asdfgdhj";
	printf("%s",ft_strrchr(str,0));
}*/
