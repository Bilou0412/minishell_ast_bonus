/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_cmd_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:28:56 by soutin            #+#    #+#             */
/*   Updated: 2023/12/12 20:41:21 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc_loop(t_cmd *cmd, t_tokens *curr)
{
	char	*buf;
	int		fd;
	char	*limiter;
	int		pid;
	int		status;

	buf = NULL;
	pid = fork();
	if (pid < 0)
		return (-1);
	if (!pid)
	{
		signal(SIGINT, &ctrl_c_child);
		fd = open("here_doc", O_RDWR | O_TRUNC | O_CREAT, 0666);
		if (fd < 0)
			return (ft_printf("%s\n", strerror(errno)), exit(1), -1);
		limiter = (char *)ft_collector(ft_strjoin(curr->next->string, "\n"),
				false);
		while (1)
		{
			buf = get_next_line(1);
			if (!buf)
				return (close(fd), exit_prog(1), -1);
			if (!ft_strncmp(buf, limiter, ft_strlen(limiter)))
				break ;
			ft_putstr_fd(buf, fd);
			ft_collector(buf, true);
		}
		ft_putstr_fd(NULL, fd);
		ft_collector(NULL, true);
		close(fd);
		exit(0);
	}
	else
		waitpid(pid, &status, 0);
	return (0);
}

void	delete_file_tokens(t_tokens **head, t_tokens **curr)
{
	t_tokens	*tmp;

	if (*curr == *head)
	{
		*head = (*head)->next->next;
		ft_collector((*curr)->next->string, true);
		ft_collector((*curr)->next, true);
		ft_collector((*curr)->string, true);
		ft_collector(*curr, true);
		*curr = *head;
	}
	else
	{
		tmp = *head;
		while (tmp->next && tmp->next != *curr)
			tmp = tmp->next;
		tmp->next = (*curr)->next->next;
		ft_collector((*curr)->next->string, true);
		ft_collector((*curr)->next, true);
		ft_collector((*curr)->string, true);
		ft_collector(*curr, true);
		*curr = tmp->next;
	}
}

int	file_add_back(t_files **head, int new_fd)
{
	t_files	*tmp;
	t_files	*new;

	new = (t_files *)ft_collector(ft_calloc(1, sizeof(t_files)), false);
	new->fd = new_fd;
	new->next = NULL;
	if (head)
	{
		if (*head == NULL)
			*head = new;
		else
		{
			tmp = *head;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
	}
	return (0);
}

int	handle_files_2(t_cmd *cmd, t_tokens *arm)
{
	int	fd;

	if (arm->type == GREAT || arm->type == CLOBBER)
	{
		fd = open(arm->next->string, O_WRONLY | O_TRUNC | O_CREAT, 0666);
		if (fd < 0)
			return (ft_printf("zebishell: "), perror(arm->next->string), -1);
		file_add_back(&cmd->outfiles, fd);
	}
	else if (arm->type == DGREAT)
	{
		fd = open(arm->next->string, O_WRONLY | O_APPEND | O_CREAT, 0666);
		if (fd < 0)
			return (ft_printf("zebishell: "), perror(arm->next->string), -1);
		file_add_back(&cmd->outfiles, fd);
	}
	return (0);
}

int	handle_files(t_cmd *cmd, t_tokens *arm)
{
	int	fd;

	if (arm->type == LESS)
	{
		fd = open(arm->next->string, O_RDONLY);
		if (fd < 0)
			return (ft_printf("zebishell: "), perror(arm->next->string), -1);
		file_add_back(&cmd->infiles, fd);
	}
	else if (arm->type == DLESS)
	{
		if (here_doc_loop(cmd, arm) < 0)
			return (-1);
		fd = open("here_doc", O_RDONLY);
		if (fd < 0)
			return (-1);
		file_add_back(&cmd->infiles, fd);
	}
	else if (handle_files_2(cmd, arm) < 0)
		return (-1);
	return (0);
}
