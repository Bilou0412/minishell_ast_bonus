/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:23:57 by soutin            #+#    #+#             */
/*   Updated: 2023/12/09 20:42:16 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "parser.h"
# include <errno.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define FREE_FULL 1
# define FREE_BUILTIN 2
# define LEFT 1
# define RIGHT 0

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
	char			**envp;
	int				nb_pipes;
}					t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_vars
{
	t_str_data		str_in;
	t_tokens		*tokens;
	t_ast			*ast;
	t_cmd			cmd;
	int				last_return_val;
	t_env			*envl;
	bool			stop;
	struct termios	original;

}					t_vars;

t_vars				*_vars(void);

void				print_tree(t_ast *ast, int depth);
void				printtab(char **v);
void				printtokens(t_tokens **head);

void				*ft_collector(void *ptr, bool clean);
void				del_a_garbage(t_list **lst, void *ptr);
void				super_free(void **__ptr);
void				freetabs(char **tab);
void				free_tree(t_ast **ast);
void				freevars(t_vars *vars, int i);
void				free_envl(t_env **lst);

int					exit_prog(int code_err);
void				ctrl_c(int sig);

int					setup_env(t_env **envl, char **envp);
t_env				*search_envl(t_env **envl, char *key);

t_tokens			*ft_toknew(char *content, int type, t_expand *lst_expand);
t_expand			*ft_explast(t_expand **lst_expand);
void				ft_tokadd_front(t_tokens **lst, t_tokens *new);
int					ft_toksize(t_tokens *lst);
t_tokens			*ft_toklast(t_tokens **tok);
void				ft_tokadd_back(t_tokens **lst, t_tokens *new);
void				ft_tokdelone(t_tokens *lst);
void				ft_tokclear(t_tokens **lst);
int					file_add_back(t_files **head, int new_fd);
void				delete_file_tokens(t_tokens **head, t_tokens **curr);
void				free_files(t_files **lst);

void				token_m(t_vars *vars, t_tokens **tok);

int					launch_ast(t_vars *vars);
int					read_ast(t_vars *vars, t_ast *current, bool is_pipe);
int					expand(t_tokens **head, t_vars *vars);

int					exec_pipes(t_vars *vars, t_ast *curr, int *pipe_fds,
						bool direction);
int					exec_simple(t_vars *vars, t_tokens **head, bool is_pipe);
int					fill_cmd_argv(t_vars *vars, t_tokens *tokens);
int					sort_cmd(t_vars *vars, t_tokens **head);
char				**init_paths(t_vars *vars);
int					here_doc_loop(t_cmd *cmd, t_tokens *curr);
int					path_to_argv(t_cmd *cmd);
int					is_builtin_pipe(t_vars *vars, t_tokens **head);
int					is_builtin(char *word);
int					handle_files(t_cmd *cmd, t_tokens *arm);
t_tokens			*duplicate_current_cmd(t_vars *vars, t_tokens **head,
						int current_cmd);
int					search_envl_index(char *var, t_vars *all);
int					multiple_dup2(t_vars *vars, int flag);
char				*cmdjoin(char *path, char *cmd);
int					waitchilds(t_vars *vars, int *pid, int childmax);
void				init_cmd_path(t_vars *vars);

int					exec_builtin(t_vars *vars);
int					check_stds(int *stds);

int					redirections(t_vars *vars);

int					go_through_paren(t_tokens **head);
int					syntax_error(t_tokens **head);
int					print_syntax_error(char *string);

char				*get_next_word(t_tokens **head);
int					cd(char **cmd_arg, t_env **envl);

void				env(t_env **envl);
int					pwd(char **arg_cmd);
int					export(char **arg_cmd, t_env **envl);
int					echo(char **arg_cmd);
void				clear(void);

int					*char_to_expand(char *str);
void				del_char(char *address, char char_to_del);
int					browse_lst_and_expand(t_tokens **head, t_vars *vars);

void				ctrl_c(int sig);
void				ctrl_c_child(int sig);

void				nothing(int sig);
char				**env_to_tab(t_env **envl);
void				ft_env_add_back(t_env **tok, t_env *new);
t_env				*ft_env_new(char *key, char *value);
int					unset(char **cmd, t_env **envl);

void				shrek_print(void);
void				bye_print(void);

#endif