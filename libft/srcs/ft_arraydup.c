/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraydup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:26:03 by bmoudach          #+#    #+#             */
/*   Updated: 2023/12/02 16:43:43 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	**ft_arraydup(char **array)
{
	int		i;
	char	**new_array;

	i = 0;
	while (array[i])
		i++;
	new_array = (char**)ft_collector(ft_calloc((i + 1), sizeof(char *)), false);
	i = 0;
	while (array[i])
	{
		new_array[i] = (char*)ft_collector(ft_strdup(array[i]), false);
		i++;
	}
	new_array[i] = NULL;
	return (new_array);
}
