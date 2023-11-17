/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:52:15 by soutin            #+#    #+#             */
/*   Updated: 2023/11/10 21:27:45 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**init_paths(t_vars *vars)
{
	char	*tmp;
	char	**env_path;

	tmp = NULL;
	tmp = search_envl(vars, "PATH");
	tmp = ft_substr(tmp, 5, ft_strlen(tmp));
	if (!tmp)
	{
		return (NULL);
	}
	env_path = ft_split(tmp, ':');
	if (!env_path)
		return (free(tmp), NULL);
	free(tmp);
	return (env_path);
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

// int	init_vars(t_vars *vars, char **envp)
// {
// 	vars->envp = envp;
// 	vars->envp_paths = init_paths(envp);
// 	if (!vars->envp_paths)
// 		return (-1);
// 	return (0);
// }
