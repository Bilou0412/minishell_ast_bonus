/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:23:57 by soutin            #+#    #+#             */
/*   Updated: 2023/11/10 21:23:41 by soutin           ###   ########.fr       */
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
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
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
	char			*path;
	char			**env_paths;
	int				nb_forks;
	int				nb_pipes;
}					t_cmd;

typedef struct s_vars
{
	t_str_data		str_in;
	t_tokens		*tokens;
	t_ast			*ast;
	t_cmd			cmd;
	char			*prompt;
	int				last_return_val;
	int				nb_pipes;
	int				nb_forks;
	char			**envp;
	char			**envl;
	int				pipe_fd[2];
	int				tmp_fd;
	int				pid[1024];
}					t_vars;

t_vars				*_vars(void);

void				print_tree(t_ast *ast, int depth);
void				printtab(char **v);
void				printtokens(t_tokens **head);
void				freetabs(char **tab);

void				freevars(t_vars *vars, int i);
int					here_doc_loop(t_cmd *cmd, t_tokens *curr);

void				free_tree(t_ast **ast);

t_tokens			*ft_lstnew(char *content, int type);
void				ft_lstadd_front(t_tokens **lst, t_tokens *new);
int					ft_lstsize(t_tokens *lst);
t_tokens			*ft_lstlast(t_tokens **tok);
void				ft_lstadd_back(t_tokens **lst, t_tokens *new);
void				ft_lstdelone(t_tokens *lst, void (*del)(void *));
void				ft_lstclear(t_tokens **lst, void (*del)(void *));

int					launch_ast(t_vars *vars);

int					read_ast(t_vars *vars, t_ast *current);
void				count_cmd(t_vars *vars, t_ast *head);
void				delete_file_tokens(t_tokens **head, t_tokens **curr);
int					file_add_back(t_files **head, int new_fd);
int					fill_cmd_argv(t_vars *vars, t_tokens *tokens);
int					exec_cmd(t_vars *vars, t_tokens **head);
char				*search_envl(t_vars *vars, char *var_name);
char				**init_paths(t_vars *vars);
int					init_cmd_and_files(t_vars *vars, t_tokens **head);
int					waitchilds(t_vars *vars, int childmax);
char				*cmdjoin(char *path, char *cmd);
int					sort_cmd(t_vars *vars, t_tokens **head);

#endif