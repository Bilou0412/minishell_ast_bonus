/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:07:58 by bmoudach          #+#    #+#             */
/*   Updated: 2023/11/30 15:04:51 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_for_echo(char **arg_cmd, int start)
{
	int	i;

	i = start;
	while (arg_cmd[i])
	{
		printf("%s", arg_cmd[i]);
		i++;
		if (arg_cmd[i])
			printf(" ");
	}
	if (start == 1)
		printf("\n");
	return (0);
}

int	option_newline(char **arg_cmd)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (arg_cmd[i])
	{
		if (arg_cmd[i][0] == '-')
		{
			j++;
			while (arg_cmd[i][j])
			{
				if (arg_cmd[i][j] != 'n' && arg_cmd[i][j] != '\0')
					return (i);
				j++;
			}
		}
		else
			return (i);
		j = 0;
		i++;
	}
	return (i);
}

int	echo(char **arg_cmd)
{
	int	i;
	int	nb_arg;

	i = 0;
	nb_arg = ft_arraylen(arg_cmd);
	if (nb_arg == 1)
		ft_putchar('\n');
	else if (i < nb_arg)
	{
		i = option_newline(arg_cmd);
		print_for_echo(arg_cmd, i);
	}
	return (0);
}
