/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:26:21 by bmoudach          #+#    #+#             */
/*   Updated: 2023/12/09 18:04:16 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*str;
	size_t		len_str;
	size_t		sizestr;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		str = ft_calloc(1, sizeof(char));
		if (!str)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	len_str = ft_strlen(s) - start;
	if (len > len_str)
		sizestr = len_str;
	else
		sizestr = len;
	str = ft_calloc((sizestr + 1), sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s + start, sizestr + 1);
	return (str);
}
