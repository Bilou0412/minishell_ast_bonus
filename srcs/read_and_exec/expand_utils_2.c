/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:22:34 by bmoudach          #+#    #+#             */
/*   Updated: 2024/01/15 17:23:03 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
