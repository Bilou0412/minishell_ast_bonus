/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:07:58 by bmoudach          #+#    #+#             */
/*   Updated: 2023/11/09 18:58:11 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_for_echo(char *str_to_print)
{
	char	c;

	c = 0;
	while (*str_to_print)
	{
		if (ft_strchr("\'\"", *str_to_print) && c == 0)
		{
			c = *str_to_print;
			str_to_print++;
		}
		else if (c != '\0' && c == *str_to_print)
			str_to_print++;
		else
		{
			ft_putchar_fd(*str_to_print, 1);
			str_to_print++;
		}
	}
}

char	*check_echo_option(char *option, char *string)
{
	int		i;
	char	*str_to_print;
	char	*tmp;

	i = 0;
	if (*option && !ft_strncmp("-n", option, 2))
	{
		i = i + 2;
		while (option[i] == 'n')
			i++;
		if (option[i] == '\0')
			return (ft_strdup(string));
		else if (option[i] == ' ')
		{
			i++;
			return (ft_strjoin(option + i, string));
		}
	}
	if (*option)
	{
		str_to_print = ft_strjoin(option, " ");
		if (!str_to_print)
			return (NULL);
		tmp = ft_strjoin(str_to_print, string);
		free(str_to_print);
		if (!tmp)
			return (NULL);
		str_to_print = ft_strjoin(tmp, "\n");
		free(tmp);
		if (!str_to_print)
			return (NULL);
		return (str_to_print);
	}
	return (ft_strjoin(string, "\n"));
}

int	echo(char *option, char *string)
{
	char	*str_to_print;

	if (!option && !string)
		return (ft_putchar_fd('\n', 1), 0);
	else if (string && !option)
		return (print_for_echo(string), ft_putchar_fd('\n', 1), 0);
	else if (!string && !ft_strncmp("-n", option, 3))
		return (0);
	else
		str_to_print = check_echo_option(option, string);
	print_for_echo(str_to_print);
	return (free(str_to_print), 0);
}
