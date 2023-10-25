/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:23:19 by soutin            #+#    #+#             */
/*   Updated: 2023/10/25 15:46:28 by soutin           ###   ########.fr       */
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

int	main()
{
	t_input_str str_in;
	char	*prompt;

	_vars()->tokens = NULL;
	while (1)
	{
		prompt = NULL;
		str_in.curpos = 0;
		if (!get_prompt(&prompt))
			return (1);
		str_in.buff = readline(prompt);
		if (str_in.buff)
		{
			token_m(&str_in, &_vars()->tokens);
			is_command_line(_vars()->tokens, &_vars()->ast);
			print_tree(_vars()->ast, 0);
			free_tree(&_vars()->ast);
			ft_lstclear(&_vars()->tokens, &free);
			free(str_in.buff);
		}
		free(prompt);
	}
	return (0);
}
