/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:07:56 by bmoudach          #+#    #+#             */
/*   Updated: 2023/12/11 17:14:52 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(t_env **envl)
{
	t_env	*tmp;

	tmp = *envl;
	while (tmp)
	{
		if (!(tmp->value))
			printf("export %s\n", tmp->key);
		else
			printf("export %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

int	add_to_env(char *key, char *value, t_env **envl)
{
	int		i;
	t_env	*to_replace;

	i = 0;
	while (key[i])
	{
		if (key[i] == '_' || (key[i] > 96 && key[i] < 123) || (key[i] > 64
				&& key[i] < 91))
			i++;
		else
			return (1);
	}
	to_replace = search_envl(envl, key);
	if (to_replace && value)
		to_replace->value = value;
	else if (!to_replace)
		ft_env_add_back(envl, (t_env *)ft_collector(ft_env_new(key, value),
				false));
	return (0);
}

char	*get_value_export(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '=')
			return (ft_collector(ft_strdup(cmd + i + 1), false));
		i++;
	}
	return (NULL);
}

char	*get_key_export(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '=')
			return (ft_collector(ft_substr(cmd, 0, i), false));
		i++;
	}
	return (ft_collector(ft_strdup(cmd), false));
}

int	export(char **arg_cmd, t_env **envl)
{
	char	*key;
	char	*value;
	int		nb_cmd;
	int		i;
	int		ret_value;

	nb_cmd = ft_arraylen(arg_cmd);
	ret_value = 0;
	if (nb_cmd == 1)
		print_export(envl);
	else
	{
		i = 1;
		while (i < nb_cmd)
		{
			key = get_key_export(arg_cmd[i]);
			value = get_value_export(arg_cmd[i]);
			ret_value = add_to_env(key, value, envl);
			i++;
		}
	}
	return (ret_value);
}
