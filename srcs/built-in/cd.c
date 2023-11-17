/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:08:01 by bmoudach          #+#    #+#             */
/*   Updated: 2023/11/15 22:19:38 by soutin           ###   ########.fr       */
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

int	refresh_pwd(t_vars *vars)
{
	char	*pwd;
	int		i;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	pwd = ft_strjoin("PWD=", cwd);
	free(cwd);
	if (!pwd)
		return (-1);
	i = search_envl_index("PWD=", vars);
	if (i > -1)
	{
		if (ft_change_string_array(i, pwd, &vars->envl) < 0)
			return (free(pwd), -1);
	}
	else
	{
		vars->envl = ft_ad_case_to_array(vars->envl);
		if (!vars->envl)
			return (free(pwd), -1);
		vars->envl[ft_arraylen(vars->envl)] = ft_strdup(pwd);
		if (!vars->envl[ft_arraylen(vars->envl)])
			return (free(pwd), -1);
	}
	return (free(pwd), 0);
}

int	refresh_old_pwd(t_vars *vars, char *pwd)
{
	char	*old_pwd;
	int		i;

	old_pwd = ft_strjoin("OLDPWD=", pwd);
	free(pwd);
	if (!old_pwd)
		return (-1);
	i = search_envl_index("OLDPWD=", vars);
	if (i > -1)
	{
		ft_change_string_array(i, old_pwd, &vars->envl);
		if (!vars->envl)
			return (free(old_pwd), -1);
	}
	else
	{
		vars->envl = ft_ad_case_to_array(vars->envl);
		if (!vars->envl)
			return (free(old_pwd), -1);
		vars->envl[ft_arraylen(vars->envl)] = ft_strdup(old_pwd);
		if (!vars->envl[ft_arraylen(vars->envl)])
			return (free(old_pwd), -1);
	}
	return (free(old_pwd), 0);
}

int	cd(t_tokens **head, t_vars *vars)
{
	char	*path;
	char	*path_home;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	path = get_path(head);
	path_home = NULL;
	if (path)
	{
		if (chdir(path))
			return (perror("cd"), -1);
	}
	else
	{
		path_home = get_home(vars->envl);
		if (!path_home)
			return (free(path_home), -1);
		if (chdir(path_home))
			return (free(path_home), -1);
	}
	if (refresh_old_pwd(vars, pwd))
		return (free(path_home), -1);
	if (refresh_pwd(vars))
		return (free(path_home), -1);
	return (free(path_home), 0);
}
