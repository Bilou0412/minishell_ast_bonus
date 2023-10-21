/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 00:02:14 by bmoudach          #+#    #+#             */
/*   Updated: 2023/05/08 20:37:11 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

char	*ft_strdup(const char *src)
{
	char	*buff;
	int		i;

	i = 0;
	buff = malloc(ft_strlen(src) * sizeof(char) + 1);
	if (!buff)
		return (0);
	while (src[i] != '\0')
	{
		buff[i] = src[i];
		i++;
	}
	buff[i] = '\0';
	return (buff);
}
