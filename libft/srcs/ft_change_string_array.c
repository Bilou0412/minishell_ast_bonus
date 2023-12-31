/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_string_array.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:16:52 by bmoudach          #+#    #+#             */
/*   Updated: 2023/11/20 18:32:05 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	**ft_change_string_array(int i_of_change_str, char *str, char **array)
{
	char	**new_array;
	int		i;

	i = 0;
	while (array[i])
		i++;
	new_array = ft_calloc((i + 1), sizeof(char *));
	if (!new_array)
		return (NULL);
	i = 0;
	while (array[i])
	{
		if (i == i_of_change_str)
			new_array[i] = ft_strdup(str);
		else
			new_array[i] = ft_strdup(array[i]);
		if (!new_array)
			return (ft_free_tab(array), new_array[i] = NULL, NULL);
		i++;
	}
	new_array[i] = NULL;
	return (ft_free_tab(array), new_array);
}

// int	ft_change_string_array(int str_to_change, char *str, char ***array)
// {
// 	free(*array[str_to_change]);
// 	*array[str_to_change] = ft_strdup(str);
// 	if (!*array[str_to_change])
// 		return (-1);
// 	return (0);
// }