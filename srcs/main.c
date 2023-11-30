/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:23:19 by soutin            #+#    #+#             */
/*   Updated: 2023/11/30 18:48:49 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

char	*get_prompt(char **prompt)
{
	int		i;
	char	*buffer;
	char	*tmp;

	tmp = NULL;
	*prompt = NULL;
	buffer = (char*)ft_collector(getcwd(NULL, 0), false);
	if (!buffer)
		exit_prog();
	i = ft_strlen(buffer);
	while (i >= 0 && buffer[i] != '/')
		i--;
	i++;
	tmp = (char*)ft_collector(ft_substr(buffer, i, ft_strlen(buffer + i)), false);
	if (!tmp)
		(free(buffer), exit_prog());
	*prompt = (char*)ft_collector(ft_strjoin(tmp, "> "), false);
	ft_collector(buffer, true);
	ft_collector(tmp, true);
	return (*prompt);
}

int	read_inputs(t_vars *vars)
{
	while (1)
	{
		init_vars(vars);
		if (!get_prompt(&vars->prompt))
			return (-1);
		vars->str_in.buff = (char*)ft_collector(readline(vars->prompt), false);
		ft_collector(vars->prompt, true);
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
	signal(SIGINT, &ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	tcgetattr(STDIN_FILENO, &_vars()->original);
	if (setup_env(_vars(), envp) < 0)
		return (-1);
	if (read_inputs(_vars()) < 0)
	{
		freevars(_vars(), 1);
		return (1);
	}
	freevars(_vars(), 1);
	return (0);
}
