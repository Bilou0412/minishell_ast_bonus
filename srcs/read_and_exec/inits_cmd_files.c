/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_cmd_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:28:56 by soutin            #+#    #+#             */
/*   Updated: 2024/01/19 17:45:59 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	file_add_back(t_files **head, int new_fd, char *name, int index)
{
	t_files	*tmp;
	t_files	*new;

	new = (t_files *)ft_collector(ft_calloc(1, sizeof(t_files)), false);
	new->fd = new_fd;
	new->delim = name;
	new->index = index;
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
		file_add_back(&cmd->outfiles, fd, NULL, 0);
	}
	else if (arm->type == DGREAT)
	{
		fd = open(arm->next->string, O_WRONLY | O_APPEND | O_CREAT, 0666);
		if (fd < 0)
			return (ft_printf("zebishell: "), perror(arm->next->string), -1);
		file_add_back(&cmd->outfiles, fd, NULL, 0);
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
		file_add_back(&cmd->infiles, fd, NULL, 0);
	}
	else if (arm->type == DLESS)
	{
		while (arm->next->heredoc_index != _vars()->heredocs->index)
			_vars()->heredocs = _vars()->heredocs->next;
		file_add_back(&cmd->infiles, _vars()->heredocs->fd, NULL, 0);
	}
	else if (handle_files_2(cmd, arm) < 0)
		return (-1);
	return (0);
}
