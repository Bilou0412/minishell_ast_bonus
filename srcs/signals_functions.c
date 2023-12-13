/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:23:01 by soutin            #+#    #+#             */
/*   Updated: 2023/12/13 15:07:42 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "minishell.h"

void	ctrl_c_child(int sig)
{
	write(2, "\n", 1);
	exit_prog(SIGINT);
}

void	ctrl_c_heredoc(int sig)
{
	write(2, "\n", 1);
	close(_vars()->fd_heredoc);
	exit_prog(SIGINT);
}

void	ctrl_c(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	rl_replace_line("", 0);
}

void	nothing(int sig)
{
	(void)sig;
	return ;
}
