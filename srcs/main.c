/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:23:19 by soutin            #+#    #+#             */
/*   Updated: 2023/11/07 19:52:12 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_vars	*_vars(void)
{
	static t_vars	vars;

	return (&vars);
}

int	init_vars(t_vars *vars, char **envp)
{
	vars->str_in.buff = NULL;
	vars->nb_cmd = 0;
	vars->ast = NULL;
	vars->envp = envp;
	vars->cmd.argv_cmd = NULL;
	vars->cmd.cmd_path = NULL;
	vars->cmd.infiles = NULL;
	vars->cmd.outfiles = NULL;
	vars->last_return_val = 0;
	vars->envl = ft_arraydup(envp);
	if (!vars->envl)
		return (1);
	return (0);
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

	vars->str_in.buff = "e1|<e2|e3|e4|e5 e6 e7 |e8 ";
	token_m(&vars->str_in, &vars->tokens);
	if (launch_ast(vars->tokens, &vars->ast) < 0)
		return (-1);
	vars->tokens = NULL;
	read_ast(vars, vars->ast);
	printtokens(&vars->tokens);
	print_tree(vars->ast, 0);
	free_tree(&vars->ast);
	while (1)
	{
		if (!get_prompt(&prompt))
			return (-1);
		vars->str_in.buff = readline(prompt);
		if (!vars->str_in.buff)
			return (-1);
		if (token_m(&vars->str_in, &vars->tokens) < 0)
			return (freevars(vars, 0), -1);
		free(vars->str_in.buff);
		vars->str_in.buff = NULL;
		if (launch_ast(vars->tokens, &vars->ast) < 0)
			return (freevars(vars, 0), -1);
		count_cmd(vars, vars->ast);
		printf("\n%d\n", vars->nb_cmd);
		if (read_ast(vars, vars->ast))
			return (free(vars->str_in.buff), free(prompt), -1);
		// print_tree(vars->ast, 0);
		printtokens(&vars->tokens);
		free_tree(&vars->ast);
		free(prompt);
	}
	return (0);
}

int	main(int c, char **v, char **envp)
{
	(void)v;
	if (c != 1)
		return (1);
	init_vars(_vars(), envp);
	if (read_inputs(_vars()) < 0)
		return (1);
	return (0);
}
