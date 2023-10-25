/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:23:57 by soutin            #+#    #+#             */
/*   Updated: 2023/10/25 16:38:41 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
# include "parser.h"
# include <errno.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>



typedef struct s_vars
{
	struct s_tokens	*tokens;
	struct s_ast	*ast;
	int				nb_cmds;
}					t_vars;



t_vars				*_vars(void);



void				printlist(struct s_cmds **head);
void				print_tree(t_ast *ast, int depth);
void				printtab(char **v);
void				printtokens(t_tokens **head);

void				free_tree(t_ast **ast);

t_tokens			*ft_lstnew(char *content, int type);
void				ft_lstadd_front(t_tokens **lst, t_tokens *new);
int					ft_lstsize(t_tokens *lst);
t_tokens			*ft_lstlast(t_tokens **tok);
void				ft_lstadd_back(t_tokens **lst, t_tokens *new);
void				ft_lstdelone(t_tokens *lst, void (*del)(void *));
void				ft_lstclear(t_tokens **lst, void (*del)(void *));

#endif