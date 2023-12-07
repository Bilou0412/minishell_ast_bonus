/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:23:19 by soutin            #+#    #+#             */
/*   Updated: 2023/12/06 18:20:13 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_vars	*_vars(void)
{
	static t_vars	vars;

	return (&vars);
}

void	init_vars(t_vars *vars)
{
	vars->str_in.buff = NULL;
	vars->nb_forks = 0;
	vars->ast = NULL;
	vars->tokens = NULL;
	vars->cmd.nb_pipes = 0;
	vars->cmd.env_paths = NULL;
	vars->cmd.argv = NULL;
	vars->cmd.path = NULL;
	vars->cmd.infiles = NULL;
	vars->cmd.outfiles = NULL;
	vars->last_return_val = 0;
}

//e1 | e2 || e3 | (e4 || e5 && e7) | e6 | e7 || e8

// int	ft_fd_collector(int fd, bool clean)
// {
// 	static t_list	*list;
	
// 	int	tmp;
	
// 	if (fd)
// 	{
// 		ft_lstadd_back(&list, ft_lstnew(NULL, fd));
// 	}
	
// }

int	read_inputs(t_vars *vars)
{
	while (1)
	{
		init_vars(vars);
		vars->str_in.buff = (char *)ft_collector(readline("zebishell> "), false);
		if (vars->str_in.buff[0])
			add_history(vars->str_in.buff);
		token_m(&vars->str_in, &vars->tokens);
		if (vars->tokens)
			if (launch_ast(vars) < 0)
				return (-1);
	}
	return (0);
}

int	main(int c, char **v, char **envp)
{
	(void)v;
	if (c != 1)
		return (1);
	// shrek_print();
	signal(SIGINT, &ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	tcgetattr(STDIN_FILENO, &_vars()->original);
	if (setup_env(&_vars()->envl, envp) < 0)
		return (-1);
	if (read_inputs(_vars()) < 0)
	{
		freevars(_vars(), 1);
		return (1);
	}
	freevars(_vars(), 1);
	return (0);
}