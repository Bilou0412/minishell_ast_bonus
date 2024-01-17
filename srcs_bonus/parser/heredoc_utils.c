/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:13:31 by soutin            #+#    #+#             */
/*   Updated: 2024/01/12 20:14:46 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_headfile(t_files **head)
{
	t_files	*tmp;

	tmp = (*head)->next;
	ft_collector(*head, true);
	*head = tmp;
}

void	parse_heredoc_cmd(t_vars *vars, t_tokens **head)
{
	t_tokens	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (tmp->type == DLESS)
		{
			close(vars->heredocs->fd);
			del_headfile(&vars->heredocs);
		}
		tmp = tmp->next;
	}
}

void	close_heredocs(t_files **head)
{
	t_files	*tmp;
	t_files	*buf;

	if (!*head)
		return ;
	tmp = *head;
	while (tmp)
	{
		buf = tmp->next;
		close(tmp->fd);
		ft_collector(tmp, true);
		tmp = buf;
	}
	*head = NULL;
}
