/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:20:32 by soutin            #+#    #+#             */
/*   Updated: 2024/01/10 20:19:15 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sort_cmd(t_vars *vars, t_tokens **head)
{
	t_tokens	*current;

	current = *head;
	while (current)
	{
		if (current->type < PIPE)
		{
			if (handle_files(&vars->cmd, current) < 0)
				return (-1);
			delete_file_tokens(head, &current);
		}
		else
			current = current->next;
	}
	fill_cmd_argv(vars, *head);
	ft_tokclear(head);
	return (0);
}

void	cmd_exec_error(char *name)
{
	ft_printf("zebishell: ");
	perror(name);
	exit_prog(126);
}

int	init_cmd_path(t_vars *vars)
{
	int		i;
	char	**env_paths;

	i = 0;
	if (path_to_argv(vars, &vars->cmd))
		return (0);
	env_paths = init_paths(vars);
	while (env_paths && env_paths[i])
	{
		vars->cmd.path = (char *)ft_collector(cmdjoin(env_paths[i],
					vars->cmd.argv[0]), false);
		if (!access(vars->cmd.path, F_OK))
		{
			if (access(vars->cmd.path, X_OK))
				cmd_exec_error(vars->cmd.argv[0]);
			return (freetabs(env_paths), 0);
		}
		ft_collector(vars->cmd.path, true);
		i++;
	}
	ft_printf("zebishell: %s: command not found\n", vars->cmd.argv[0]);
	exit_prog(127);
	return (0);
}

int	path_to_argv(t_vars *vars, t_cmd *cmd)
{
	char	**tmp;
	int		i;

	i = 0;
	if (!access(cmd->argv[0], F_OK))
	{
		errno = 0;
		if (access(vars->cmd.argv[0], X_OK))
			cmd_exec_error(vars->cmd.argv[0]);
		cmd->path = cmd->argv[0];
		tmp = ft_split(cmd->argv[0], '/');
		while (tmp[i + 1])
			i++;
		cmd->argv[0] = (char *)ft_collector(ft_substr(tmp[i], 0,
					ft_strlen(tmp[i])), false);
		freetabs(tmp);
		return (1);
	}
	return (0);
}
