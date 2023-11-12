/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:07:58 by bmoudach          #+#    #+#             */
/*   Updated: 2023/11/12 17:10:29 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_for_echo(char *str_to_print)
{
	char	c;

	c = 0;
	while (*str_to_print)
	{
		if (ft_strchr("\'\"", *str_to_print) && c == 0)
		{
			c = *str_to_print;
			str_to_print++;
		}
		else if (c != '\0' && c == *str_to_print)
			str_to_print++;
		else
		{
			ft_putchar_fd(*str_to_print, 1);
			str_to_print++;
		}
	}
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

int	is_option(t_tokens **head)
{
	t_tokens	*current;
	char		*current_string;
	int			i;

	i = 0;
	current = *head;
	current = current->next;
	while (current)
	{
		if (current->type == WORD)
		{
			current_string = del_quote(current->next);
			if (!current_string)
				return (NULL);
			if (current_string[i] == '-')
			{
				i++;
				while (current_string[i] == 'n')
					i++;
				if (!current_string[i])
					return (1);
			}
			return (0);
		}
		current = current->next;
	}
	return (0);
}
char	**string_to_print(t_tokens **head)
{
	t_tokens	*current;
	char		*current_string;
	int			i;
	int			option;

	i = 0;
	option = 0;
	current = *head;
	current = current->next;
	while (current)
	{
		while (current->type == WORD)
		{
			current_string = del_quote(current->next);
			if (!current_string)
				return (NULL);
			if (current_string[i] == '-')
			{
				i++;
				while (current_string[i] == 'n')
					i++;
				if (!current_string[i])
				{
					current = current->next;
					option = 1;
				}
				else
					return ();
			}
		}
		current = current->next;
	}
	return (0);
}
int	echo(t_tokens **head)
{
	int		option;
	char	*string;

	option = is_option(head);
	string = string_to_print(head);
	if (!option && !string)
		return (ft_putchar_fd('\n', 1), 0);
	else if (string && !option)
		return (print_for_echo(string), ft_putchar_fd('\n', 1), 0);
	else if (!string && !ft_strncmp("-n", option, 3))
		return (0);
	else
		str_to_print = check_echo_option(option, string);
	print_for_echo(str_to_print);
	return (free(str_to_print), 0);
}
