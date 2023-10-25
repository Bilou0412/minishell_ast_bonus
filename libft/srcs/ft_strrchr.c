/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:07:01 by bmoudach          #+#    #+#             */
/*   Updated: 2023/10/25 17:43:21 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

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
