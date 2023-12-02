/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:55:42 by soutin            #+#    #+#             */
/*   Updated: 2023/12/02 16:49:50 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(char **arg_cmd)
{
	char	*str;

	if(ft_arraylen(arg_cmd) > 1)
	{
		if(arg_cmd[1][0] == '-')
			return (ft_putstr_fd("bash: pwd: no option\n", 2),1);
	}
	str = ft_collector(getcwd(NULL, 0), false);
	printf("%s\n", str);
	ft_collector(str, true);
	return (0);
}
