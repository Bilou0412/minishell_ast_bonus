/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_string_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:03:41 by bmoudach          #+#    #+#             */
/*   Updated: 2023/11/09 18:36:56 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	**ft_del_string_array(int i_of_del_str, char **array)
{
	char	**new_array;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (array[i])
		i++;
	new_array = ft_calloc((i), sizeof(char *));
	if (!new_array)
		return (NULL);
	i = 0;
	while (array[j])
	{
		if (i == i_of_del_str)
			j++;
		new_array[i] = ft_strdup(array[j]);
		if (!new_array)
			return (ft_free_tab(array), new_array[i] = NULL, NULL);
		i++;
		j++;
	}
	new_array[i] = NULL;
	return (ft_free_tab(array), new_array);
}
