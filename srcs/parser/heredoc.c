/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:21:50 by soutin            #+#    #+#             */
/*   Updated: 2024/01/19 21:32:59 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find(char *str, int fd)
{
	int		len;
	char	save;
	t_env	*tmp;

	len = 1;
	while (str[len] && str[len] != '$' && str[len] != ' ')
		len++;
	if (!len)
		return (len);
	save = str[len];
	str[len] = 0;
	tmp = search_envl(&_vars()->envl, str + 1);
	if (tmp)
		ft_putstr_fd(tmp->value, fd);
	str[len] = save;
	return (len);
}

void	expand_heredoc_or_not(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			i += find(str + i, fd);
		else
			i += ft_putchar_fd(str[i], fd);
	}
	ft_putchar_fd('\n', fd);
	ft_collector(str, true);
}

void	here_doc_loop(t_tokens *curr, int *pipe)
{
	char	*buf;
	char	*limiter;

	buf = NULL;
	limiter = curr->next->string;
	close(pipe[0]);
	while (1)
	{
		buf = readline("> ");
		if (!buf || !ft_strncmp(buf, limiter, ft_strlen(limiter) + 1))
			break ;
		expand_heredoc_or_not(buf, pipe[1]);
	}
	ft_putstr_fd(NULL, pipe[1]);
	close(pipe[1]);
	close_heredocs(&_vars()->heredocs);
	exit_prog(0);
}

void	init_heredoc(t_tokens **head)
{
	static int	i;
	t_vars		*vars;
	int			pid;
	int			pipes[2];

	vars = _vars();
	if (pipe(pipes) < 0)
		return ;
	file_add_back(&vars->heredocs, pipes[0], (*head)->next->string, i);
	(*head)->next->heredoc_index = i;
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (!pid)
	{
		signal(SIGINT, &ctrl_c_heredoc);
		vars->fd_curr_heredoc = pipes[1];
		here_doc_loop(*head, pipes);
	}
	waitchilds(vars, &pid, 1);
	signal(SIGQUIT, sigquit_handler);
	vars->child_sigint = false;
	close(pipes[1]);
	i++;
}
