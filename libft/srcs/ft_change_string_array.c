/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_string_array.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:16:52 by bmoudach          #+#    #+#             */
/*   Updated: 2023/12/09 18:04:48 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_change_string_array(int str_to_change, char *str, char **array)
{
	ft_collector(array[str_to_change], true);
	array[str_to_change] = ft_collector(ft_strdup(str), false);
	return (0);
}
