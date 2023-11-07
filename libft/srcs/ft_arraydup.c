/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraydup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:26:03 by bmoudach          #+#    #+#             */
/*   Updated: 2023/11/07 19:23:25 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char **ft_arraydup(char **array)
{
    int i;
    char **new_array;

    i = 0;
    while (array[i])
        i++;
    new_array = ft_calloc((i + 1), sizeof(char *));
    if(!new_array)
        return (NULL);
    i = 0;
    while (array[i])
    {
        new_array[i] = ft_strdup(array[i]);
        if(!new_array)
            return (ft_free_tab(array),new_array[i] = NULL,NULL);
        i++;
    }
    new_array[i] = NULL;
    return (new_array);
}