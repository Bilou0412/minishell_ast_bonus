/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:23:01 by soutin            #+#    #+#             */
/*   Updated: 2023/11/30 15:24:07 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "minishell.h"

void	ctrl_c(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	freevars(_vars(), 0);
	rl_on_new_line();
	rl_redisplay();
	rl_replace_line("", 0);
}

void	nothing(int sig)
{
	(void)sig;
	return ;
}