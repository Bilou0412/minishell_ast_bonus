#include "../../inc/minishell.h"

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
	if (!ft_strncmp(content, "$?", 2))
		return (ERRORLVL);
	if (content[0] == '$')
		return (DOLLARS);
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