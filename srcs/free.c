#include "../inc/minishell.h"

int	free_struc(t_tokens *tok)
{
	t_tokens *tmp;

	while (tok)
	{
		tmp = tok->next;
		free(tok->token);
		free(tok);
		tok = tmp;
	}
	return (0);
}