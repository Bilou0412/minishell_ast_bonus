#include "minishell.h"

void	clear(void)
{
	printf("\033[H\033[J");
}