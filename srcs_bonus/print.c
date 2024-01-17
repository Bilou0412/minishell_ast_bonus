/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 16:50:50 by soutin            #+#    #+#             */
/*   Updated: 2024/01/12 20:28:50 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	printtokens(t_tokens **head)
// {
// 	t_tokens	*current;

// 	current = *head;
// 	while (current)
// 	{
// 		printf("l%s %d", current->string, current->type);
// 		current = current->next;
// 	}
// 	printf("\n");
// }

// void	printtab(char **v)
// {
// 	static int	i;

// 	while (*v)
// 	{
// 		printf("argv[%d] : %s\n", i, *v);
// 		v++;
// 		i++;
// 	}
// }

// void	print_tree(t_ast *ast, int depth)
// {
// 	int	i;

// 	i = 0;
// 	if (!ast)
// 		return ;
// 	print_tree(ast->right, depth + 1);
// 	while (i++ < depth)
// 		printf("    ");
// 	if (!ast->tokens)
// 	{
// 		if (ast->type == PIPE)
// 			printf("| %d\n", ast->type);
// 		if (ast->type == OR)
// 			printf("|| %d\n", ast->type);
// 		if (ast->type == AND)
// 			printf("&& %d\n", ast->type);
// 	}
// 	else
// 	{
// 		printf("%d ", ast->type);
// 		printtokens(&ast->tokens);
// 	}
// 	print_tree(ast->left, depth + 1);
// }

void	my_usleep(unsigned int microseconds)
{
	unsigned int	i;

	i = 0;
	while (i < microseconds)
		i++;
}

void	sleepprintf(char *str)
{
	my_usleep(35000000);
	printf("%s", str);
}

void	slllllprintf(char *str)
{
	my_usleep(150000);
	printf("%s", str);
}
