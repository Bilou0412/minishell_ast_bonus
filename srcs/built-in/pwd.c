/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:55:42 by soutin            #+#    #+#             */
/*   Updated: 2024/01/15 16:48:04 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(char **arg_cmd)
{
	char	*str;

	if (ft_arraylen(arg_cmd) > 1)
	{
		if (arg_cmd[1][0] == '-')
			return (ft_putstr_fd("bash: pwd: no option\n", 2), 1);
	}
	str = getcwd(NULL, 0);
	if (!str)
	{
		printf("pwd: error retrieving current directory: getcwd: ");
		printf("cannot access parent directories: No such file or directory\n");
	}
	else
	{
		printf("%s\n", str);
		free(str);
	}
	return (0);
}
