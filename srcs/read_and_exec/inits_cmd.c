/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:20:32 by soutin            #+#    #+#             */
/*   Updated: 2023/11/27 16:46:38 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	sort_cmd(t_vars *vars, t_tokens **head)
{
	t_tokens	*current;

	current = *head;
	while (current && current->type != PIPE)
	{
		
		if (current->type < 4)
		{
			if (handle_files(&vars->cmd, current) < 0)
				return (-1);
			delete_file_tokens(head, &current);
		}
		else
			current = current->next;
	}
	if (fill_cmd_argv(vars, *head) < 0)
		return (-1);
	return (0);
}

int	init_cmd_path(t_vars *vars)
{
	int	i;

	i = 0;
	if (path_to_argv(&vars->cmd) < 0)
		return (-1);
	if (vars->cmd.path)
		return (0);
	vars->cmd.env_paths = init_paths(vars);
	if (!vars->cmd.env_paths)
		return (-1);
	while (vars->cmd.env_paths[i])
	{
		vars->cmd.path = cmdjoin(vars->cmd.env_paths[i], vars->cmd.argv[0]);
		if (!vars->cmd.path)
			return (perror("join"), -1);
		if (!access(vars->cmd.path, F_OK | X_OK))
			return (0);
		free(vars->cmd.path);
		vars->cmd.path = NULL;
		i++;
	}
	ft_printf("command not found: %s\n", vars->cmd.argv[0]);
	return (-1);
}

int	path_to_argv(t_cmd *cmd)
{
	char	**tmp;
	int		i;

	i = 0;
	if (!access(cmd->argv[0], F_OK | X_OK))
	{
		cmd->path = cmd->argv[0];
		tmp = ft_split(cmd->argv[0], '/');
		if (!tmp)
			return (-1);
		while (tmp[i + 1])
			i++;
		cmd->argv[0] = ft_substr(tmp[i], 0, ft_strlen(tmp[i]));
		freetabs(tmp);
		if (!cmd->argv[0])
			return (-1);
		return (0);
	}
	return (0);
}

int	init_cmd_and_files(t_vars *vars, t_tokens **head, int i)
{
	if (sort_cmd(vars, head) < 0 || init_cmd_path(vars) < 0)
	{
		if (i > 0)
			close(vars->tmp_fd);
		if (vars->cmd.nb_pipes)
		{
			close(vars->pipe_fd[1]);
			close(vars->pipe_fd[0]);
		}
		ft_lstclear(head, &free);
		return (freevars(vars, 1), -1);
	}
	// ft_lstclear(head, &free);
	if (tough_choices(vars, i) < 0)
		return (freevars(vars, 1), -1);
	if (vars->cmd.nb_pipes)
		if (close(vars->pipe_fd[1]) < 0 || close(vars->pipe_fd[0]) < 0)
			return (freevars(vars, 1), -1);
	return (0);
}
