/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   own_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:18:53 by soutin            #+#    #+#             */
/*   Updated: 2023/12/09 18:16:34 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*search_envl(t_env **envl, char *key)
{
	t_env	*tmp;

	tmp = *envl;
	while (tmp)
	{
		if ((ft_strlen(key) == ft_strlen(tmp->key)) && !ft_strncmp(tmp->key,
				key, ft_strlen(key)))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_env	*ft_env_new(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)ft_calloc(1, sizeof(*new));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

t_env	*ft_env_last(t_env **tok)
{
	t_env	*tmp;

	tmp = *tok;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	ft_env_add_back(t_env **tok, t_env *new)
{
	t_env	*tmp;

	if (tok)
	{
		if (*tok == NULL)
			*tok = new;
		else
		{
			tmp = ft_env_last(tok);
			tmp->next = new;
		}
	}
}

int	setup_env(t_env **envl, char **envp)
{
	t_env	*tmp;
	int		key_len;
	char	*key;
	char	*value;
	int		i;

	tmp = *envl;
	i = 0;
	while (envp[i])
	{
		key_len = ft_strlen_to_char(envp[i], '=');
		key = (char *)ft_collector(ft_substr(envp[i], 0, key_len), false);
		if (key_len == ft_strlen(envp[i]))
			value = ft_collector(ft_strdup(""), false);
		else
			value = (char *)ft_collector(ft_strdup(envp[i] + key_len + 1),
					false);
		ft_env_add_back(envl, (t_env *)ft_collector(ft_env_new(key, value),
				false));
		i++;
	}
	return (0);
}

char	**env_to_tab(t_env **envl)
{
	t_env	*tmp;
	char	**envp;
	int		i;

	tmp = *envl;
	i = 0;
	while (tmp)
	{
		if (tmp->value)
			i++;
		tmp = tmp->next;
	}
	envp = (char **)ft_collector(ft_calloc(i + 1, sizeof(char *)), false);
	tmp = *envl;
	i = 0;
	while (tmp)
	{
		if (tmp->value)
		{
			envp[i] = (char *)ft_collector(ft_strjoin(tmp->key, "="), false);
			envp[i] = (char *)ft_collector(ft_strjoin_gnl(envp[i], tmp->value),
					false);
			i++;
		}
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}
