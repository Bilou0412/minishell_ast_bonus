/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:23:19 by soutin            #+#    #+#             */
/*   Updated: 2023/12/13 15:08:16 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_vars	*_vars(void)
{
	static t_vars	vars;

	return (&vars);
}

// void	init_vars(t_vars *vars)
// {
// 	vars->str_in.buff = NULL;
// 	vars->nb_forks = 0;
// 	vars->ast = NULL;
// 	vars->tokens = NULL;
// 	vars->cmd.nb_pipes = 0;
// 	vars->cmd.env_paths = NULL;
// 	vars->cmd.argv = NULL;
// 	vars->cmd.path = NULL;
// 	vars->cmd.infiles = NULL;
// 	vars->cmd.outfiles = NULL;
// 	vars->last_return_val = 0;
// }

int	init_minishell(t_vars *vars, char **envp)
{
	// shrek_print();
	signal(SIGINT, &ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	if (setup_env(&vars->envl, envp) < 0)
		return (1);
	tcgetattr(STDIN_FILENO, &_vars()->original);
	return (0);
}

int	launch_ast(t_vars *vars)
{
	vars->ast = is_branch(&vars->tokens, 0);
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
