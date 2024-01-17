/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:23:51 by bmoudach          #+#    #+#             */
/*   Updated: 2024/01/17 16:19:37 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// This function return the next key to expand in word,
// key start by $ and finish by ' " or \0
char	*get_key_to_exp(char *word, int *start)
{
	char	*to_expand;
	int		size;
	int		i;

	i = *start;
	size = 0;
	to_expand = NULL;
	while (word[i])
	{
		if (size == 1 && (word[i] == '?' || ft_isdigit(word[i])))
		{
			size++;
			break ;
		}
		else if (size > 0 && (!ft_isalnum(word[i]) && word[i] != '_'))
			break ;
		i++;
		size++;
	}
	if (size > 1)
		to_expand = ft_collector(ft_substr(word, *start, size), false);
	*start += size - 1;
	return (to_expand);
}

void	get_value_of_key(t_env **envl, t_expand **head)
{
	t_expand	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (tmp->to_expand)
		{
			if (tmp->to_expand && !ft_strncmp("$?", tmp->to_expand, 3))
				tmp->value = ft_collector(ft_itoa(_vars()->return_value),
						false);
			else if (search_envl(envl, tmp->to_expand + 1))
				tmp->value = search_envl(envl, tmp->to_expand + 1)->value;
		}
		tmp = tmp->next;
	}
}

char	*parse_replace_expand(t_expand **expand, char *src_str)
{
	char		*dest_str;
	t_expand	*tmp;
	int			i_string;

	i_string = 0;
	tmp = *expand;
	dest_str = ft_collector(ft_strdup(src_str), false);
	while (dest_str[i_string])
	{
		if (dest_str[i_string] == '$')
		{
			dest_str = replace_key_for_value(dest_str, &i_string, tmp);
			tmp = tmp->next;
		}
		i_string++;
	}
	return (dest_str);
}

void	delete_1_tok(t_tokens **head, t_tokens *current)
{
	t_tokens	*tmp;

	if (current == *head)
		*head = (*head)->next;
	else
	{
		tmp = *head;
		while (tmp && tmp->next != current)
			tmp = tmp->next;
		if (tmp)
			tmp->next = current->next;
	}
	current->next = NULL;
	ft_tokclear(&current);
}

void	expand(t_vars *vars, t_tokens **head)
{
	t_tokens	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (tmp)
		{
			get_value_of_key(&vars->envl, &tmp->expand);
			tmp->string = parse_replace_expand(&(tmp->expand), tmp->string);
			if (!*tmp->string && tmp->next)
				delete_1_tok(head, tmp);
		}
		tmp = tmp->next;
	}
}
