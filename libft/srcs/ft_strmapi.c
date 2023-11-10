/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:14:19 by bmoudach          #+#    #+#             */
/*   Updated: 2023/11/10 20:07:03 by soutin           ###   ########.fr       */
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
		s1 = ft_calloc(1, sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = '\0';
		return (s1);
	}
	s1 = ft_calloc((ft_strlen(s) + 1), sizeof(char));
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
