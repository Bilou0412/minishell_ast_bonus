/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 16:50:50 by soutin            #+#    #+#             */
/*   Updated: 2023/10/25 16:35:30 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	printlist(t_cmds **head)
{
	t_cmds	*current;

	current = *head;
	while (current)
	{
		ft_printf("%s ", current->string);
		current = current->next;
	}
}

// void	printtokens(t_tokens **head)
// {
// 	t_tokens	*current;

// 	current = *head;
// 	while (current)
// 	{
// 		ft_printf("%s : \n", current->string);
// 		if (current->type == WORD)
// 			ft_printf("WORD");
// 		else if (current->type == FILEPATH)
// 			ft_printf("FILEPATH");
// 		else if (current->type == LIMITER)
// 			ft_printf("LIMITER");
// 		else if (current->type == RESERVEDW)
// 			ft_printf("RESERVEDw");
// 		else if (current->type == DOLLAR)
// 			ft_printf("ENVVARIABLE");
// 		else if (current->type == GREAT)
// 			ft_printf("GREAT");
// 		else if (current->type == DGREAT)
// 			ft_printf("DGREAT");
// 		else if (current->type == LESS)
// 			ft_printf("LESS");
// 		else if (current->type == DLESS)
// 			ft_printf("DLESS");
// 		else if (current->type == PIPE)
// 			ft_printf("PIPE");
// 		else if (current->type == AND)
// 			ft_printf("AND");
// 		else if (current->type == OR)
// 			ft_printf("OR");
// 		else if (current->type == O_PARENTHESIS)
// 			ft_printf("O_PARENTHESIS");
// 		else if (current->type == C_PARENTHESIS)
// 			ft_printf("C_PARENTHESIS");
// 		current = current->next;
// 	}
// }

void	printtab(char **v)
{
	static int i; 
	
	while (*v)
	{
		printf("argv[%d] : %s\n", i, *v);
		v++;
	}
	i++;
}

void	print_tree(t_ast *ast, int depth)
{
	int	i = 0;

	if (!ast)
		return ;
	print_tree(ast->right, depth + 1);
	while (i < depth)
	{
    	ft_printf("   ");
        i++;
    }
	printlist(&ast->cmds);
	printf("\n");
	print_tree(ast->left, depth + 1);
}