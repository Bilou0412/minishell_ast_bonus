/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:23:19 by soutin            #+#    #+#             */
/*   Updated: 2023/11/15 13:14:43 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_vars	*_vars(void)
{
	static t_vars	vars;

	return (&vars);
}

char	*search_envl(t_vars *vars, char *var_name)
{
	int	i;
	int	size_name_envl;
	int	size_name_var;

	i = 0;
	size_name_var = ft_strlen_to_char(var_name, '=');
	while (vars->envl[i])
	{
		size_name_envl = ft_strlen_to_char(vars->envl[i], '=');
		if (size_name_envl == size_name_var)
		{
			if (!ft_strncmp(var_name, vars->envl[i], size_name_envl))
				return (vars->envl[i]);
		}
		i++;
	}
	return (NULL);
}

void	init_vars(t_vars *vars)
{
	vars->str_in.buff = NULL;
	vars->cmd.nb_pipes = 0;
	vars->nb_forks = 0;
	vars->ast = NULL;
	vars->tokens = NULL;
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
		if (waitchilds(vars, vars->nb_forks) < 0)
			return (-1);
		// print_tree(vars->ast, 0);
		freevars(vars, 0);
	}
	return (0);
}

int	setup_env(t_vars *vars, char **envp)
{
	vars->envl = ft_arraydup(envp);
	if (!vars->envl)
		return (-1);
	vars->cmd.env_paths = init_paths(vars);
	if (!vars->cmd.env_paths)
		return (freetabs(vars->envl), -1);
	return (0);
}
static void	ctrl_c(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

int	main(int c, char **v, char **envp)
{
	(void)v;
	if (c != 1)
		return (1);
	signal(SIGINT, &ctrl_c);
	if (setup_env(_vars(), envp) < 0)
		return (-1);
	if (read_inputs(_vars()) < 0)
		return (1);
	freetabs(_vars()->envl);
	freetabs(_vars()->cmd.env_paths);
	return (0);
}
