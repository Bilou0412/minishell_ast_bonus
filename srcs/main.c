#include "../inc/minishell.h"
#include <stdio.h>
#include <string.h>

void	print_lex_info(t_tokens *tok)
{
	int	i;

	i = 0;
	while (tok)
	{
		ft_printf("tok[%d] : %s\n type : ", i, tok->token);
		if (tok->type == 0)
			ft_printf("LESS\n");
		else if (tok->type == 1)
			ft_printf("GREAT\n");
		else if (tok->type == 2)
			ft_printf("GG\n");
		else if (tok->type == 3)
			ft_printf("LL\n");
		else if (tok->type == 4)
			ft_printf("PIPE\n");
		else if (tok->type == 5)
			ft_printf("WORD\n");
		else if (tok->type == 6)
			ft_printf("ERRORL\n");
		else if (tok->type == 7)
			ft_printf("DOLLARS\n");
		else if (tok->type == 8)
			ft_printf("LIMITER\n");
		else if (tok->type == 9)
			ft_printf("RESERVED\n");
		else if (tok->type == 10)
			ft_printf("INDEFINE\n");
		else if (tok->type == 11)
			ft_printf("INFILE\n");
		tok = tok->next;
		i++;
	}
}

int	main(void)
{
	t_tokens *tok;
	t_input_str str_in;

	
	while (1)
	{
		tok = NULL;
		str_in.curpos = 0;
		str_in.buff = readline("zebishell> ");
		if (*str_in.buff)
		{
			token_m(&str_in, &tok);
			print_lex_info(tok);
			free(str_in.buff);
		}
		else
			free(str_in.buff);
	}
}