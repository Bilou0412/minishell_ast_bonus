/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_maker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:17:56 by bmoudach          #+#    #+#             */
/*   Updated: 2023/11/29 23:09:52 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	content_to_token(char *content, t_tokens **tok, int type, int *expand)
{
	t_tokens	*node;

	node = ft_lstnew(content, type, expand);
	if (!node)
	{
		free(content);
		freevars(_vars(), 0);
		exit(1);
	}
	ft_lstadd_front(tok, node);
	return (0);
}

int	single_char_tok(t_str_data *str_in, t_tokens **tok)
{
	char	*content;
	int		type;

	if (ft_strchr("<>|()", str_in->buff[str_in->curpos]))
	{
		content = ft_substr(str_in->buff, str_in->curpos, 1);
		if (!content)
		{
			freevars(_vars(), 0);
			exit(1);
		}
		type = tok_type(content);
		content_to_token(content, tok, type, (int*)0);
		return (1);
	}
	return (0);
}

int	double_char_tok(t_str_data *str_in, t_tokens **tok)
{
	char	*content;
	int		type;
	int		curpos;

	curpos = str_in->curpos;
	if (!ft_strncmp(str_in->buff + curpos, "||", 2) || !ft_strncmp(str_in->buff
			+ curpos, "&&", 2) || !ft_strncmp(str_in->buff + curpos, "<<", 2)
		|| !ft_strncmp(str_in->buff + curpos, ">>", 2))
	{
		content = ft_substr(str_in->buff, str_in->curpos, 2);
		if (!content)
		{
			freevars(_vars(), 0);
			exit(1);
		}
		type = tok_type(content);
		content_to_token(content, tok, type, (int*)0);
		return (1);
	}
	return (0);
}

int	make_word(t_str_data *str_in, t_tokens **tok)
{
	int		size_word;
	char	*word;
	int		*expand;

	word = NULL;
	size_word = check_char(str_in);
	if (size_word < 0)
		return (-1);
	else if (!size_word)
		return (str_in->curpos += 2, 0);
	word = ft_substr(str_in->buff, str_in->curpos, size_word);
	if (!word)
	{
		freevars(_vars(), 0);
		exit(1);
	}
	str_in->curpos += size_word;
	expand = char_to_expand(word);
	if (expand)
		del_quote(word);
	content_to_token(word, tok, WORD, expand);
	return (0);
}

int	token_m(t_str_data *str_in, t_tokens **tok)
{
	if (str_in->buff)
		str_in->buff_size = ft_strlen(str_in->buff);
	str_in->curpos = 0;
	while (str_in->curpos < str_in->buff_size)
	{
		if (double_char_tok(str_in, tok))
			str_in->curpos += 2;
		else if (single_char_tok(str_in, tok) || ft_strchr(" \t\n",
				str_in->buff[str_in->curpos]))
			str_in->curpos++;
		else if (make_word(str_in, tok) < 0)
		{
			ft_lstclear(tok, &free);
			super_free(&str_in->buff);
			return (-1);
		}
	}
	super_free(&str_in->buff);
	return (0);
}
