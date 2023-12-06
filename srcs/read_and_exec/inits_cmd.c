/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:20:32 by soutin            #+#    #+#             */
/*   Updated: 2023/12/06 21:14:20 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_cmd(t_vars *vars, t_tokens **head)
{
	t_tokens	*current;

	current = *head;
	while (current)
	{
		if (current->type < 4)
		{
			if (handle_files(&vars->cmd, current) < 0)
				exit_prog(1);
			delete_file_tokens(head, &current);
		}
		else
			current = current->next;
	}
	fill_cmd_argv(vars, *head);
	// printtab(vars->cmd.argv);
}

void	init_cmd_path(t_vars *vars)
{
	int		i;
	char	**env_paths;

	i = 0;
	if (path_to_argv(&vars->cmd))
		return ;
	env_paths = init_paths(vars);
	if (env_paths)
	{
		while (env_paths[i])
		{
			vars->cmd.path = cmdjoin(env_paths[i], vars->cmd.argv[0]);
			if (!access(vars->cmd.path, F_OK | X_OK))
			{
				freetabs(env_paths);
				return ;
			}
			ft_collector(vars->cmd.path, true);
			i++;
		}
	}
	ft_printf("command not found: %s\n", vars->cmd.argv[0]);
	freetabs(env_paths);
	exit_prog(1);
}

int	path_to_argv(t_cmd *cmd)
{
	char	**tmp;
	int		i;

	i = 0;
	printf("%s\n", cmd->argv[0]);
	if (!access(cmd->argv[0], F_OK | X_OK))
	{
		cmd->path = cmd->argv[0];
		tmp = ft_split(cmd->argv[0], '/');
		while (tmp[i + 1])
			i++;
		cmd->argv[0] = (char *)ft_collector(ft_substr(tmp[i], 0, ft_strlen(tmp[i])),
				false);
		freetabs(tmp);
		return(1);
	}
	return (0);
}

int	init_cmd_and_files(t_vars *vars, t_tokens **head)
{
	sort_cmd(vars, head);
	return (0);
}
