/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:23:57 by soutin            #+#    #+#             */
/*   Updated: 2023/11/07 12:40:10 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
# include "parser.h"
# include <errno.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>

typedef struct s_files
{
	int				fd;
	struct s_files	*next;
}					t_files;

typedef struct s_cmd
{
	t_files			*infiles;
	t_files			*outfiles;
	char			**argv;
	char			*cmd_path;
	char			**envp_paths;

}					t_cmd;

typedef struct s_vars
{
	t_tokens		*tokens;
	t_ast			*ast;
	t_str_data		str_in;
	t_cmd			cmd;
	char			**envp;
	char			**envl;
	char			**envp_paths;
	int				pipe_fd[2];
	int				tmp_fd;
	int				pid[1024];
}					t_vars;

t_vars				*_vars(void);

void				print_tree(t_ast *ast, int depth);
void				printtab(char **v);
void				printtokens(t_tokens **head);

int					read_ast(t_vars *vars, t_ast *current);
int					here_doc_loop(t_cmd *cmd, t_tokens *curr);

void				free_tree(t_ast **ast);

t_tokens			*ft_lstnew(char *content, int type);
void				ft_lstadd_front(t_tokens **lst, t_tokens *new);
int					ft_lstsize(t_tokens *lst);
t_tokens			*ft_lstlast(t_tokens **tok);
void				ft_lstadd_back(t_tokens **lst, t_tokens *new);
void				ft_lstdelone(t_tokens *lst, void (*del)(void *));
void				ft_lstclear(t_tokens **lst, void (*del)(void *));

#endif