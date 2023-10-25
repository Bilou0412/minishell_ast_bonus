/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:12:50 by bmoudach          #+#    #+#             */
/*   Updated: 2023/05/13 14:45:33 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (0);
}
/*#include<stdio.h>
int	main(void)
{
	char str[] = "tripouille";
	printf("%s",strchr(str,'t' + 256));
}
#include <string.h>
int main(void)
{
        char s[] = "tripouille";
	printf("%s \n %s",ft_strchr(s,'t' + 256),s);
        return (0);
}*/
