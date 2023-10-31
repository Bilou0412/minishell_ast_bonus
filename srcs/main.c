/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:23:19 by soutin            #+#    #+#             */
/*   Updated: 2023/10/31 16:18:07 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_vars	*_vars(void)
{
	static t_vars	vars;

	return (&vars);
}

char	*get_prompt(char **prompt)
{
	int		i;
	char	*buffer;
	char	*tmp;

	tmp = NULL;
	*prompt = NULL;
	buffer = getcwd(NULL, 0);
	if (!buffer)
		return (NULL);
	i = ft_strlen(buffer);
	while (i >= 0 && buffer[i] != '/')
		i--;
	tmp = ft_substr(buffer, i, ft_strlen(buffer + i));
	if (!tmp)
		return (NULL);
	*prompt = ft_strjoin(tmp, " ");
	if (!prompt)
		return (NULL);
	free(buffer);
	free(tmp);
	return (*prompt);
}

int	read_inputs(t_vars *vars)
{
	char		*prompt;

	while (1)
	{
		if (!get_prompt(&prompt))
			return (1);
		vars->str_in.buff = readline(prompt);
		if (!vars->str_in.buff)
			return (-1);
		if (vars->str_in.buff)
		{
			token_m(&vars->str_in, &vars->tokens);
			if (launch_ast(vars->tokens, &vars->ast) < 0)
				return (1);
			free_tree(&vars->ast);
			free(vars->str_in.buff);
		}
		free(prompt);
	}
	return (0);
}

int	main(void)
{
	if (read_inputs(_vars()) < 0)
		return (1);
	return (0);
}
