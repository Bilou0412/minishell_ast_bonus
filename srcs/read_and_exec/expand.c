/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:51:16 by soutin            #+#    #+#             */
/*   Updated: 2023/11/29 16:58:59 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_char_in_str(char *str, char c)
{
	int	i;
	int	number_of_char;

	i = 0;
	number_of_char = 0;
	while (str[i])
	{
		if (str[i] == c)
			number_of_char++;
		i++;
	}
	return (number_of_char);
}

char	**get_array_of_value_to_expand(t_tokens **head, t_vars *vars)
{
	char		**value_of_var_to_expand;
	char		*var_to_find_in_env;
	int			number_of_dollars;
	int			size_of_array;
	int			i;
	int			j;
	t_tokens	*tmp;

	tmp = *head;
	i = 0;
	j = 0;
	number_of_dollars = 0;
	size_of_array = count_char_in_str(tmp->string, '$');
	value_of_var_to_expand = ft_calloc(size_of_array + 1, sizeof(char *));
	if (!value_of_var_to_expand)
		return (NULL);
	while (tmp->string[i])
	{
		if (tmp->string[i] == '$')
		{
			var_to_find_in_env = ft_substr(tmp->string, i + 1,
				tmp->expand[number_of_dollars]);
			if (!var_to_find_in_env)
				return (NULL);
			value_of_var_to_expand[number_of_dollars] = ft_strdup(search_envl(vars,
					var_to_find_in_env));
			if (!value_of_var_to_expand[number_of_dollars]
				&& tmp->expand[number_of_dollars])
				return (ft_free_tab(value_of_var_to_expand), NULL);
			else if (value_of_var_to_expand[number_of_dollars][j])
			{
				while (value_of_var_to_expand[number_of_dollars][j] != '=')
					del_char(value_of_var_to_expand[number_of_dollars],
						value_of_var_to_expand[number_of_dollars][j]);
				del_char(value_of_var_to_expand[number_of_dollars],
					value_of_var_to_expand[number_of_dollars][j]);
				j = 0;
			}
			number_of_dollars++;
		}
		i++;
	}
	return (value_of_var_to_expand);
}

int	expand(t_tokens **head, t_vars *vars)
{
	char		*str;
	char		**value_of_var_to_expand;
	int			i;
	int			nb_dollars;
	int			size_to_add;
	char		*string_to_add;
	t_tokens	*tmp;

	tmp = *head;
	i = 0;
	nb_dollars = 0;
	str = NULL;
	value_of_var_to_expand = get_array_of_value_to_expand(head, vars);
	if (!value_of_var_to_expand)
		return (-1);
	while (tmp->string[i])
	{
		if (tmp->string[i] == '$')
		{
			if (!nb_dollars && i > 0)
				str = ft_substr(tmp->string, i - size_to_add, size_to_add);
			else if (i > 0)
			{
				string_to_add = ft_substr(tmp->string, i - size_to_add,
					size_to_add);
				if (!string_to_add)
					return (-1);
				str = ft_strjoin_gnl(str, string_to_add);
				free(string_to_add);
			}
			if (!str && i > 0)
				return (-1);
			size_to_add = 0;
			str = ft_strjoin_gnl(str, value_of_var_to_expand[nb_dollars]);
			if (!str)
				return (-1);
			i += tmp->expand[nb_dollars] + 1;
			nb_dollars++;
		}
		size_to_add++;
		i++;
	}
	string_to_add = ft_substr(tmp->string, i - size_to_add, size_to_add);
	if (!string_to_add)
		return (-1);
	str = ft_strjoin_gnl(str, string_to_add);
	// super_free(&tmp->string);
	tmp->string = str;
	return (0);
}

int	*char_to_expand(char *str)
{
	int		number_of_dollars;
	int		i;
	int		*expand;
	int		in_quote;
	char	quote;
	int		dollars;

	number_of_dollars = count_char_in_str(str, '$');
	if (!number_of_dollars)
		return (NULL);
	expand = ft_calloc(number_of_dollars + 1, sizeof(int));
	if (!expand)
		return (NULL);
	i = 0;
	number_of_dollars = -1;
	quote = 0;
	in_quote = false;
	while (str[i])
	{
		if (ft_strchr("\'\"", str[i]) && in_quote == false)
		{
			in_quote = true;
			quote = str[i];
			dollars = 0;
		}
		else if (str[i] == quote && in_quote == true)
		{
			in_quote = false;
			quote = 0;
			dollars = 0;
		}
		else if (str[i] == '$')
		{
			number_of_dollars++;
			expand[number_of_dollars] = 0;
			if (quote != '\'')
				dollars = 1;
		}
		else if (dollars == 1)
			expand[number_of_dollars]++;
		i++;
	}
	expand[number_of_dollars + 1] = -1;
	return (expand);
}

int	browse_lst_and_expand(t_tokens **head, t_vars *vars)
{
	t_tokens *tmp;

	tmp = *head;
	while (tmp)
	{
		if (tmp->expand)
			expand(&tmp, vars);
		tmp = tmp->next;
	}
	return (0);
}