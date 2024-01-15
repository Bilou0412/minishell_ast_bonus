/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:48:30 by bmoudach          #+#    #+#             */
/*   Updated: 2024/01/15 21:22:29 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*init_cd(t_env **envl, t_env **home, t_env **old_pwd, t_env **env_pwd)
{
	char	*tmp;

	tmp = NULL;
	*home = NULL;
	*old_pwd = NULL;
	*env_pwd = NULL;
	*old_pwd = search_envl(envl, "OLDPWD");
	*env_pwd = search_envl(envl, "PWD");
	*home = search_envl(envl, "HOME");
	tmp = getcwd(NULL, 0);
	if (!tmp)
		return (ft_collector(ft_strdup(search_envl(envl, "HOME")->value),
				false));
	else
	{
		free(tmp);
		return (ft_collector(getcwd(NULL, 0), false));
	}
}

int	cd(char **path, t_env **envl)
{
	t_env	*envl_home;
	t_env	*env_old_pwd;
	t_env	*env_pwd;
	char	*pwd;

	if (ft_arraylen(path) > 2)
		return (ft_printf("bash: cd: too many arguments\n"), 1);
	pwd = init_cd(envl, &envl_home, &env_old_pwd, &env_pwd);
	if (path[1])
	{
		if (chdir(path[1]))
			return (ft_printf("zebishell: cd: "), perror(path[1]), 1);
	}
	else
	{
		if (!envl_home)
			return (ft_printf("zebishell: cd: HOME not set\n"), 1);
		if (chdir(envl_home->value))
			return (ft_printf("zebishell: cd: "), perror(envl_home->value), 1);
	}
	ft_collector(env_old_pwd->value, true);
	ft_collector(env_pwd->value, true);
	env_old_pwd->value = pwd;
	env_pwd->value = ft_collector(getcwd(NULL, 0), false);
	return (0);
}
