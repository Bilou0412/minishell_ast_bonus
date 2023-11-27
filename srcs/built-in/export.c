/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:07:56 by bmoudach          #+#    #+#             */
/*   Updated: 2023/11/27 20:29:57 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	search_envl_index(char *var, t_vars *all)
{
	int	i;
	int	size_name_envl;
	int	size_name_var;

	i = 0;
	size_name_var = ft_strlen_to_char(var, '=');
	while (all->envl[i])
	{
		size_name_envl = ft_strlen_to_char(all->envl[i], '=');
		if (size_name_envl == size_name_var)
		{
			if (!ft_strncmp(var, all->envl[i], size_name_envl))
				return (i);
		}
		i++;
	}
	return (-1);
}

char	*get_next_word(t_tokens **head)
{
	t_tokens	*current;

	current = *head;
	while (current)
	{
		if (current->type == WORD)
			return (current->string);
		current = current->next;
	}
	return (NULL);
}

int	check_var_name(char *var)
{
	int	i;

	i = 0;
	if (var && !ft_strchr(var, '='))
		return (-1);
	while (var[i] && var[i] != '=')
	{
		if (ft_isalpha(var[i]) || var[i] == '_' || (var[i] == '+' && var[i
				+ 1] == '='))
			i++;
		else
			return (1);
	}
	return (0);
}

int	export(t_tokens **head, t_vars *all)
{
	int		size;
	int		to_change;
	char	*var;

	var = get_next_word(head);
	size = ft_arraylen(all->envl);
	if (check_var_name(var))
		return (-1);
	to_change = search_envl_index(var, all);
	if (to_change > -1)
	{
		all->envl = ft_change_string_array(to_change, var, all->envl);
		if (!all->envl)
			return (-1);
	}
	else
	{
		all->envl = ft_ad_case_to_array(all->envl);
		if (!all->envl)
			return (0);
		all->envl[size] = ft_strdup(var);
		if (!all->envl[size])
			return (-1);
	}
	return (0);
}
