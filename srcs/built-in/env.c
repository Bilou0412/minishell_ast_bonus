/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:11:09 by bmoudach          #+#    #+#             */
/*   Updated: 2023/12/01 17:43:23 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_env **envl)
{
	t_env	*tmp;

	tmp = *envl;
	while (tmp)
	{
		printf("%s=%s/n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}
