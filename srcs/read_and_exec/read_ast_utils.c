/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:28:56 by soutin            #+#    #+#             */
/*   Updated: 2023/11/17 16:01:20 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	count_cmd(t_vars *vars, t_ast *head)
{
	t_ast	*tmp;

	tmp = head;
	if (!head)
		return ;
	count_cmd(vars, head->left);
	count_cmd(vars, head->right);
	if ((head->tokens->type < 4 || head->tokens->type > 6))
		vars->cmd.nb_pipes++;
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

int	fill_cmd_argv(t_vars *vars, t_tokens *tokens)
{
	t_tokens	*tmp;
	int			i;
	char		*str;

	i = 0;
	vars->cmd.argv = ft_calloc(ft_lstsize(tokens) + 1, sizeof(char *));
	if (!vars->cmd.argv)
		return (-1);
	tmp = tokens;
	while (tmp)
	{
		while (tmp->string[i] && tmp->string)
		if (tmp->string[0] == '$' && ft_strlen(tmp->string) > 1)
		{
			str = expand(vars, tmp->string + 1);
			if (!str)
				vars->cmd.argv[i] = ft_strdup("");
			else
			{
				vars->cmd.argv[i] = ft_strdup(str);	
			}
		}
		else
		{
			vars->cmd.argv[i] = ft_strdup(tmp->string);
		}
		if (!vars->cmd.argv[i])
			return (freetabs(vars->cmd.argv), -1);
		tmp = tmp->next;	
		i++;
	}
	vars->cmd.argv[i] = NULL;
	return (0);
}
