/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:23:19 by soutin            #+#    #+#             */
/*   Updated: 2023/11/27 15:36:00 by soutin           ###   ########.fr       */
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
	buffer = getcwd(NULL, 0);
	if (!buffer)
		return (NULL);
	i = ft_strlen(buffer);
	while (i >= 0 && buffer[i] != '/')
		i--;
	i++;
	tmp = ft_substr(buffer, i, ft_strlen(buffer + i));
	if (!tmp)
		return (NULL);
	*prompt = ft_strjoin(tmp, "> ");
	if (!prompt)
		return (NULL);
	free(buffer);
	free(tmp);
	return (*prompt);
}

void	ctrl_c(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	freevars(_vars(), 0);
	rl_on_new_line();
	rl_redisplay();
	rl_replace_line("", 0);
}

int	read_inputs(t_vars *vars)
{
	while (1)
	{
		init_vars(vars);
		if (!get_prompt(&vars->prompt))
			return (-1);
		vars->str_in.buff = readline(vars->prompt);
		if (!vars->str_in.buff)
			return (-1);
		if (vars->str_in.buff[0])
			add_history(vars->str_in.buff);
		if (!token_m(&vars->str_in, &vars->tokens))
		{
			if (launch_ast(vars) < 0)
				return (-1);
			else if (read_ast(vars, vars->ast))
				return (-1);
		}
		if (waitchilds(vars, vars->pid, vars->nb_forks) < 0)
			return (-1);
		freevars(vars, 0);
	}
	return (0);
}
void	nothing(int sig)
{
	(void)sig;
	return ;
}
int	main(int c, char **v, char **envp)
{
	(void)v;
	if (c != 1)
		return (1);
	signal(SIGINT, &ctrl_c);
	signal(SIGQUIT, SIG_IGN);
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
