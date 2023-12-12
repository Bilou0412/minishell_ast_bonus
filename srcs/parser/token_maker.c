/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_maker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:17:56 by bmoudach          #+#    #+#             */
/*   Updated: 2023/12/12 20:38:44 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	content_to_token(char *content, t_tokens **tok, int type,
		t_expand *lst_expand)
{
	t_tokens	*node;

	node = (t_tokens *)ft_collector(ft_toknew(content, type, lst_expand),
			false);
	ft_tokadd_back(tok, node);
	return (0);
}

int	single_char_tok(t_str_data *str_in, t_tokens **tok)
{
	char	*content;
	int		type;

	if (ft_strchr("<>|()", str_in->buff[str_in->curpos]))
	{
		content = (char *)ft_collector(ft_substr(str_in->buff, str_in->curpos,
					1), false);
		type = tok_type(content);
		content_to_token(content, tok, type, NULL);
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
	if (!ft_strncmp(str_in->buff + curpos, "||", 2)
		|| !ft_strncmp(str_in->buff + curpos, "&&", 2)
		|| !ft_strncmp(str_in->buff + curpos, "<<", 2)
		|| !ft_strncmp(str_in->buff + curpos, ">>", 2)
		|| !ft_strncmp(str_in->buff + curpos, ">|", 2))
	{
		content = (char *)ft_collector(ft_substr(str_in->buff, str_in->curpos,
					2), false);
		type = tok_type(content);
		content_to_token(content, tok, type, NULL);
		return (1);
	}
	return (0);
}

int	make_word(t_str_data *str_in, t_tokens **tok)
{
	int			size_word;
	char		*word;
	t_expand	*lst_expand;

	word = NULL;
	size_word = check_char(str_in);
	if (size_word < 0)
		return (-1);
	else if (!size_word)
		return (str_in->curpos += 2, 0);
	word = (char *)ft_collector(ft_substr(str_in->buff, str_in->curpos,
				size_word), false);
	str_in->curpos += size_word;
	lst_expand = create_lst_expand(word, tok);
	del_quote(word);
	content_to_token(word, tok, WORD, lst_expand);
	return (0);
}

void	token_m(t_vars *vars, t_tokens **tok)
{
	t_str_data	*str_in;

	str_in = &vars->str_in;
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
			ft_tokclear(tok);
			ft_collector((str_in->buff), true);
			return ;
		}
	}
	ft_collector(str_in->buff, true);
	if (syntax_error(&_vars()->tokens))
		ft_tokclear(tok);
}
