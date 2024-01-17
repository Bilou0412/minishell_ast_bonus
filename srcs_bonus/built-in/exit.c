/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:56:49 by bmoudach          #+#    #+#             */
/*   Updated: 2024/01/15 20:37:14 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_digit(char *arg, int *exit_status)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]) || i > 18)
		{
			ft_printf("zebishell: exit: %s: numeric argument required\n", arg);
			*exit_status = 2;
			return (1);
		}
		i++;
	}
	return (0);
}

int	exit_builtin(char *arg, int nb_arg)
{
	int	exit_status;
	int	error;

	exit_status = 0;
	printf("exit\n");
	if (nb_arg > 1)
	{
		error = check_digit(arg, &exit_status);
		if (!exit_status)
			exit_status = ft_atoi(arg);
	}
	else
		exit_status = _vars()->return_value;
	if (nb_arg > 2 && !error)
		return (ft_printf("zebishell: exit: too many arguments\n"), 1);
	return (exit_prog(exit_status), 0);
}

int	exit_prog(int code_err)
{
	rl_clear_history();
	ft_collector(NULL, true);
	tcsetattr(STDIN_FILENO, TCSANOW, &_vars()->original);
	exit(code_err);
}
