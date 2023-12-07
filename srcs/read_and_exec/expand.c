/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
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
	while (word[i])
	{
		if (size == 1 && word[i] == '$')
		{
			size++;
			break ;
		}
		else if (word[i] == '\'' || word[i] == '\"' || (word[i] == '$'
			&& size > 1))
			break ;
		i++;
		size++;
	}
	to_expand = ft_collector(ft_substr(word, *start, size), false);
	*start += size - 1;
	return (to_expand);
}

//' " \0
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
				content_to_lst_expand(get_key_to_exp(word, &i_word),
					&lst_expand);
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
			tmp->value = search_envl(envl, tmp->to_expand);
		tmp = tmp->next;
	}
}

char	*replace_key_for_value(char *src_str, int *start, t_expand *expand)
{
	char	*dest_src;
	int		i_src_str;
	int		size_dest_src;
	int		size_to_expand;
	int		size_value;

	if (!expand->to_expand)
		return (NULL);
		
	return (dest_src);
}
char	*parse_replace_expand(t_expand **expand, char *src_str)
{
	char		*dest_str;
	t_expand	*tmp;
	int			i_string;

	i_string = 0;
	tmp = *expand;
	dest_str = ft_collector(ft_strdup(src_str), false);
	while (tmp)
	{
		while (src_str[i_string])
		{
			if (src_str[i_string] == '$')
				dest_str = replace_key_for_value(dest_str, &i_string, tmp);
			i_string++;
		}
		tmp = tmp->next;
	}
}

int	expand(t_vars *vars, t_tokens **head)
{
	t_tokens *tmp;

	tmp = *head;
	while (tmp)
	{
		if (tmp->expand)
		{
			get_value_of_key(&vars->envl, &tmp->expand);
			tmp->string = parse_replace_expand(&(tmp->expand), tmp->string);
		}
		tmp = tmp->next;
	}
}