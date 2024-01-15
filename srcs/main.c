/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:23:19 by soutin            #+#    #+#             */
/*   Updated: 2024/01/15 21:22:55 by soutin           ###   ########.fr       */
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
	signal(SIGINT, ctrl_c);
	return (0);
}

void	init_loop(t_vars *vars)
{
	signal(SIGQUIT, SIG_IGN);
	vars->last_return_val = 0;
	vars->heredoc_sigint = false;
	vars->child_sigint = false;
	vars->error = false;
}

int	build_and_run_ast(t_vars *vars)
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
	free_tree(&vars->ast);
	close_heredocs(&vars->heredocs);
	return (0);
}

int	main(int c, char **v, char **envp)
{
	t_vars	*vars;

	(void)v;
	vars = _vars();
	init_minishell(vars, envp);
	if (c != 1)
		return (ft_printf("No arguments awaited\n"), 1);
	while (1)
	{
		init_loop(vars);
		vars->str_in.buff = (char *)ft_collector(readline("zebishell> "),
				false);
		if (vars->str_in.buff[0])
			add_history(vars->str_in.buff);
		token_m(vars, &vars->tokens);
		if (vars->tokens)
			build_and_run_ast(vars);
	}
	return (0);
}
