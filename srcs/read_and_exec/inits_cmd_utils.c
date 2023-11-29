/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:52:15 by soutin            #+#    #+#             */
/*   Updated: 2023/11/29 14:05:59 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**init_paths(t_vars *vars)
{
	char	*tmp;
	char	**env_path;

	tmp = NULL;
	tmp = search_envl(vars, "PATH");
	if(!tmp)
		return (NULL);
	if (!*tmp)
		return (super_free(&tmp), NULL);
	tmp = ft_substr(tmp, 5, ft_strlen(tmp + 5));
	if (!tmp)
		return (NULL);
	env_path = ft_split(tmp, ':');
	if (!env_path)
		return (free(tmp), NULL);
	free(tmp);
	return (env_path);
}

int	fill_cmd_argv(t_vars *vars, t_tokens *tokens)
{
	t_tokens	*tmp;
	int			i;

	i = 0;
	vars->cmd.argv = ft_calloc(ft_lstsize(tokens) + 1, sizeof(char *));
	if (!vars->cmd.argv)
		return (-1);
	tmp = tokens;
	while (tmp)
	{
		vars->cmd.argv[i] = ft_strdup(tmp->string);
		if (!vars->cmd.argv[i])
			return (-1);
		tmp = tmp->next;	
		i++;
	}
	vars->cmd.argv[i] = NULL;
	return (0);
}

char	*cmdjoin(char *path, char *cmd)
{
	char	*new;
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	new = ft_strjoin(tmp, cmd);
	if (!new)
		return (free(tmp), NULL);
	free(tmp);
	return (new);
}
