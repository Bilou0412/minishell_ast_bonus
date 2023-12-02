/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:58:09 by soutin            #+#    #+#             */
/*   Updated: 2023/12/02 16:16:14 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	multiple_dup2(t_vars *vars, int in, int builtin)
{
	t_files	*tmp;
	int		std_fd;

	if (in)
	{
		tmp = vars->cmd.infiles;
		std_fd = STDIN_FILENO;
	}
	else
	{
		tmp = vars->cmd.outfiles;
		std_fd = STDOUT_FILENO;
	}
	while (tmp)
	{
		if (dup2(tmp->fd, std_fd) < 0)
			return (-1);
		if (close(tmp->fd) < 0)
			return (-1);	
		tmp = tmp->next;
	}
	return (0);
}

int	waitchilds(t_vars *vars, int *pid, int childmax)
{
	int	i;
	int	status;

	i = 0;
	while (i < childmax)
	{
		if (waitpid(pid[i], &status, 0) < 0)
			return (-1);
		i++;
		vars->last_return_val = WEXITSTATUS(status);
	}
	return (0);
}

