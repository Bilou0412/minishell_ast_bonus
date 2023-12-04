/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:08:01 by bmoudach          #+#    #+#             */
/*   Updated: 2023/12/04 23:26:36 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(char **cmd_arg, t_env **envl)
{
	char	*path;
	t_env	*envl_home;
	t_env	*env_old_pwd;
	t_env	*env_pwd;
	char	*pwd;

	pwd = ft_collector(getcwd(NULL, 0), false);
	path = cmd_arg[1];
	env_old_pwd = search_envl(envl, "OLDPWD");
	env_pwd = search_envl(envl, "PWD");
	envl_home = search_envl(envl, "HOME");
	if (path)
	{
		if (chdir(path))
			return (perror("cd"), 0);
	}
	else
	{
		path = envl_home->value;
		if (!path)
			return (-1);
		if (chdir(path))
			return (0);
	}
	return (env_old_pwd->value = pwd, env_pwd->value = path, 0);
}
