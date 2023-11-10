/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:20:32 by soutin            #+#    #+#             */
/*   Updated: 2023/11/10 14:38:14 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	init_cmd_path(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->envp_paths[i])
	{
		if (vars->cmd.cmd_path)
			free(vars->cmd.cmd_path);
		vars->cmd.cmd_path = cmdjoin(vars->envp_paths[i], vars->cmd.argv[0]);
		if (!vars->cmd.cmd_path)
			return (perror("join"), -1);
		if (access(vars->cmd.cmd_path, F_OK | X_OK) == 0)
			return (0);
		i++;
	}
	printf("la");
	ft_printf("command not found: %s\n", vars->cmd.argv[0]);
	return (-1);
}

int	path_to_argv(char **argv)
{
	char	**tmp;
	int		i;

	i = 0;
	if (!access(argv[0], F_OK | X_OK))
	{
		tmp = ft_split(argv[0], '/');
		if (!tmp)
			return (-1);
		while (tmp[i + 1])
			i++;
		free(argv[0]);
		argv[0] = ft_substr(tmp[i], 0, ft_strlen(tmp[i]));
		freetabs(tmp);
		if (!argv[0])
			return (-1);
		return (0);
	}
	return (0);
}

int	here_doc_loop(t_cmd *cmd, t_tokens *curr)
{
	char	*buf;
	int		fd;
	char	*limiter;

	buf = NULL;
	fd = open("here_doc", O_RDWR | O_TRUNC | O_CREAT, 0666);
	if (fd < 0)
		return (ft_printf("%s\n", strerror(errno)), -1);
	limiter = ft_strjoin(curr->next->string, "\n");
	if (!limiter)
		return (-1);
	while (1)
	{
		buf = get_next_line(STDIN_FILENO);
		if (!buf)
			return (free(limiter), close(fd), -1);
		ft_putstr_fd(buf, fd);
		if (!ft_strncmp(buf, limiter, ft_strlen(limiter)))
			break ;
		free(buf);
	}
	ft_putstr_fd(NULL, fd);
	free(buf);
	close(fd);
	return (free(limiter), 0);
}

int	init_cmd_and_files(t_vars *vars, int i)
{
	if (path_to_argv(vars->cmd.argv) < 0)
		return (freevars(vars, i), -1);
	else if (init_cmd_path(vars) < 0)
		return (freevars(vars, i), -1);
	return (0);
}
