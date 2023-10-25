/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:44:33 by soutin            #+#    #+#             */
/*   Updated: 2023/10/25 15:46:43 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	cmds_lstadd_front(t_cmds **lst, t_cmds *new)
{
	if (*lst)
	{
		new->next = *lst;
	}
	*lst = new;
}

t_cmds *convert_tok_to_node(t_tokens *token)
{
    t_cmds  *new;

    if (!token)
        return (NULL);
    new = (t_cmds*)ft_calloc(1, sizeof(new));
    if (!new)
        return (NULL);
    new->string = token->string;
    new->type = token->type;
    new->next = NULL;
    return (new);
}

 t_ast *ast_lstnew()
{
    t_ast   *new;
    
    new = ft_calloc(1, sizeof(t_ast*));
    if (!new)
        return (NULL);
    new->left = NULL;
    new->right = NULL;
    return (new);
}

int	is_last_cmd(t_tokens *current)
{
	t_tokens	*tmp;

	tmp = current;
	while (tmp && (tmp->type < 4 || tmp->type > 6))
		tmp = tmp->next;
	if (!tmp)
		return (1);
	return (0);
}

int is_command_line(t_tokens *current, t_ast **root)
{
    if (!current)
        return (0);
    if (!*root)
        *root = ast_lstnew();
    if (current->type > 4 || current->type > 6)
    {
        if (!is_last_cmd(current))
        {
			(*root)->right = ast_lstnew();
			is_command(&current, (*root)->right);
		}
		else
		{
			is_command(&current, *root);
			return (0);
		}
    }
    if (current && (current->type >= 4 && current->type <= 6))
    {
        (*root)->cmds = convert_tok_to_node(current);
        (*root)->left = ast_lstnew();
        if (is_command_line(current->next, &(*root)->left) < 0)
			return (-1);
    }
    return (1);
}

void    is_command(t_tokens **current, t_ast *node)
{
    t_cmds  *tmp;
    
    if (!*current)
        return ;
    if ((*current)->type >= 4 && (*current)->type <= 6)
        return ;
    if ((*current)->type < 4 || (*current)->type > 6)
    {
        tmp = convert_tok_to_node(*current);
        cmds_lstadd_front(&node->cmds, tmp);
        *current = (*current)->next;
        is_command(current, node);
    }
}
