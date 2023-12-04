/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:52:15 by soutin            #+#    #+#             */
/*   Updated: 2023/12/04 17:41:25 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_paths(t_vars *vars)
{
	char	*tmp;
	char	**env_path;

	env_path = NULL;
	tmp = NULL;
	tmp = (search_envl(&vars->envl, "PATH"))->value;
	if (tmp)
	{
		tmp = (char*)ft_collector(ft_substr(tmp, 5, ft_strlen(tmp + 5)), false);
		env_path = ft_split(tmp, ':');
	}
	ft_collector(tmp, true);
	return (env_path);
}

int	fill_cmd_argv(t_vars *vars, t_tokens *tokens)
{
	t_tokens	*tmp;
	int			i;

	i = 0;
	vars->cmd.argv = (char**)ft_collector(ft_calloc(ft_toksize(tokens) + 1, sizeof(char *)), false);
	tmp = tokens;
	while (tmp)
	{
		vars->cmd.argv[i] = (char*)ft_collector(ft_strdup(tmp->string), false);
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

	tmp = (char*)ft_collector(ft_strjoin(path, "/"), false);
	new = (char*)ft_collector(ft_strjoin(tmp, cmd), false);
	ft_collector(tmp, true);
	return (new);
}
