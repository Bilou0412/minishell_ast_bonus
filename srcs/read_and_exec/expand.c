/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:51:16 by soutin            #+#    #+#             */
/*   Updated: 2023/12/07 15:58:55 by bmoudach         ###   ########.fr       */
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
