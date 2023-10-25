/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:14:19 by bmoudach          #+#    #+#             */
/*   Updated: 2023/10/25 17:43:06 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*s1;

	i = 0;
	if (!s)
		return (NULL);
	if (!ft_strlen(s))
	{
		s1 = malloc(sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = '\0';
		return (s1);
	}
	s1 = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!s1)
		return (0);
	while (s[i])
	{
		s1[i] = (f)(i, s[i]);
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
