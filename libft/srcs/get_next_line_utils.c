/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:46:52 by bmoudach          #+#    #+#             */
/*   Updated: 2023/11/10 20:06:19 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	int		size;

	if (!s1 && s2)
		return (ft_strdup(s2));
	else if (s1 && !s2)
		return (ft_strdup(s1));
	else
	{
		size = ft_strlen(s1) + ft_strlen(s2);
		str = ft_calloc((size + 1), sizeof(char));
		if (!str)
			return (NULL);
		ft_strlcpy(str, s1, ft_strlen(s1) + 1);
		ft_strlcat(str, s2, size + 1);
		free(s1);
	}
	return (str);
}
