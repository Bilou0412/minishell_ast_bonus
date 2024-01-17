/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_maker_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:23:40 by bmoudach          #+#    #+#             */
/*   Updated: 2024/01/09 17:52:48 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (!ft_strncmp(content, ">|", 2))
		return (CLOBBER);
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
	int		in_quote;
	char	quote;

	quote = *current;
	in_quote = true;
	*current = str_in->buff[str_in->curpos + ++(*word_size)];
	while (*current)
	{
		if (*current == quote && in_quote == true)
			in_quote = false;
		else if (ft_strchr("\'\"", *current) && in_quote == false)
		{
			in_quote = true;
			quote = *current;
		}
		else if (ft_strchr("<>|& ", *current) && in_quote == false)
			break ;
		*current = str_in->buff[str_in->curpos + ++(*word_size)];
	}
	if (in_quote == true)
		return (printf("zebishell: missing quote\n"), -1);
	else
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
		if ((ft_strchr(" \t\n", current) || (tok_type(&current) != WORD))
			|| (current == '&' && str_in->buff[str_in->curpos + word_size
					+ 1] == '&'))
			break ;
		word_size++;
	}
	return (word_size);
}

void	del_char(char *address, char char_to_del)
{
	while (*address != '\0' && *address != char_to_del)
		address++;
	if (*address == char_to_del)
	{
		while (*address != '\0')
		{
			*address = *(address + 1);
			address++;
		}
	}
}

int	del_quote(char *str)
{
	int		in_quote;
	char	quote;
	int		i;

	i = 0;
	quote = 0;
	in_quote = false;
	while (str[i])
	{
		if (ft_strchr("\'\"", str[i]) && in_quote == false)
		{
			in_quote = true;
			quote = str[i];
			del_char(str + i, quote);
			i--;
		}
		else if (str[i] == quote && in_quote == true)
		{
			in_quote = false;
			del_char(str + i, quote);
			i--;
		}
		i++;
	}
	return (0);
}
