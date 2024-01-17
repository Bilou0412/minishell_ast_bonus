/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:22:34 by bmoudach          #+#    #+#             */
/*   Updated: 2024/01/15 18:41:05 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_quote_char(char *quote_char, char *word, int i_word)
{
	if (!*quote_char)
		*quote_char = word[i_word];
	else if (*quote_char == word[i_word])
		*quote_char = false;
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
			check_quote_char(&quote_char, word, i_word);
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

char	*init_replace(t_expand *expand, char **beginning_str, char *src_str,
	int *start)
{
	int		size_to_expand;

	size_to_expand = ft_strlen(expand->to_expand);
	*beginning_str = ft_collector(ft_substr(src_str, 0, *start), false);
	return (ft_collector(ft_strdup(src_str + *start + size_to_expand), false));
}

char	*replace_key_for_value(char *src_str, int *start, t_expand *expand)
{
	char	*beginning_str;
	char	*and_str;
	char	*dest_str;

	beginning_str = NULL;
	if (expand->to_expand)
	{
		and_str = init_replace(expand, &beginning_str, src_str, start);
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
