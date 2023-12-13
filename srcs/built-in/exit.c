/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:56:49 by bmoudach          #+#    #+#             */
/*   Updated: 2023/12/13 15:29:26 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_builtin(char *arg, int nb_arg)
{
	int	i;
	int	exit_status;

	i = 0;
	if (nb_arg > 2)
		return (ft_printf("too many arguments\n"), 1);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (ft_printf("numeric argument required"), 1);
		i++;
	}
	exit_status = ft_atoi(arg);
	rl_clear_history();
	ft_collector(NULL, true);
	tcsetattr(STDIN_FILENO, TCSANOW, &_vars()->original);
	exit(exit_status);
}

int	exit_prog(int code_err)
{
	rl_clear_history();
	ft_collector(NULL, true);
	tcsetattr(STDIN_FILENO, TCSANOW, &_vars()->original);
	exit(code_err);
}
