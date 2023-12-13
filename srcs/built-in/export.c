/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:07:56 by bmoudach          #+#    #+#             */
/*   Updated: 2023/12/13 16:16:25 by bmoudach         ###   ########.fr       */
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
	if (!key[i] || (!ft_isalpha(key[i]) && key[i] != '_'))
		return (ft_printf("bash: export: `%s': not a valid identifier\n", key),
			1);
	while (key[i])
	{
		if (ft_isalnum(key[i]) || key[i] == '_')
			i++;
		else
			return (ft_printf("bash: export: `%s': not a valid identifier\n",
					key), 1);
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
