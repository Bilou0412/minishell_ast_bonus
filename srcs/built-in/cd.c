/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:08:01 by bmoudach          #+#    #+#             */
/*   Updated: 2023/12/13 16:28:09 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(char *path, t_env **envl)
{
	t_env	*envl_home;
	t_env	*env_old_pwd;
	t_env	*env_pwd;
	char	*pwd;

	pwd = ft_collector(getcwd(NULL, 0), false);
	env_old_pwd = search_envl(envl, "OLDPWD");
	env_pwd = search_envl(envl, "PWD");
	envl_home = search_envl(envl, "HOME");
	if (path)
	{
		if (chdir(path))
			return (ft_printf("zebishell: cd: "), perror(path), 1);
	}
	else
	{
		if (!envl_home)
			return (ft_printf("zebishell: cd: HOME not set\n"), 1);
		return (cd(envl_home->value, envl));
	}
	ft_collector(env_old_pwd->value, true);
	ft_collector(env_pwd->value, true);
	return (env_old_pwd->value = pwd, env_pwd->value = ft_collector(getcwd(NULL,
				0), false), 0);
}
