/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:51:16 by soutin            #+#    #+#             */
/*   Updated: 2023/12/07 21:34:58by bmoudach         ###   ########.fr       */
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
		if (size == 1 && word[i] == '?')
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

t_expand	*create_lst_expand(char *word, t_tokens **tok)
{
	t_expand	*lst_expand;
	int			i_word;
	char		quote_char;

	lst_expand = NULL;
	i_word = 0;
	quote_char = false;
	while (word[i_word])
	{
		if (word[i_word] == '\'' || word[i_word] == '\"')
		{
			if (!quote_char)
				quote_char = word[i_word];
			else if (quote_char == word[i_word])
				quote_char = false;
		}
		else if (word[i_word] == '$')
		{
			if (quote_char == '\'')
				content_to_lst_expand(NULL, &lst_expand);
			else
			{
				content_to_lst_expand(get_key_to_exp(word, &i_word),
					&lst_expand);
			}
		}
		i_word++;
	}
	return (lst_expand);
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
				tmp->value = ft_itoa(_vars()->last_return_val);
			else if (search_envl(envl, tmp->to_expand + 1))
				tmp->value = search_envl(envl, tmp->to_expand + 1)->value;
		}
		tmp = tmp->next;
	}
}

char	*replace_key_for_value(char *src_str, int *start, t_expand *expand)
{
	char	*beginning_str;
	char	*and_str;
	char	*dest_str;
	int		size_to_expand;

	if (expand->to_expand)
	{
		size_to_expand = ft_strlen(expand->to_expand);
		beginning_str = ft_collector(ft_substr(src_str, 0, *start), false);
		and_str = ft_collector(ft_strdup(src_str + *start + size_to_expand),
				false);
		if (expand->value)
		{
			dest_str = ft_collector(ft_strjoin(beginning_str, expand->value),
					false);
			dest_str = ft_collector(ft_strjoin_gnl(dest_str, and_str), false);
			*start = ft_strlen(beginning_str) + ft_strlen(expand->value) - 1;
		}
		else
		{
			dest_str = ft_collector(ft_strjoin(beginning_str, and_str), false);
			*start = ft_strlen(beginning_str) - 1;
		}
	}
	else
		return (src_str);
	return (ft_collector(src_str, true), dest_str);
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

void	expand(t_vars *vars, t_tokens **head)
{
	t_tokens *tmp;

	tmp = *head;
	while (tmp)
	{
		if (tmp)
		{
			get_value_of_key(&vars->envl, &tmp->expand);
			tmp->string = parse_replace_expand(&(tmp->expand), tmp->string);
		}
		tmp = tmp->next;
	}
}