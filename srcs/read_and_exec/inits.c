/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:20:32 by soutin            #+#    #+#             */
/*   Updated: 2023/11/14 18:24:26 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	init_cmd_path(t_vars *vars)
{
	int	i;

	i = 0;
	if (vars->cmd.path)
		return (0);
	while (vars->cmd.env_paths[i])
	{
		vars->cmd.path = cmdjoin(vars->cmd.env_paths[i], vars->cmd.argv[0]);
		if (!vars->cmd.path)
			return (perror("join"), -1);
		// printf("%s\n", vars->cmd.path);
		if (access(vars->cmd.path, F_OK | X_OK) == 0)
			return (0);
		if (vars->cmd.path)
			free(vars->cmd.path);
		vars->cmd.path = NULL;
		i++;
	}
	ft_printf("command not found: %s\n", vars->cmd.argv[0]);
	return (-1);
}

int	path_to_argv(t_cmd *cmd)
{
	char	**tmp;
	int		i;

	i = 0;
	if (!access(cmd->argv[0], F_OK | X_OK))
	{
		cmd->path = cmd->argv[0];
		tmp = ft_split(cmd->argv[0], '/');
		if (!tmp)
			return (-1);
		while (tmp[i + 1])
			i++;
		free(cmd->argv[0]);
		cmd->argv[0] = ft_substr(tmp[i], 0, ft_strlen(tmp[i]));
		freetabs(tmp);
		if (!cmd->argv[0])
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
	printf("\nok\n");
	limiter = curr->next->string;
	while (1)
	{
		buf = readline("heredoc> ");
		if (!buf)
			return (close(fd), -1);
		ft_putstr_fd(buf, fd);
		if (!ft_strncmp(buf, limiter, ft_strlen(limiter)))
			break ;
		free(buf);
	}
	ft_putstr_fd(NULL, fd);
	free(buf);
	close(fd);
	return (0);
}

int	init_cmd_and_files(t_vars *vars, t_tokens **head)
{
	
	if (sort_cmd(vars, head) < 0)
		return (-1);
	if (path_to_argv(&vars->cmd) < 0)
		return (freevars(vars, 1), -1);
	else if (init_cmd_path(vars) < 0)
		return (freevars(vars, 1), -1);
	return (0);
}
