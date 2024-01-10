/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:23:19 by soutin            #+#    #+#             */
/*   Updated: 2024/01/10 20:54:52 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_vars	*_vars(void)
{
	static t_vars	vars;

	return (&vars);
}

int	init_minishell(t_vars *vars, char **envp)
{
	shrek_print();
	if (setup_env(&vars->envl, envp) < 0)
		return (1);
	tcgetattr(STDIN_FILENO, &_vars()->original);
	return (0);
}

int	launch_ast(t_vars *vars)
{
	signal(SIGQUIT, sigquit_handler);
	vars->ast = is_branch(&vars->tokens, 0);
	if (vars->heredoc_sigint)
		vars->error = true;
	tcsetattr(STDIN_FILENO, TCSANOW, &vars->original);
	if (!vars->error)
	{
		if (read_ast(vars, vars->ast, false))
			exit_prog(1);
	}
	else
		ft_tokclear(&vars->tokens);
	vars->last_return_val = 0;
	free_tree(&vars->ast);
	return (0);
}

int	read_inputs(t_vars *vars)
{
	while (1)
	{
		vars->heredoc_sigint = false;
		vars->child_sigint = false;
		if (vars->heredocs)
			free_files(&vars->heredocs);
		vars->heredocs = NULL;
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, nothing);
		vars->str_in.buff = (char *)ft_collector(readline("zebishell> "),
				false);
		if (vars->str_in.buff[0])
			add_history(vars->str_in.buff);
		token_m(vars, &vars->tokens);
		if (vars->tokens)
			launch_ast(vars);
		vars->error = false;
	}
	return (0);
}

int	main(int c, char **v, char **envp)
{
	(void)v;
	init_minishell(_vars(), envp);
	if (c != 1)
		return (ft_printf("No arguments awaited\n"), 1);
	if (read_inputs(_vars()) < 0)
		return (1);
	return (0);
}
