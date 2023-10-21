#include "../../inc/minishell.h"

t_tokens	*ft_lstlast(t_tokens **tok)
{
	t_tokens	*tmp;

	tmp = *tok;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}
t_tokens	*ft_lstnew(char *content, int type)
{
	t_tokens	*new;

	new = (t_tokens *)ft_calloc(1, sizeof(*new));
	if (!new)
		return (NULL);
	new->token = content;
	new->type = type;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(t_tokens **tok, t_tokens *new)
{
	t_tokens	*tmp;

	if (tok)
	{
		if (*tok == NULL)
			*tok = new;
		else
		{
			tmp = ft_lstlast(tok);
			tmp->next = new;
		}
	}
}
void	ft_lstadd_front(t_tokens **tok, t_tokens *new)
{
	if (tok)
	{
		if (*tok)
			new->next = *tok;
		*tok = new;
	}
}