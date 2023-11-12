/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:08:01 by bmoudach          #+#    #+#             */
/*   Updated: 2023/11/12 18:59:18 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_path(t_tokens **head)
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
char	*get_home(char **envl)
{
	int		i;
	char	*path_home;

	i = 0;
	path_home = NULL;
	while (envl[i] && !path_home)
	{
		if (!ft_strncmp("HOME=", envl[i], 5))
		{
			path_home = ft_substr(envl[i], 5, ft_strlen(envl[i]));
			if (!path_home)
				return (NULL);
		}
		i++;
	}
	return (path_home);
}

int	cd(t_tokens **head, char **envl)
{
	char	*path;
	char	*path_home;

	path = get_path(head);
	path_home = NULL;
	if (path)
	{
		if (chdir(path))
			return (perror("cd"), -1);
	}
	else
	{
		path_home = get_home(envl);
		if (!path_home)
			return (free(path_home), -1);
		if (chdir(path_home))
			return (free(path_home), -1);
	}
	return (free(path_home), 0);
}
