/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 18:25:05 by soutin            #+#    #+#             */
/*   Updated: 2023/12/11 17:57:33 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_syntax_error(char *string)
{
	_vars()->error = true;
	return (ft_printf("zebishell: syntax error near unexpected token `%s\'\n",
			string));
}

void	skip_parenthesis(t_tokens **tmp, int *flag)
{
	while (*tmp && *flag)
	{
		if ((*tmp)->type == O_PARENTHESIS)
			(*flag)++;
		else if ((*tmp)->type == C_PARENTHESIS)
			(*flag)--;
		*tmp = (*tmp)->next;
	}
}

int	go_through_paren(t_tokens **head)
{
	t_tokens	*tmp;
	int			flag;

	tmp = *head;
	while (tmp)
	{
		if (tmp->type == C_PARENTHESIS)
			return (print_syntax_error(tmp->string));
		if (tmp->type == O_PARENTHESIS)
		{
			flag = 1;
			tmp = tmp->next;
			skip_parenthesis(&tmp, &flag);
			if (flag)
				return (print_syntax_error("("));
		}
		else
			tmp = tmp->next;
	}
	return (0);
}

int	syntax_error(t_tokens **head)
{
	t_tokens	*tmp;

	tmp = *head;
	if (tmp && tmp->type >= PIPE && tmp->type <= AND)
		return (print_syntax_error(tmp->string));
	if (go_through_paren(&tmp))
		return (1);
	while (tmp)
	{
		if (tmp->type < PIPE && !tmp->next)
			return (print_syntax_error("newline"));
		if (tmp->type < PIPE && tmp->next->type < 10)
			return (print_syntax_error(tmp->next->string));
		if (tmp->type >= PIPE && tmp->type <= AND && !tmp->next)
			return (print_syntax_error("newline"));
		if (tmp->type >= PIPE && tmp->type <= AND
			&& tmp->next->type >= PIPE && tmp->next->type <= AND)
			return (print_syntax_error(tmp->next->string));
		tmp = tmp->next;
	}
	return (0);
}
