/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:58:09 by soutin            #+#    #+#             */
/*   Updated: 2023/11/29 15:56:31 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	multiple_dup2(t_vars *vars, int in, int builtin)
{
	t_files	*tmp;

	if (in)
	{
		tmp = vars->cmd.infiles;
		while (tmp)
		{
			if (dup2(tmp->fd, STDIN_FILENO) < 0)
				return (-1);
			if (close(tmp->fd) < 0)
				return (-1);
			tmp = tmp->next;
		}
	}
	else
	{
		tmp = vars->cmd.outfiles;
		while (tmp)
		{
			if (dup2(tmp->fd, STDOUT_FILENO) < 0)
				return (-1);
			if (close(tmp->fd) < 0)
				return (-1);
			tmp = tmp->next;
		}
	}
	return (0);
}

int	waitchilds(t_vars *vars, int *pid, int childmax)
{
	int	i;
	int	status;

	i = 0;
	while (i < childmax)
	{
		if (waitpid(pid[i], &status, 0) < 0)
			return (-1);
		i++;
		vars->last_return_val = WEXITSTATUS(status);
	}
	return (0);
}

int	dup_toks(t_tokens **new_lst, t_tokens *current)
{
	char		*new_string;
	t_tokens	*new_token;
	int			*new_expand;
	int			i;

	i = 0;
	new_expand = NULL;
	new_string = ft_strdup(current->string);
	if (!new_string)
		return (-1);
	if (current->expand)
	{
		while (current->expand[i] != -1)
			i++;
		new_expand = ft_calloc(i, sizeof(int));
		i = 0;
		while (current->expand[i] != -1)
		{
			new_expand[i] = current->expand[i];
			i++;
		}
		if (!new_expand)
			return (free(new_string), -1);
	}

	new_token = ft_lstnew(new_string, current->type, new_expand);
	if (!new_token)
		return (ft_lstclear(new_lst, &free), -1);
	ft_lstadd_back(new_lst, new_token);
	return (0);
}

t_tokens	*duplicate_current_cmd(t_vars *vars, t_tokens **head, int current_cmd)
{
	t_tokens	*tmp;
	t_tokens	*new_lst;
	int			i;
	
	i = 0;
	tmp = *head;
	new_lst = NULL;
	while (i < current_cmd)
	{
		while (tmp && tmp->type != PIPE)
			tmp = tmp->next;
		if (tmp)
			tmp = tmp->next;
		i++;
	}
	while (tmp)
	{
		if (dup_toks(&new_lst, tmp) < 0)
			return (NULL);
		if (tmp->next && tmp->next->type == PIPE)
			break;
		tmp = tmp->next;
	}
	return (new_lst);
}
