/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:25:33 by bmoudach          #+#    #+#             */
/*   Updated: 2023/05/07 19:41:57 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*st1;
	unsigned char	*st2;

	i = 0;
	st1 = (unsigned char *)s1;
	st2 = (unsigned char *)s2;
	while ((st1[i] != '\0' || st2[i] != '\0') && i < n)
	{
		if (st1[i] > st2[i])
			return (1);
		else if (st1[i] < st2[i])
			return (-1);
		i++;
	}
	return (0);
}
