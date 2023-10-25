/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_mak.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:17:56 by bmoudach          #+#    #+#             */
/*   Updated: 2023/10/25 16:00:42 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	content_to_token(char *content, t_tokens **tok, int type)
{
	t_tokens	*node;

	node = ft_lstnew(content, type);
	if (!node)
		return (-1);
	ft_lstadd_front(tok, node);
	return (0);
}

int	single_char_tok(t_input_str *str_in, t_tokens **tok)
{
	char	*content;
	int		type;

	content = ft_substr(str_in->buff, str_in->curpos, 1);
	if (!content)
		return (-1);
	type = tok_type(content);
	if (ft_strchr("<>|()", str_in->buff[str_in->curpos]))
	{
		if (!content_to_token(content, tok, type))
			return (1);
		else
			return (free(content), 0);
	}
	return (free(content), 0);
}

int	double_char_tok(t_input_str *str_in, t_tokens **tok)
{
	char	*content;
	int		type;

	content = ft_substr(str_in->buff, str_in->curpos, 2);
	if (!content)
		return (-1);
	type = tok_type(content);
	if (!ft_strncmp(content, "||", 2) || !ft_strncmp(content, "&&", 2)
		|| !ft_strncmp(content, "<<", 2) || !ft_strncmp(content, ">>", 2))
	{
		if (!content_to_token(content, tok, type))
			return (1);
		else
			return (free(content), -1);
	}
	return (free(content), 0);
}

int	make_word(t_input_str *str_in, t_tokens **tok)
{
	int		size_word;
	char	*word;

	word = NULL;
	size_word = check_char(str_in);
	if (size_word == -1)
		return (-1);
	if (size_word)
	{
		word = ft_substr(str_in->buff, str_in->curpos, size_word);
		if (!word)
			return (-1);
		str_in->curpos += size_word;
	}
	else if (!size_word)
		return (str_in->curpos += 2, 0);
	if (!word)
		return (-1);
	if (content_to_token(word, tok, WORD) == -1)
		return (-1);
	return (0);
}

int	token_m(t_input_str *str_in, t_tokens **tok)
{
	str_in->buff_size = ft_strlen(str_in->buff);
	str_in->curpos = 0;
	while (str_in->curpos < str_in->buff_size)
	{
		if (double_char_tok(str_in, tok))
			str_in->curpos += 2;
		else if (single_char_tok(str_in, tok)
			|| str_in->buff[str_in->curpos] == ' ')
			str_in->curpos++;
		else
			make_word(str_in, tok);
	}
	return (0);
}
