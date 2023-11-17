/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_maker_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:23:40 by bmoudach          #+#    #+#             */
/*   Updated: 2023/11/17 15:56:26 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// renvois le type de content
int	tok_type(char *content)
{
	if (!ft_strncmp(content, "||", 2))
		return (OR);
	if (!ft_strncmp(content, "&&", 2))
		return (AND);
	if (!ft_strncmp(content, "<<", 2))
		return (DLESS);
	if (!ft_strncmp(content, ">>", 2))
		return (DGREAT);
	if (content[0] == '<')
		return (LESS);
	if (content[0] == '>')
		return (GREAT);
	if (content[0] == '|')
		return (PIPE);
	if (content[0] == '(')
		return (O_PARENTHESIS);
	if (content[0] == ')')
		return (C_PARENTHESIS);
	return (WORD);
}

int	char_is_quote(t_str_data *str_in, int *word_size, char *current)
{
	char	quote;

	quote = *current;
	(*word_size)++;
	*current = str_in->buff[str_in->curpos + *word_size];
	while (*word_size + str_in->curpos < str_in->buff_size)
	{
		if (*current == quote)
			break ;
		(*word_size)++;
		*current = str_in->buff[str_in->curpos + *word_size];
	}
	if (*current == '\0')
		return (printf("quote error\n"), -1);
	return (0);
}

int	check_char(t_str_data *str_in)
{
	char	current;
	int		word_size;

	word_size = 0;
	while (word_size + str_in->curpos <= str_in->buff_size)
	{
		current = str_in->buff[str_in->curpos + word_size];
		if (current == '\'' || current == '\"')
			if (char_is_quote(str_in, &word_size, &current) < 0)
				return (-1);
		if ((ft_strchr(" \t\n", current) || (tok_type(&current) != WORD && tok_type(&current) != DOLLARS))
			|| (current == '&' && str_in->buff[str_in->curpos + word_size
					+ 1] == '&'))
			break ;
		word_size++;
	}
	return (word_size);
}

char	get_quote_to_del(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '\'' || word[i] == '\"')
			return (word[i]);
		else
			i++;
	}
	return (0);
}

char	*del_quote(char *word)
{
	char	quote;
	int		i;
	int		size;
	char	*word_unquoted;

	i = 0;
	size = 0;
	quote = get_quote_to_del(word);
	while (word[i++])
	{
		if (word[i] != quote)
			size++;
	}
	word_unquoted = ft_calloc(size + 1, sizeof(char));
	if (!word_unquoted)
		return (free(word), NULL);
	i = 0;
	size = 0;
	while (word[i++])
	{
		if (word[i] != quote)
			word_unquoted[size++] = word[i];
	}
	return (word_unquoted[size] = '\0', free(word), word_unquoted);
}
