/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:52:15 by soutin            #+#    #+#             */
/*   Updated: 2023/12/08 17:08:40 by soutin           ###   ########.fr       */
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
		ft_collector(tmp, true);
	}
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

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	new = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!new)
		return (NULL);
	return (new);
}
