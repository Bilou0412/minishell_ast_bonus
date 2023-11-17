/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:51:16 by soutin            #+#    #+#             */
/*   Updated: 2023/11/16 17:57:28 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*expand(t_vars *vars, char *name)
{
	char	*str;

	str = search_envl(vars, name);
	if (str)
		return (str + ft_strlen(name) + 1);
	return (NULL);
}