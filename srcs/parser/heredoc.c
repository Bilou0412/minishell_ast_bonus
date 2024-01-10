/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:21:50 by soutin            #+#    #+#             */
/*   Updated: 2024/01/10 20:20:38 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_heredoc_cmd(t_vars *vars, t_tokens **head)
{
	t_tokens	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (tmp->type == DLESS)
		{
			close(vars->heredocs->fd);
			del_headfile(&vars->heredocs);
		}
		tmp = tmp->next;
	}
}

void	here_doc_loop(t_tokens *curr, int *pipe)
{
	char	*buf;
	char	*limiter;

	buf = NULL;
	limiter = (char *)ft_collector(ft_strjoin(curr->next->string, "\n"),
			false);
	close(pipe[0]);
	while (1)
	{
		buf = get_next_line(1);
		if (!buf)
			(close(pipe[1]), exit_prog(1));
		if (!ft_strncmp(buf, limiter, ft_strlen(limiter)))
			break ;
		ft_putstr_fd(buf, pipe[1]);
		ft_collector(buf, true);
	}
	ft_putstr_fd(NULL, pipe[1]);
	close(pipe[1]);
	exit_prog(0);
}

void	del_headfile(t_files **head)
{
	t_files	*tmp;

	tmp = (*head)->next;
	ft_collector(*head, true);
	*head = tmp;
}

void	init_heredoc(t_tokens **head)
{
	t_vars	*vars;
	int		pid;
	int		pipes[2];

	vars = _vars();
	if (pipe(pipes) < 0)
		return ;
	file_add_back(&vars->heredocs, pipes[0]);
	vars->child_sigint = true;
	pid = fork();
	if (!pid)
	{
		signal(SIGQUIT, &nothing);
		signal(SIGINT, &ctrl_c_heredoc);
		vars->fd_curr_heredoc = pipes[1];
		here_doc_loop(*head, pipes);
	}
	waitchilds(vars, &pid, 1);
	signal(SIGQUIT, sigquit_handler);
	vars->child_sigint = false;
	close(pipes[1]);
}
