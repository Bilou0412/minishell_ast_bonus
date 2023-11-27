/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:28:56 by soutin            #+#    #+#             */
/*   Updated: 2023/11/27 15:54:36 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	here_doc_loop(t_cmd *cmd, t_tokens *curr)
{
	char	*buf;
	int		fd;
	char	*limiter;

	buf = NULL;
	fd = open("here_doc", O_RDWR | O_TRUNC | O_CREAT, 0666);
	if (fd < 0)
		return (ft_printf("%s\n", strerror(errno)), -1);
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

void	delete_file_tokens(t_tokens **head, t_tokens **curr)
{
	t_tokens	*tmp;

	if (*curr == *head)
	{
		*head = (*head)->next->next;
		free((*curr)->next->string);
		free((*curr)->next);
		free((*curr)->string);
		free(*curr);
		*curr = *head;
	}
	else
	{
		tmp = *head;
		while (tmp->next && tmp->next != *curr)
			tmp = tmp->next;
		tmp->next = (*curr)->next->next;
		free((*curr)->next->string);
		free((*curr)->next);
		free((*curr)->string);
		free(*curr);
		*curr = tmp->next;
	}
}

int	file_add_back(t_files **head, int new_fd)
{
	t_files	*tmp;
	t_files	*new;

	new = ft_calloc(1, sizeof(t_files));
	if (!new)
		return (-1);
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

	if (arm->type == GREAT)
	{
		fd = open(arm->next->string, O_WRONLY | O_TRUNC | O_CREAT, 0666);
		if (fd < 0)
			return (-1);
		if (file_add_back(&cmd->outfiles, fd) < 0)
			return (-1);
	}
	else if (arm->type == DGREAT)
	{
		fd = open(arm->next->string, O_WRONLY | O_APPEND | O_CREAT, 0666);
		if (fd < 0)
			return (-1);
		if (file_add_back(&cmd->outfiles, fd) < 0)
			return (-1);
	}
	return (0);
}

int	handle_files(t_cmd *cmd, t_tokens *arm)
{
	int	fd;

	if (!arm->next && arm->next->type != WORD)
		return (-1);
	if (arm->type == LESS)
	{
		fd = open(arm->next->string, O_RDONLY);
		if (fd < 0)
			return (-1);
		if (file_add_back(&cmd->infiles, fd) < 0)
			return (-1);
	}
	else if (arm->type == DLESS)
	{
		if (here_doc_loop(cmd, arm) < 0)
			return (-1);
		fd = open("here_doc", O_RDONLY);
		if (fd < 0)
			return (-1);
		if (file_add_back(&cmd->infiles, fd) < 0)
			return (-1);
	}
	else if (handle_files_2(cmd, arm) < 0)
		return (-1);
	return (0);
}
