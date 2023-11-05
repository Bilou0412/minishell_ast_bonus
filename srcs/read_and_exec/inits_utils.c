/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:52:15 by soutin            #+#    #+#             */
/*   Updated: 2023/11/04 19:55:58 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// char	**init_paths(char **envp)
// {
// 	int		i;
// 	char	*tmp;
// 	char	**envp_path;

// 	i = 0;
// 	tmp = NULL;
// 	while (envp[i++])
// 	{
// 		if (!ft_strncmp(envp[i], "PATH=", 5))
// 		{
// 			tmp = ft_substr(envp[i], 5, ft_strlen(&envp[i][5]));
// 			if (!tmp)
// 				return (NULL);
// 			break ;
// 		}
// 	}
// 	envp_path = ft_split(tmp, ':');
// 	if (!envp_path)
// 		return (free(tmp), NULL);
// 	free(tmp);
// 	return (envp_path);
// }

// char	*cmdjoin(char *path, char *cmd)
// {
// 	char	*new;
// 	char	*tmp;

// 	tmp = ft_strjoin(path, "/");
// 	if (!tmp)
// 		return (NULL);
// 	new = ft_strjoin(tmp, cmd);
// 	if (!new)
// 		return (free(tmp), NULL);
// 	free(tmp);
// 	return (new);
// }

// int	init_vars(t_vars *vars, char **envp)
// {
// 	vars->envp = envp;
// 	vars->envp_paths = init_paths(envp);
// 	if (!vars->envp_paths)
// 		return (-1);
// 	return (0);
// }
