#include "minishell.h"

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
void	ft_exp_add_back(t_expand **expand, t_expand *new)
{
	t_tokens	*tmp;

	if (expand)
	{
		if (*expand == NULL)
			*expand = new;
		else
		{
			tmp = ft_toklast(expand);
			tmp->next = new;
		}
	}
}
t_tokens	*ft_expand_new(char *content)
{
	t_expand	*new;

	new = (t_expand *)ft_calloc(1, sizeof(*new));
	if (!new)
		return (NULL);
	new->to_expand = content;
	new->next = NULL;
	return (new);
}
void	content_to_lst_expand(char *to_expand, t_expand *expand)
{
	t_expand	*node;

	node = node = (t_expand *)ft_collector(ft_expand_new(to_expand), false);
	ft_exp_add_back(expand, node);
	return (0);
}
