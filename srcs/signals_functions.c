/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:23:01 by soutin            #+#    #+#             */
/*   Updated: 2024/01/12 18:56:00 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "minishell.h"

void	ctrl_c_heredoc(int sig)
{
	(void)sig;
	close_heredocs(&_vars()->heredocs);
	close(_vars()->fd_curr_heredoc);
	exit_prog(SIGINT);
}

void	ctrl_c(int sig)
{
	(void)sig;
	if (_vars()->child_sigint)
	{
		write(1, "\n", 1);
		_vars()->child_sigint = false;
		_vars()->heredoc_sigint = true;
	}
	else
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sigquit_handler(int num)
{
	(void)num;
	write(1, "Quit: 3\n", 9);
}
